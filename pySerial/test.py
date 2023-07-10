#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   test.py
@Time    :   2023/06/30 14:25
@Author  :   shun
@Description  :   TODO
'''

import time
import serial
import serial.rs485

ser = serial.Serial(port="COM1",
                   baudrate=9600,
                   bytesize=serial.EIGHTBITS,
                   parity=serial.PARITY_NONE,
                   stopbits=serial.STOPBITS_TWO,
                   timeout=0.5)
ser.rs485_mode = serial.rs485.RS485Settings()
ser.write(b'hello')
time.sleep(1)
data = ser.readline()

print(data)

if __name__ == '__main__':
    pass