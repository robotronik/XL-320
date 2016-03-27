#!/usr/bin/python
# -*- coding: utf8 -*-
import serial
import sys

try:
	ser = serial.Serial(port='/dev/ttyUSB0', baudrate=1000000,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)
	header=b'\xFF\xFF\xFD\x00'
	ID=b'\xFE'
	pack_len=b'\x06\x00'
	instruct=b'\x03'
	led_adrr=b'\x25\x00'
	params=led_adrr+b'\x02'
	crc=b'\xD5\x97'
	to_write=header+ID+pack_len+instruct+params+crc
	#to_write=b'\xFF\xFF\xFD\x00\x01\x07\x00\x02\x00\x00\x00\x02\x00\x00\x26\xF0'
	ser.write(bytes(to_write))
	while True:
		print(ser.read(1))
except:
	print("Unexpected exception thrown : ",  sys.exc_info())
finally:
	ser.close()