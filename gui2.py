from tkinter import *
import re
import tkinter
import tkintermapview
import os 
import sys
import inspect
import requests
import json
import subprocess

currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0, parentdir)

from req.autocomplete import autocomplete

def read_route():
    f = open('route.txt', 'r')
    route = f.readlines()
    buses, stops, coords = [], [], []
    for i, r in enumerate(route):
        r = r.strip()
        x = r.split(':')
        route[i] = x
    return route

def latlong_to_bng(lat, long):
    response = requests.get('http://webapps.bgs.ac.uk/data/webservices/CoordConvert_LL_BNG.cfc?method=LatLongToBNG&lat='+str(lat)+'&lon='+str(long))
    data = json.loads(response.text)
    northing = int(data['NORTHING'])
    easting = int(data['EASTING'])
    return northing, easting


def bng_to_latlong(easting, northing):
    rez = requests.get('http://webapps.bgs.ac.uk/data/webservices/CoordConvert_LL_BNG.cfc?method=BNGtoLatLng&easting='+str(easting)+'&northing='+str(northing))
    d = json.loads(rez.text)
    lat = float(d['LATITUDE'])
    lon = float(d['LONGITUDE'])
    return lat, lon


class AutocompleteEntry(Entry):
    def __init__(self, map, autocompleteList, *args, **kwargs):
        self.map = map
        self.bs_coords = []
        self.res = ''
        if 'listboxLength' in kwargs:
            self.listboxLength = kwargs['listboxLength']
            del kwargs['listboxLength']
        else:
            self.listboxLength = 8
        if 'matchesFunction' in kwargs:
            self.matchesFunction = kwargs['matchesFunction']
            del kwargs['matchesFunction']
        else:
            def matches(fieldValue, acListEntry):
                pattern = re.compile('.*' + re.escape(fieldValue) + '.*', re.IGNORECASE)
                return re.match(pattern, acListEntry)
                
            self.matchesFunction = matches

        
        Entry.__init__(self, *args, **kwargs)
        self.focus()
        self.autocompleteList = autocompleteList
        self.var = self["textvariable"]
        if self.var == '':
            self.var = self["textvariable"] = StringVar()

        self.var.trace('w', self.changed)
        self.bind("<Right>", self.selection)
        self.bind("<Up>", self.moveUp)
        self.bind("<Down>", self.moveDown)
        
        self.listboxUp = False

    def changed(self, name, index, mode):
        if self.var.get() == '':
            if self.listboxUp:
                self.listbox.destroy()
                self.listboxUp = False
        else:
            words = self.comparison()
            if words and words != '':
                if not self.listboxUp:
                    self.listbox = Listbox(width=self["width"], height=self.listboxLength)
                    self.listbox.bind("<Button-1>", self.selection)
                    self.listbox.bind("<Right>", self.selection)
                    self.listbox.place(x=self.winfo_x(), y=self.winfo_y() + self.winfo_height())
                    self.listboxUp = True
                
                self.listbox.delete(0, END)
                for w in words:
                    self.listbox.insert(END,w)
            else:
                if self.listboxUp:
                    self.listbox.destroy()
                    self.listboxUp = False
        
    def selection(self, event):
        if self.listboxUp:
            self.var.set(self.listbox.get(ACTIVE))
            self.listbox.destroy()
            self.listboxUp = False
            self.icursor(END)
            on_search()


    def moveUp(self, event):
        if self.listboxUp:
            if self.listbox.curselection() == ():
                index = '0'
            else:
                index = self.listbox.curselection()[0]
            if index != '0':                
                self.listbox.selection_clear(first=index)
                index = str(int(index) - 1)
                self.listbox.see(index) # Scroll!
                self.listbox.selection_set(first=index)
                self.listbox.activate(index)


    def moveDown(self, event):
        if self.listboxUp:
            if self.listbox.curselection() == ():
                index = '0'
            else:
                index = self.listbox.curselection()[0]
                
            if index != END:                        
                self.listbox.selection_clear(first=index)
                index = str(int(index) + 1)
                
                self.listbox.see(index) # Scroll!
                self.listbox.selection_set(first=index)
                self.listbox.activate(index) 

    def comparison(self):
        self.res = autocomplete(self.var.get())
        if self.res == '':
            prediction_list = self.res
        else:
            prediction_list = [self.res[0]['address']]
        return prediction_list

if __name__ == '__main__':

    mac = True
    linux = False
    windows = False
    if mac or linux:
        main_exec = './main'
    elif windows:
        main_exec = 'main.exe'
    
    labels = []

    def on_search():
        if entry.res and entry.res != '' and entry2.res and entry2.res != '':
                lat1 = entry.res[0]['lat']
                long1 = entry.res[0]['long']
                northing1, easting1 = latlong_to_bng(lat1, long1)
                lat2 = entry2.res[0]['lat']
                long2 = entry2.res[0]['long']
                northing2, easting2 = latlong_to_bng(lat2, long2)
                subprocess.call([main_exec, str(easting1), str(northing1), str(easting2), str(northing2)])
                route = read_route()
                print('\n\nroute')
                entry.bs_coords = []
                route.reverse()
                for index, x in enumerate(route):
                    print(x)
                    if x[0] != 'Journey time':
                        lat,lon = bng_to_latlong(x[2], x[3])
                        entry.bs_coords.append((lat,lon))
                        if index > 0 and route[index][0] != route[index-1][0]:
                            labels.append([route[index][0], lat, lon])

                lat1,lon1 = bng_to_latlong(easting1, northing1)
                lat2,lon2 = bng_to_latlong(easting2, northing2)
                entry.map.set_path([(lat2, lon2), entry.bs_coords[-1]])
                entry.map.set_path(entry.bs_coords[1:], color='#FF0000')
                entry.map.set_path([(lat1, lon1), entry.bs_coords[0], entry.bs_coords[1]])
                for l in labels:
                    if l[0] != '0':
                        entry.map.set_marker(float(l[1]), float(l[2]), text=l[0])


    autocompleteList = []
    def matches(fieldValue, acListEntry):
        pattern = re.compile(re.escape(fieldValue) + '.*', re.IGNORECASE)
        return re.match(pattern, acListEntry)
    
    root = Tk()
    root.title('London Public Transport Router')
    l = Label().grid(column=1)
    m = tkintermapview.TkinterMapView(l, width=800, height=600)
    m.set_position(51.475331432, -0.170165986)
    entry = AutocompleteEntry(m, autocompleteList, root, listboxLength=6, width=32, matchesFunction=matches)
    entry.grid(row=0, column=0)
    entry2 = AutocompleteEntry(m, autocompleteList, root, listboxLength=6, width=32, matchesFunction=matches)
    entry2.grid(row=1, column=0)
    m.grid(column=0)
    lsb = Label().grid(row=0, column=1)
    root.mainloop()