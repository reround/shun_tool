#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   server.py
@Time    :   2023/06/27 10:13
@Author  :   shun
@Description  :   串口 server
'''

import serial
import serial.tools.list_ports


def print_comport():
    """
    打印串口信息
    """
    ports_list = list(serial.tools.list_ports.comports())
    if len(ports_list) <= 0:
        print("无串口设备。")
    else:
        print("可用串口设备：")
        for comport in ports_list:
            print(list(comport)[0], list(comport)[1])


try:
    ser = serial.Serial(port="COM2",
                        baudrate=9600,
                        bytesize=serial.SEVENBITS,
                        parity=serial.PARITY_NONE,
                        stopbits=serial.STOPBITS_TWO,
                        timeout=0.5)
    if ser.isOpen():
        print("串口打开成功。")
        print(ser.name)
    else:
        print("打开串口失败。")

    w_len = ser.write("hello".encode('utf-8'))
    print(w_len)
    
    print(ser.rs485_mode)

    ser.close()
except Exception as e:
    print(e)

if __name__ == '__main__':
    pass