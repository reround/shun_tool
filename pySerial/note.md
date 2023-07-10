
# 1 创建、打开串口

在使用 serial.Serial() 创建串口实例时，可以传入的参数很多，常用的参数如下（默认值用括号）：

```
port - 串口设备名或 (None)。
baudrate - 波特率，可以是50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, (9600), 19200, 38400, 57600, 115200, 230400, 460800, 500000, 576000, 921600, 1000000, 1152000, 1500000, 2000000, 2500000, 3000000, 3500000, 4000000。
bytesize - 数据位，可取值为：FIVEBITS, SIXBITS, SEVENBITS, (EIGHTBITS)。
parity - 校验位，可取值为：(PARITY_NONE), PARITY_EVEN, PARITY_ODD, PARITY_MARK, PARITY_SPACE。
stopbits - 停止位，可取值为：(STOPBITS_ONE),       STOPBITS_ONE_POINT_FIVE, STOPBITS_TOW。
xonxoff - 软件流控，可取值为 True, (False)。
rtscts - 硬件（RTS/CTS）流控，可取值为 True, (False)。
dsr/dtr - 硬件（DSR/DTR）流控，可取值为 True, (False)。
timeout - 读超时时间，可取值为 (None), 0 或者其他具体数值（支持小数）。当设置为 None 时，表示阻塞式读取，一直读到期望的所有数据才返回；当设置为 0 时，表示非阻塞式读取，无论读取到多少数据都立即返回；当设置为其他数值时，表示设置具体的超时时间（以秒为单位），如果在该时间内没有读取到所有数据，则直接返回。
write_timeout: 写超时时间，可取值为 (None), 0 或者其他具体数值（支持小数）。参数值起到的效果参考 timeout 参数。
```

# 2 关闭串口

直接调用 close() 方法即可。

# 3 发送数据 write()

关于write() 方法，需要了解如下几点：
① write() 方法只能发送 bytes 类型的数据，所以需要对字符串进行 encode 编码。
② write() 方法执行完成后，会将发送的字节数作为返回值。
③ 在打开串口时，可以为 write() 方法配置超时时间

# 4 读取数据 read()

关于 read() 方法，需要了解如下几点：
① read() 方法默认一次读取一个字节，可以通过传入参数指定每次读取的字节数。
② read() 方法会将读取的内容作为返回值，类型为 bytes。
③ 在打开串口时，可以为 read() 方法配置超时时间。
