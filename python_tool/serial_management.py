from tkinter import ttk
import serial
from serial.tools.list_ports import comports
from ctypes import create_string_buffer,memmove


class SerialHandler():
	def __init__(self,parent):
		self.parent=parent
		self.connection_established=False
		self.serial_instance=serial.Serial()

	def is_connected(self):
		return self.connection_established

	def set_parameters(self,port,baudrate):
		self.serial_instance.port = port
		self.serial_instance.baudrate = baudrate
		self.serial_instance.parity=serial.PARITY_NONE
		self.serial_instance.stopbits=serial.STOPBITS_ONE
		self.serial_instance.bytesize=serial.EIGHTBITS
		# self.serial_instance.write_timeout=0

	def connect(self):
		self.serial_instance.open()
		self.connection_established=True

	def disconnect(self):
		self.serial_instance.close()
		self.connection_established=False

	def send(self,buff,buff_len):
		frame=create_string_buffer(buff_len)
		memmove(frame,buff,buff_len)
		print(buff_len)
		print(bytes(frame))
		print('in send')
		if self.serial_instance.isOpen():
			r=self.serial_instance.write(bytes(frame))
		else:
			print('serial port is not open')


class SerialFrame(ttk.Frame):
	def __init__(self,parent):
		ttk.Frame.__init__(self, parent)
		self.parent=parent
		self.initialize()
		self.connected=False
	
	def initialize(self):
		self.grid()

		#Button refresh ports list
		buttonRefresh=ttk.Button(self,text='Refresh ports', command = self.OnButtonClick_Refresh)
		buttonRefresh.grid(column=2,row=0)

		#Button connection/disconnection
		self.buttonToggleConnect=ttk.Button(self,text='Connect',command=self.OnButtonClick_ToggleConnect)
		self.buttonToggleConnect.grid(column=2,row=1)

		#list of ports
		self.list_ports=ttk.Combobox(self,state='readonly')
		self.list_ports.grid(column=1,row=0,sticky='NSEW')
		self.refresh_ports()

		#baudrate selection
		self.list_baudrate=ttk.Combobox(self,state='readonly')
		self.list_baudrate['values']=('1000000','115200','57600','9600')
		self.list_baudrate.current(0)
		self.list_baudrate.grid(column=1,row=1,sticky='NSEW')

		#windows management
		self.columnconfigure(0, weight = 0)
		self.columnconfigure(1, weight = 1)
		self.columnconfigure(2, weight = 0)

	def refresh_ports(self):
		tmp_list = []
		for device, description, hwdID in sorted(serial.tools.list_ports.comports()):
			tmp_list.append(device)
		self.list_ports['values']=tuple(tmp_list)

		if len(self.list_ports['values'])!=0:
			self.list_ports.current(0)
			self.list_ports.config(state='readonly')
			self.buttonToggleConnect.config(state='enabled')
		else:
			self.list_ports.config(state='disabled')
			self.buttonToggleConnect.config(state='disabled')

	def OnButtonClick_ToggleConnect(self):
		if(not self.connected):
			port=self.list_ports.get()
			baudrate=self.list_baudrate.get()
			self.parent.serial.set_parameters(port,baudrate)
			self.parent.serial.connect()
		else:
			self.parent.serial.disconnect()

		# state actualisation
		self.connected=self.parent.serial.is_connected()

		# text changement if everything is ok
		if(self.connected):
			self.buttonToggleConnect.config(text='Disconnect')
		else:
			self.buttonToggleConnect.config(text='Connect')

	def OnButtonClick_Refresh(self):
		self.refresh_ports()
