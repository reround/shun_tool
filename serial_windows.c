#include <stdio.h>
#include <windows.h>
#include <string.h>
 
//开启DEBUG打印
#define LOGD(...) printf(__VA_ARGS__)
//开启ERROR打印
#define LOGE(...) printf(__VA_ARGS__)

 
//缓冲区大小
#define BUF_SIZE    2048
#define EXIT_STR    "exit"
#define I_EXIT      "I exit.\r\n"
#define I_RECEIVE   "I receive.\r\n"
 
//打开串口
HANDLE OpenSerial(const char *com, //串口名称，如COM1，COM2
    int baud,       //波特率：常用取值：CBR_9600、CBR_19200、CBR_38400、CBR_115200、CBR_230400、CBR_460800
    int byteSize,   //数位大小：可取值7、8；
    int parity,     //校验方式：可取值NOPARITY、ODDPARITY、EVENPARITY、MARKPARITY、SPACEPARITY
    int stopBits)   //停止位：ONESTOPBIT、ONE5STOPBITS、TWOSTOPBITS；
{    
    DCB dcb;
    BOOL b = FALSE;
	COMMTIMEOUTS CommTimeouts;	
    HANDLE comHandle = INVALID_HANDLE_VALUE;
 
    //打开串口
	comHandle = CreateFile(com,            //串口名称
		GENERIC_READ | GENERIC_WRITE,      //可读、可写   				 
		0,            // No Sharing                               
		NULL,         // No Security                              
		OPEN_EXISTING,// Open existing port only                     
		FILE_ATTRIBUTE_NORMAL,            // Non Overlapped I/O                           
		NULL);        // Null for Comm Devices
 
	if (INVALID_HANDLE_VALUE == comHandle) {
        LOGE("CreateFile fail\r\n");
        return comHandle;
    }
 
    // 设置读写缓存大小
	b = SetupComm(comHandle, BUF_SIZE, BUF_SIZE);
    if (!b) {
        LOGE("SetupComm fail\r\n");
    }
 
    //设定读写超时
	CommTimeouts.ReadIntervalTimeout = MAXDWORD;//读间隔超时
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;//读时间系数
	CommTimeouts.ReadTotalTimeoutConstant = 0;//读时间常量
	CommTimeouts.WriteTotalTimeoutMultiplier = 1;//写时间系数
	CommTimeouts.WriteTotalTimeoutConstant = 1;//写时间常量
	b = SetCommTimeouts(comHandle, &CommTimeouts); //设置超时
    if (!b) {
        LOGE("SetCommTimeouts fail\r\n");
    }
 
    //设置串口状态属性
    GetCommState(comHandle, &dcb);//获取当前
	dcb.BaudRate = baud; //波特率
	dcb.ByteSize = byteSize; //每个字节有位数
	dcb.Parity   = parity; //无奇偶校验位
	dcb.StopBits = stopBits; //一个停止位
	b = SetCommState(comHandle, &dcb);//设置
    if (!b) {
        LOGE("SetCommState fail\r\n");
    }
 
    return comHandle;
}
 
int main(int argc, char *argv[])
{
    BOOL b = FALSE;
    DWORD wRLen = 0;
    DWORD wWLen = 0;
    char buf[BUF_SIZE] = {0};
	HANDLE comHandle = INVALID_HANDLE_VALUE;//串口句柄    	
 
    //打开串口
    const char *com = "COM2";
	comHandle = OpenSerial(com, CBR_9600, 8, NOPARITY, ONESTOPBIT);
	if (INVALID_HANDLE_VALUE == comHandle) {
		LOGE("OpenSerial COM2 fail!\r\n");
		return -1;
	}
	LOGD("Open COM2 Successfully!\r\n");
 
    //循环接收消息，收到消息后将消息内容打印并回复I_RECEIVE, 如果收到EXIT_STR就回复EXIT_STR并退出循环
	while (1) {
		wRLen = 0;
        //读串口消息
		b = ReadFile(comHandle, buf, sizeof(buf)-1, &wRLen, NULL);
		if (b && 0 < wRLen) {//读成功并且数据大小大于0
            buf[wRLen] = '\0';
            LOGD("[RECV]%s\r\n", buf);//打印收到的数据
            if (0 == strncmp(buf, EXIT_STR, strlen(EXIT_STR))) {
                //回复
                b = WriteFile(comHandle, TEXT(I_EXIT), strlen(I_EXIT), &wWLen, NULL);
                if (!b) {
                    LOGE("WriteFile fail\r\n");
                }
                break;
            }
            //回复
			b = WriteFile(comHandle, TEXT(I_RECEIVE), strlen(I_RECEIVE), &wWLen, NULL);
            if (!b) {
                LOGE("WriteFile fail\r\n");
            }
		}
	}
 
    //关闭串口
	b = CloseHandle(comHandle);
    if (!b) {
        LOGE("CloseHandle fail\r\n");
    }
 
    LOGD("Program Exit.\r\n");
    return 0;
}
