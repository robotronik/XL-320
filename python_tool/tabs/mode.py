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
		self.torque_is_enable=1

	def initialize(self):
		self.grid()

		# Supposes the servo is in Torque enable state at program startup
		self.buttonTorque=ttk.Button(self,text='Disable torque',command=self.OnButtonClick_TorqueState)
		self.buttonTorque.grid(column=0,row=0)

		self.choice_list=ttk.Combobox(self)
		self.choice_list.config(values=['Wheel','Join'])
		self.choice_list.grid(column=0,row=1)

		self.buttonSend=ttk.Button(self,text='Set Mode',command=self.OnButtonClick_Send)
		self.buttonSend.grid(column=0,row=2)

	def OnButtonClick_Send(self):
		mode=self.mode_values[self.choice_list.get()]
		self.parent.lib.set_control_mode_servo(byref(self.parent.servo),c_uint(mode),c_uint(1))
		pass

	def OnButtonClick_TorqueState(self):
		if self.torque_is_enable:
			self.parent.lib.disable_power_servo(byref(self.parent.servo),c_uint(1))
			self.buttonTorque.config(text='Enable torque')
			self.torque_is_enable=0
		else:
			self.parent.lib.enable_power_servo(byref(self.parent.servo),c_uint(1))
			self.buttonTorque.config(text='Disable torque')
			self.torque_is_enable=1