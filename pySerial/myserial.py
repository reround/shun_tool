#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   myserial.py
@Time    :   2023/06/27 13:12
@Author  :   shun
@Description  :   TODO
'''

import time
import serial
import serial.tools.list_ports


class MySerial(serial.Serial):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.log = open("log.txt", "a")

    def print_comport(self):
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
                

    def write(self, message: str):
        """
        发送信息

        :param str message: 发送的信息
        """
        super().write(message.encode("utf-8"))

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
    ser = MySerial()
    # ser.print_comport()
    ser = MySerial(port="COM1",
                   baudrate=9600,
                   bytesize=serial.EIGHTBITS,
                   parity=serial.PARITY_NONE,
                   stopbits=serial.STOPBITS_TWO,
                   timeout=0.5)
    while True:
        da = ser.receive_save()
        print(da)
        time.sleep(0.5)
        # time.sleep(1)
    # pass
