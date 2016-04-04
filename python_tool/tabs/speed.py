from ctypes import *
import tkinter
from tkinter import ttk


class SpeedTab(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()

	def initialize(self):
		self.grid()
		self.speedValueSpinBox=tkinter.Spinbox(self,from_=0,to=1023)
		self.speedValueSpinBox.grid(column=0,row=0)
		buttonSend=ttk.Button(self,text='Set Speed',command=self.OnButtonClick_Send)
		buttonSend.grid(column=0,row=1)

	def OnButtonClick_Send(self):
		speed=int(self.speedValueSpinBox.get())
		self.parent.lib.set_speed_servo(byref(self.parent.servo),c_uint(speed),c_uint(1))
