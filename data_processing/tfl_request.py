import requests
from datetime import datetime
import time
import os.path

fr = open("../bus_sequences/route.txt", "r")


r = fr.readlines()
bus_routes = []
prev = ""
for i in r:
    if i != prev:
        prev = i
        bus_routes.append(i.strip())

fs = open("../bus_sequences/sequence.txt", "r")
seq = fs.readlines()
for i in range(len(seq)):
    seq[i] = int(seq[i].strip())


bsorder = []
filebs = open("../bus_sequences/stop_name.txt", "r")
bs = filebs.readlines()

i = 1
while seq[i] > seq[i-1]:
    bsorder.append(bs[i].strip())
    i+=1
    




# for i in range(len(bus_routes)):
for i in range(1):

    routei = bus_routes[i]
    minbustimes = {}

    bustimes= {}

    fwrite = open("bus_times/"+ routei+ ".txt", "w+")
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


        if j["stationName"].upper() in bustimes:
            bustimes[j["stationName"].upper()].append(int(time_to_arrival[2:4]))
        else:
            bustimes[j["stationName"].upper()] = [int(time_to_arrival[2:4])]
        
        # if j["stationName"].upper() == "ANCHOR STREET":
        #     print(time_to_arrival)

        # if j["stationName"] in minbustimes:
        #     # print('time_to_arrival: ', time_to_arrival)
        #     # print('minbustimes[]: ', minbustimes[j["stationName"]])
        #     if int(time_to_arrival[2:4]) < int(minbustimes[j["stationName"]][2:4]):
        #         minbustimes[j["stationName"]] = time_to_arrival
        #         lines = fwrite.readlines()
        #         for n in range(len(lines)):
        #             if j["stationName"] in lines[n]:
        #                 lines[n] = j["lineName"] + " " +time_to_arrival + " " + j["stationName"].upper() + '\n'
        #                 fwrite.writelines(lines)

        # else:
        #     fwrite.write(j["lineName"] + " " +time_to_arrival + " " + j["stationName"].upper() + '\n')
        #     minbustimes[j["stationName"]] = time_to_arrival
    fwrite.close()

    #     for key, value in j.items():
    #         print(key, ":", value)
    #     print('\n\n\n\n')
    # print('routei: ', routei)


# print(bsorder, '\n\n')
# print(bustimes)

fail = 0

for i in bsorder:
    try:
        print(i + ": ", bustimes[i])

    except:
        fail += 1
print('fails: ', fail)