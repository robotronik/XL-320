from ctypes import *
import tkinter
from tkinter import ttk


class PositionTab(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()

	def initialize(self):
		self.grid()
		self.positionValueSpinBox=tkinter.Spinbox(self,from_=0,to=1023)
		self.positionValueSpinBox.grid(column=0,row=0)
		buttonSend=ttk.Button(self,text='Set Position',command=self.OnButtonClick_Send)
		buttonSend.grid(column=0,row=1)

	def OnButtonClick_Send(self):
		position=int(self.positionValueSpinBox.get())
		self.parent.lib.set_angle_servo(byref(self.parent.servo),c_uint(position),c_uint(1))
