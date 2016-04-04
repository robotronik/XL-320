from ctypes import *
import tkinter
from tkinter import ttk


class IDTab(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()

	def initialize(self):
		self.grid()
		self.IDValueSpinBox=tkinter.Spinbox(self,from_=0,to=253)
		self.IDValueSpinBox.grid(column=0,row=0)
		buttonNewSendID=ttk.Button(self,text='Send new ID',command=self.OnButtonClick_SendID)
		buttonNewSendID.grid(column=0,row=1)

	def OnButtonClick_SendID(self):
		#self.parent.lib.
		print(self.IDValueSpinBox.get())
