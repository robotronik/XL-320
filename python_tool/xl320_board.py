import tkinter
import ctypes
from ctypes import *
from tkinter import ttk
from tabs.ID import IDTab
from tabs.alarm import AlarmTab
from tabs.custom import CustomTab
from tabs.led import LEDColorTab
from tabs.mode import ModeTab
from tabs.position import PositionTab
from tabs.reset import ResetTab
from tabs.speed import SpeedTab
from tabs.torque import TorqueTab
import serial_management


class XL_320_servo(ctypes.Structure):
	pass
class XL_320_group(ctypes.Structure):
	pass
class XL_320_socket(ctypes.Structure):
	pass


SENDFUNC = CFUNCTYPE(None, POINTER(c_char), c_int)

XL_320_servo._fields_ = [('socket_ptr', POINTER(XL_320_socket)),
						('ID', c_ubyte)]

XL_320_group._fields_ = [('socket_ptr_list', POINTER(XL_320_socket)*253),
						('nbr_socket', c_ubyte),
						('servo_ptr_list', POINTER(XL_320_servo)*253),
						('nbr_servo', c_ubyte)]

XL_320_socket._fields_ = [('send_function',SENDFUNC),
						('group',XL_320_group)]






class FrameGenerationZone(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.lib=cdll.LoadLibrary("./libxl320.so")
		self.socket=XL_320_socket()
		self.send_serial_py_test_c=SENDFUNC(lambda x,y : self.send_serial_py(x,y))
		self.send_serial_py_test_c.argtypes = (c_char_p, c_int)
		self.send_serial_py_test_c.restype = None
		self.lib.init_socket(byref(self.socket),self.send_serial_py_test_c)
		print(self.socket.send_function)
		self.servo=XL_320_servo()
		#254 correspond to broadcast ID
		self.lib.init_servo(byref(self.servo),c_uint(254),byref(self.socket))
		print(self.socket.group.nbr_servo)
		self.initialize()

	def initialize(self):
		self.grid
		self.notebook=ttk.Notebook(self)
		my_IDTab= IDTab(self)
		my_ResetTab = ResetTab(self)
		my_AlarmTab = AlarmTab(self)
		my_LEDColorTab = LEDColorTab(self)
		my_ModeTab = ModeTab(self)
		my_SpeedTab = SpeedTab(self)
		my_PositionTab = PositionTab(self)
		my_TorqueTab = TorqueTab(self)
		my_CustomTab = CustomTab(self)
		self.notebook.add(my_IDTab,text='ID')
		self.notebook.add(my_ResetTab,text='Reset')
		self.notebook.add(my_AlarmTab,text='Alarm')
		self.notebook.add(my_LEDColorTab,text='LED Color')
		self.notebook.add(my_ModeTab,text='Mode')
		self.notebook.add(my_SpeedTab,text='Speed')
		self.notebook.add(my_PositionTab,text='Position')
		self.notebook.add(my_TorqueTab,text='Torque')
		self.notebook.add(my_CustomTab,text='Custom Frame')
		self.notebook.grid(column=0,row=0)

	def send_serial_py(self,buff,buff_len):
		self.parent.serial.send(buff,buff_len)
