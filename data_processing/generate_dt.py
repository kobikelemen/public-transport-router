

oneminfrac = 2/3
twominfrac = 1/3





import random
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

n = 0

    

for i in range(len(bus_routes)):
# for i in range(1):
    
    routei = bus_routes[i]

    for q in range(2):
        
        difs = []

        while seq[n+1] > seq[n]:
            # print('hi')
            r = random.random()
            if r < twominfrac:
                difs.append(2)
            else:
                difs.append(1)
            n+=1
        n += 1  
        r = random.random()
        if r < twominfrac:
            difs.append(2)
        else:
            difs.append(1)


        f = open('bus_times/'+ routei+ 'dt.txt', 'w')
        for i in difs:
            f.write(str(i) + '\n')
        

