import tkinter
from ctypes import *
from tkinter import ttk
from serial_management import SerialFrame
from serial_management import SerialHandler
from reception_board import ReceivedFrameZone
from xl320_board import FrameGenerationZone

class XL320Tool(tkinter.Tk):
	def __init__(self,parent):
		tkinter.Tk.__init__(self, parent)
		self.parent=parent
		self.serial=SerialHandler(self)
		self.initialize()

	def initialize(self):
		self.grid
		my_SerialFrame = SerialFrame(self)
		my_SerialFrame.grid(column=0,row=0,sticky='NSEW')
		my_FrameGenerationZone=FrameGenerationZone(self)
		my_FrameGenerationZone.grid(column=0,row=1)
		my_ReceivedFrameZone=ReceivedFrameZone(self)
		my_ReceivedFrameZone.setText('st')
		my_ReceivedFrameZone.grid(column=0,row=2)
		self.update()

if __name__ == '__main__':
	app = XL320Tool(None)
	app.resizable(False,False)
	app.mainloop()
	# add parameter for autosend