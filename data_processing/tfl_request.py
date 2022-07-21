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



filebs = open("../bus_sequences/stop_name.txt", "r")
bs = filebs.readlines()
print('\n\nbs',bs[0:100], '\n')

n = 1

    

for i in range(len(bus_routes)):
# for i in range(1):
    
    routei = bus_routes[i]
    url = 'https://api.tfl.gov.uk/line/'+routei+'/arrivals'
    print(url)
    response = requests.get(url)
    while response.status_code != 200: 
        time.sleep(15)
        response = requests.get(url)
    json = response.json()


    for q in range(2):


        bsorder = []
        bsorder.append(bs[n-1].strip())
        while seq[n] > seq[n-1]:
            print('hi')
            bsorder.append(bs[n].strip())
            n+=1
        n += 1        

        bustimes= {}
        fwrite = open("bus_times/"+ routei+ ".txt", "w+")

        
        for j in json:

            if "BECKTON BUS STATION" in j["stationName"].upper():

                print("\n\nFOUND!\n")

                print("destinationName: ", j["destinationName"], '\n\n')
                for key, value in j.items():
                    print(key, ":", value)
                print('\n\n\n')


            disallowedchar = ".,'"
            dest = j["destinationName"].upper()
            for char in disallowedchar:
                dest = dest.replace(char, "")
        
            
            dest_words = dest.split()

            for d in dest_words:

                if d in bsorder[-1] or dest in bsorder[-2]: 
                    at = j["expectedArrival"][11:-1]
                    ts = j["timestamp"][11:18]
                    x = "%H:%M:%S"
                    arrival_time = datetime.strptime(at, x)
                    time_stamp = datetime.strptime(ts, x)
                    dt = arrival_time - time_stamp
                    time_to_arrival = str(dt)

                    # length = len(j["lineName"]) + len(time_to_arrival) + len(j["stationName"]) + 4
                    # fwrite.write(j["lineName"] + " " +time_to_arrival + " " + j["stationName"].upper() + '\n')

                    stationname = j["stationName"].upper()
                    if "  " in stationname:
                        stationname = stationname.replace("  ", " ")
                        # print("\n\n", stationname, "\n\n")

                    if stationname in bustimes:
                        bustimes[stationname].append(int(time_to_arrival[2:4]))
                        bustimes[stationname].sort()
                    else:
                        bustimes[stationname] = [int(time_to_arrival[2:4])]
                    
                    break

            # for key, value in j.items():
            #     print(key, ":", value)
            # print('\n\n\n\n')

        fwrite.close()


        fail = 0
        # for i in bsorder:
        #     try:
        #         print(i + ": ", bustimes[i])
        #     except:
        #         fail += 1

        

        print('\nfails: ', fail)
        print('bustimes: ',bustimes)
        print('\nbsorder: ',bsorder, '\n')
        if routei == "106":
            continue
        uhohs = 0
        journeytimes = []
        try:
            prev = min(bustimes[bsorder[0]])
        except:
            prev = min(bustimes[bsorder[1]]) + 1
            # for u in range(len(prev)):
            #     prev[u] += 2
            uhohs += 1

        journeytimes.append(prev)
        prevmin = prev
        difs = []

        for a in bsorder[1:]:
            try:
                times = bustimes[a]
            except:
                # print('\nfail: ', i)
                fail += 1
                difs.append(2)
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
        f = open('bus_times/'+ routei+ 'dt.txt', 'w')
        for i in difs:
            f.write(str(i) + '\n')
        

