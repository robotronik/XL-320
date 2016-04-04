from ctypes import *
from tkinter import ttk


class LEDColorTab(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()

	def initialize(self):
		self.grid()
		self.buttonSend=ttk.Button(self,text='Set LED Color',command=self.OnButtonClick_Send)
		self.buttonSend.grid(column=0,row=0)

	def OnButtonClick_Send(self):
		self.parent.lib.set_led_color_servo(byref(self.parent.servo),2,1)
		pass
