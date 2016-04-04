from ctypes import *
from tkinter import ttk

class ModeTab(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()
		self.mode_values={}
		self.mode_values['Wheel']=1
		self.mode_values['Join']=2

	def initialize(self):
		self.grid()

		self.choice_list=ttk.Combobox(self)
		self.choice_list.config(values=['Wheel','Join'])
		self.choice_list.grid(column=0,row=0)

		self.buttonSend=ttk.Button(self,text='Set Mode',command=self.OnButtonClick_Send)
		self.buttonSend.grid(column=0,row=1)

	def OnButtonClick_Send(self):
		mode=self.mode_values[self.choice_list.get()]
		self.parent.lib.set_control_mode_servo(byref(self.parent.servo),c_uint(mode),c_uint(1))
		pass
