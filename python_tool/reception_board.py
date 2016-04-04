from tkinter import ttk


class ReceivedFrameZone(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.displayText='ee'
		self.initialize()

	def initialize(self):
		self.grid()
		displayZone=ttk.Label(self,text=self.displayText)
		displayZone.grid(column=0,row=0)

	def setText(self,text):
		self.displayText=text