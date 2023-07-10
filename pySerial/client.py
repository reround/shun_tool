#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   client.py
@Time    :   2023/06/27 10:13
@Author  :   shun
@Description  :   串口 client
'''
import time
import serial
from myserial import MySerial

ser = MySerial(port="COM1",
               baudrate=9600,
               bytesize=serial.SEVENBITS,
               parity=serial.PARITY_NONE,
               stopbits=serial.STOPBITS_TWO,
               timeout=0.5)
while True:
    if ser.in_waiting:
        data = ser.read()
        print(data)
    else:
        time.sleep(1)
if __name__ == '__main__':
    pass