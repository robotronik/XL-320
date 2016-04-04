from ctypes import *
from tkinter import ttk


class LEDColorTab(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()
		self.color_values={}
		self.color_values['off']=0
		self.color_values['red']=1
		self.color_values['green']=2
		self.color_values['yellow']=3
		self.color_values['blue']=4
		self.color_values['pink']=5
		self.color_values['blue green']=6
		self.color_values['white']=7


	def initialize(self):
		self.grid()

		self.choice_list=ttk.Combobox(self)
		self.choice_list.config(values=['off','red','green','yellow','blue',
										'pink','blue green','white'])
		self.choice_list.grid(column=0,row=0)

		self.buttonSend=ttk.Button(self,text='Set LED Color',command=self.OnButtonClick_Send)
		self.buttonSend.grid(column=0,row=1)

	def OnButtonClick_Send(self):
		color=self.color_values[self.choice_list.get()]
		self.parent.lib.set_led_color_servo(byref(self.parent.servo),c_uint(color),1)
		pass
