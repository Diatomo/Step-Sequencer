

from tkinter import *;
import serial

gui = Tk()
ser = serial.Serial('/dev/ttyACM0')


class Muxer:

    def __init__(self):
        self.nRows = 4
        self.nCols = 4
        self.widgets = []
        self.state = []

    def setup(self):
        self.setupState()
        self.setupWdigets()
        self.configureWidgets()

    def setupState(self):
        for r in range(self.nRows):
            temp = []
            for c in range(self.nCols):
                temp.append(0)
            self.state.append(temp)
            temp = []

    def setupWidgets(self):
        for r in range(nRows):
            temp = []
            for c in range(nCols):
                start = start + 1
                temp.append(Button(gui, text = str(start), borderwidth = 1))
            widgets.append(temp)
            temp = []

    def configureWidgets(self):
        for r in range(nRows):
            for c in range(nCols):
                widgets[r][c]["fg"] = "black"
                widgets[r][c]["bg"] = "white"
                widgets[r][c]["activebackground"] = "red"
                widgets[r][c].grid(row = r, column = c)

    def poll(self):
        x = ser.read(10) #test how this is going to read
        #grab toggle byte && change state
        widgets[x[0]][x[1]] = x[2]
        for r in range(nRows):
            for c in range(nCols):
                 
        gui.mainloop()

    def loop(self):
        for r in range(nRows):
            for c in range(nCols):
                if (state[r][c] == True):
                    widgets[r][c].flash()
        gui.mainloop()

