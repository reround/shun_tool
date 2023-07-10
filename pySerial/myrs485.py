#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   myrs485.py
@Time    :   2023/06/30 15:08
@Author  :   shun
@Description  :   TODO
'''

import time
import serial
import serial.rs485

class MyRS485(serial.rs485):
    """
    RS485 子类
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.log = open("log.txt", "a")
    
    def receive_save(self) -> str:
        """
        接收信息并保存

        :return str: 接收到的信息
        """
        len = self.in_waiting
        if len != 0:
            data = self.read(len)
            str_data = str(data)
            self.log.writelines(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) + " " + str_data + "\n")
            return(str_data)


if __name__ == '__main__':
    # ser = MySerial()
    # ser.print_comport()
    ser = MyRS485(port="COM1",
                   baudrate=9600,
                   bytesize=serial.EIGHTBITS,
                   parity=serial.PARITY_NONE,
                   stopbits=serial.STOPBITS_TWO,
                   timeout=0.5)
    while True:
        da = ser.receive_save()
        print(da)
        time.sleep(0.5)