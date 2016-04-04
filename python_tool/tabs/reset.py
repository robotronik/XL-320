from ctypes import *
from tkinter import ttk

class ResetTab(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()

	def initialize(self):
		self.grid()
		self.buttonReset=ttk.Button(self,text='Reset',command=self.OnButtonClick_Reset)
		self.buttonReset.grid(column=0,row=0)

	def OnButtonClick_Reset(self):
		# libxl320=cdll.LoadLibrary("./libxl320.so")
		pass
