/*
 * 可以這樣設置發送的信息：  uint8_t bytes[8] = {0x55, 0X00, 0x84, 0x84, 0x44, 0x35, 0x66, 0xAA};
 * int 轉 uint8_t ：
 *        bytes[3] = (val >> 8) & 0xFF;
 *        bytes[4] = val & 0xFF;
 */
#ifndef SERIAL_H

#define SERIAL_H

#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

using namespace std;

class Serial
{
public:
    string port;
    HANDLE hSerial;

    int open(LPCSTR);
    int send(LPCVOID);
    char* read(int);
};

int Serial::open(LPCSTR port)
{
    // 打开串口
    this->hSerial = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (this->hSerial == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to open serial port." << std::endl;
        return 1;
    }

    // 配置串口参数
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(this->hSerial, &dcbSerialParams)) {
        std::cout << "Failed to get serial port parameters." << std::endl;
        CloseHandle(this->hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;  // 设置波特率为9600
    dcbSerialParams.ByteSize = 8;         // 数据位为8位
    dcbSerialParams.Parity = NOPARITY;    // 无奇偶校验
    dcbSerialParams.StopBits = ONESTOPBIT;// 1位停止位
    if (!SetCommState(this->hSerial, &dcbSerialParams)) {
        std::cout << "Failed to set serial port parameters." << std::endl;
        CloseHandle(this->hSerial);
        return 1;
    }

    // this->port = port;
    cout << "new com" << endl;
    return 0;
};

int Serial::send(LPCVOID sendData)
{
    DWORD bytesWritten;

    if (!WriteFile(this->hSerial, sendData, sizeof(sendData), &bytesWritten, NULL)) {
        std::cout << "Failed to write to serial port." << std::endl;
        CloseHandle(this->hSerial);
        return 1; 
    }
    return 0;
}

char* Serial::read(int num)
{
    // 接收数据
    char* recvData = new char[num];
    DWORD bytesRead;
    if (!ReadFile(this->hSerial, recvData, num, &bytesRead, NULL)) {
        std::cout << "Failed to read from serial port." << std::endl;
        CloseHandle(this->hSerial);
        return recvData;
    }
    return recvData;
}


#endif
