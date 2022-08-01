import subprocess


starte = '532733'
startn = '176014'
ende = '530932'
endn = '175200'


# subprocess.call(["./main", "1", "2", "3", "9"])
subprocess.call(["./main", starte, startn, ende, endn])

f = open('frontend/route.txt', 'r')
route = f.readlines()
print(route)

"""
pass start + end coords to dijkstras
return path to here in nice format 
request appropriately sized img and plot route

"""