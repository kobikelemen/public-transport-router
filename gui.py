import keyword
import PySimpleGUI as sg
import os 
import sys
import inspect
import requests
import json
import subprocess
import folium

currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
# parentparentdir = os.path.dirname(parentdir)
# sys.path.insert(0, parentparentdir)
sys.path.insert(0, parentdir)

from req.autocomplete import autocomplete


def read_route():
    f = open('frontend/route.txt', 'r')
    route = f.readlines()
    # for i in route:
    #     route[i] = route[i].strip()
    return route


keywords = keyword.kwlist
font = ('Helvetica', 16)

layout = [
    [folium.Map(title='Golden Gate Bridge', location=(37.81959, -122.4785504))],
    [sg.Text('Input Python keyword:', font=font)],
    [sg.Input('', size=(20, 1), font=font, enable_events=True, key='-IN-')],

    [sg.pin(sg.Col([[sg.Listbox(values=[], size=(20, 3), enable_events=True, key='-BOX-',
        font=font, select_mode=sg.LISTBOX_SELECT_MODE_SINGLE, no_scrollbar=True)]],
        key='-BOX-CONTAINER-', pad=(0,0), visible=False))]
]

window = sg.Window('AutoComplete', layout, return_keyboard_events=True, finalize=True)
sel_item = 0
list_element = window.Element('-BOX-')
input_text = ""

res = None

while True:

    event, values = window.read()
    if event == sg.WINDOW_CLOSED:
        break
    # pressing down arrow will trigger event -IN- then aftewards event Down:40
    elif event == 'Down:40':
        sel_item = sel_item + (sel_item < len(prediction_list))
        list_element.Update(set_to_index=sel_item)
    elif event == 'Up:38':
        sel_item = sel_item - (sel_item > 0)
        list_element.Update(set_to_index=sel_item)
    elif event == '\r':
        if len(values['-BOX-']) > 0:
            window['-IN-'].update(value=values['-BOX-'])
            window['-BOX-CONTAINER-'].update(visible=False)
    elif event == '-IN-':
        text = values['-IN-']
        if text == input_text:
            continue
        else:
            input_text = text
        prediction_list = []
        if text:
            # prediction_list = [item for item in keywords if item.startswith(text)]
            res = autocomplete(text)
            if res == '':
                prediction_list = res
            else:
                prediction_list = [res[0]['address']]

        list_element.update(values=prediction_list)
        sel_item = 0
        list_element.Update(set_to_index=sel_item)

        if len(prediction_list) > 0:
            window['-BOX-CONTAINER-'].update(visible=True)
        else:
            window['-BOX-CONTAINER-'].update(visible=False)

    elif event == '-BOX-':

        if res and res != '':
            lat = res[0]['lat']
            long = res[0]['long']
            response = requests.get('http://webapps.bgs.ac.uk/data/webservices/CoordConvert_LL_BNG.cfc?method=LatLongToBNG&lat='+str(lat)+'&lon='+str(long))
            data = json.loads(response.text)
            northing = int(data['NORTHING'])
            easting = int(data['EASTING'])
            ende, endn = '526455', '179252' # imperial


            subprocess.call(["./main", str(easting), str(northing), ende, endn])
            route = read_route()
            print('route ', route)
            print('\n\nstart', easting, northing,'end', ende, endn)

        window['-IN-'].update(value=values['-BOX-'])
        visible = False
        window['-BOX-CONTAINER-'].update(visible=False)

window.close()