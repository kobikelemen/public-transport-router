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

bsorder.append(bs[0].strip())
while seq[i] > seq[i-1]:
    bsorder.append(bs[i].strip())
    i+=1
    


# for i in range(len(bus_routes)):
for i in range(1):

    routei = bus_routes[i]
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

        if j["destinationName"].upper() in bsorder[-1]: 
            at = j["expectedArrival"][11:-1]
            ts = j["timestamp"][11:18]
            x = "%H:%M:%S"
            arrival_time = datetime.strptime(at, x)
            time_stamp = datetime.strptime(ts, x)
            dt = arrival_time - time_stamp
            time_to_arrival = str(dt)

            # length = len(j["lineName"]) + len(time_to_arrival) + len(j["stationName"]) + 4
            # fwrite.write(j["lineName"] + " " +time_to_arrival + " " + j["stationName"].upper() + '\n')

            if j["stationName"].upper() in bustimes:
                bustimes[j["stationName"].upper()].append(int(time_to_arrival[2:4]))
                bustimes[j["stationName"].upper()].sort()
            else:
                bustimes[j["stationName"].upper()] = [int(time_to_arrival[2:4])]

        for key, value in j.items():
            print(key, ":", value)
        print('\n\n\n\n')

    fwrite.close()



fail = 0

for i in bsorder:
    try:
        print(i + ": ", bustimes[i])

    except:
        fail += 1
print('\nfails: ', fail)


journeytimes = []

# print(bustimes[bsorder[0]))
prev = min(bustimes[bsorder[0]])
journeytimes.append(prev)
# print(bustimes)
# print(bsorder)
prevmin = min(bustimes[bsorder[0]])

difs = []

for i in bsorder[1:]:
    try:
        times = bustimes[i]
    except:
        continue
    check = False
    for t in times:
        if t >= prev:
            difs.append(t-prev)
            prev = t
            journeytimes.append(prev)
            check = True
            
            break
    if not check:
        prev = prevmin
        for t in times:
            if t >= prev:
                difs.append(t-prev)
                prev = t
                journeytimes.append(prev)
                check = True
                break
    prevmin = min(times)

print(journeytimes)
print(difs)


f = open('bus_times/1dt.txt', 'w')

for i in difs:
    f.write(str(i) + '\n')

