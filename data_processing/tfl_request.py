import requests
from datetime import datetime
import time
import os.path

fr = open("../bus_sequences/route.txt", "r")


seq = fr.readlines()
bus_routes = []
prev = ""
for i in seq:
    if i != prev:
        prev = i
        bus_routes.append(i.strip())



for i in range(len(bus_routes)):

    routei = bus_routes[i]

    fwrite = open("bus_times/"+ routei+ ".txt", "w")
    url = 'https://api.tfl.gov.uk/line/'+routei+'/arrivals'
    print(url)
    response = requests.get(url)
    while response.status_code != 200: 
        time.sleep(15)
        response = requests.get(url)
        
    json = response.json()
    

    


    for j in json:

        at = j["expectedArrival"][11:-1]
        ts = j["timestamp"][11:18]
        x = "%H:%M:%S"
        arrival_time = datetime.strptime(at, x)
        time_stamp = datetime.strptime(ts, x)
        dt = arrival_time - time_stamp
        time_to_arrival = str(dt)

        length = len(j["lineName"]) + len(time_to_arrival) + len(j["stationName"]) + 4
        fwrite.write(j["lineName"] + " " +time_to_arrival + " " + j["stationName"].upper() + '\n')
    
    
    fwrite.close()

    #     for key, value in j.items():
    #         print(key, ":", value)
    #     print('\n\n\n\n')
    # print('routei: ', routei)

