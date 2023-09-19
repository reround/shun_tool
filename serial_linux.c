
/*

Linux 下 C 語言串口的读写。

*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

int main()
{
    int fd;
    char recvbuff[128]; 
    int count=0;
    char buffer[]="Hello,word!\r\n";
    struct termios uart_cfg;
    fd=open("/dev/ttyS3",O_RDWR|O_NONBLOCK|O_NOCTTY);//打开串口
    if(fd<0)
    {
        perror("Failed to open serial:");
        return -1;
    }
    fcntl(fd,F_SETFL,0);   // 设置串口阻塞办法
    //cfmakeraw(&uart_cfg);// 将终端设置为原始模式 8n1没有流控
    cfsetspeed(&uart_cfg,B9600);    // 设置波特率
   // uart_cfg.c_cflag|=CLOCAL|CREAD;
//设置数据位
uart_cfg.c_cflag &= ~CSIZE; /* 用数据位掩码清空数据位设置 */
uart_cfg.c_cflag |= CS8;//数据位为8
//设置奇偶校验位
//奇校
//uart_cfg.c_cflag |= (PARODD | PARENB); 
//uart_cfg.c_iflag |= INPCK;
//偶校
uart_cfg.c_cflag |= PARENB;
uart_cfg.c_cflag &= ~PARODD;   /* 清除奇校验标志，则配置为偶校验*/
uart_cfg.c_iflag |= INPCK;
//无校
//uart_cfg.c_cflag &= ~PARENB;
//设置停止位
//uart_cfg.c_cflag &=  ~CSTOPB;    /* 将停止位设置为一个比特 */
uart_cfg.c_cflag |=  CSTOPB;    /* 将停止位设置为两个比特 */
    tcflush(fd,TCIOFLUSH);/* 用于清空输入/输出缓冲区*/
    tcsetattr(fd,TCSANOW,&uart_cfg);//使新的设置生效
    while(1)
    {
        write(fd,buffer,strlen(buffer));    //往串口发送消息    
        sleep(1);
        count=read(fd,recvbuff,127);   //读取串口接收数据
        if(count>0)
        {
            recvbuff[count]=0;
            printf("STR:%s\r\n",recvbuff);
        }
    }
    close(fd);
    return 0;
}
