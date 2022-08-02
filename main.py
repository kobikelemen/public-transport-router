import subprocess
import os 
import sys
import inspect
# from ... import requests

currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0, parentdir)

from req import imgrequest

starte = '532733'
startn = '176014'
ende = '530932'
endn = '175200'


# subprocess.call(["./main", "1", "2", "3", "9"])
subprocess.call(["./main", starte, startn, ende, endn])

f = open('frontend/route.txt', 'r')
route = f.readlines()
print(route)
 
imgrequest.img()

"""
pass start + end coords to dijkstras
return path to here in nice format 
request appropriately sized img and plot route

"""