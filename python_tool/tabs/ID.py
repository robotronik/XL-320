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
		self.IDValueSpinBox=tkinter.Spinbox(self,from_=0,to=252)
		self.IDValueSpinBox.grid(column=0,row=0)
		buttonNewSendID=ttk.Button(self,text='Send new ID',command=self.OnButtonClick_SendID)
		buttonNewSendID.grid(column=0,row=1)

	def OnButtonClick_SendID(self):
		new_ID=int(self.IDValueSpinBox.get())
		self.parent.lib.set_ID_servo(byref(self.parent.servo),c_uint(new_ID),c_uint(1))
		print(self.IDValueSpinBox.get())
