import PySimpleGUI as sg
import os.path

layout = [
    [sg.Image("x.png")],
]

window = sg.Window("test",layout)

while True:
    event, values = window.read()
    if event == 'Exit' or event == sg.WIN_CLOSED:
        break

window.close()