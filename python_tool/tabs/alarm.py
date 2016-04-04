from ctypes import *
from tkinter import ttk


class AlarmTab(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()

	def initialize(self):
		self.grid()
		self.buttonSend=ttk.Button(self,text='Alarm Shutdown',command=self.OnButtonClick_Send)
		self.buttonSend.grid(column=0,row=0)

	def OnButtonClick_Send(self):
		# libxl320=cdll.LoadLibrary("./libxl320.so")
		pass
