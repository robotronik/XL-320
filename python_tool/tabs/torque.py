from ctypes import *
import tkinter
from tkinter import ttk


class TorqueTab(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()

	def initialize(self):
		self.grid()
		self.IDValueSpinBox=tkinter.Spinbox(self,from_=0,to=1023)
		self.IDValueSpinBox.grid(column=0,row=0)
		buttonSend=ttk.Button(self,text='Set Torque Limit',command=self.OnButtonClick_Send)
		buttonSend.grid(column=0,row=1)

	def OnButtonClick_Send(self):
		libxl320=cdll.LoadLibrary("./libxl320.so")
		print(self.IDValueSpinBox.get())
