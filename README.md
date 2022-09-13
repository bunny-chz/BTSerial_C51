# BTSerial_C51
C51超声波测距Keil小项目，蓝牙串口发送数据的示例源码
测距数据传送给手机实时显示，此仓库对应的软件： 
https://github.com/bunny-chz/BTSerial

一、硬件上接线:

单片机开发板是郭天祥的TX-1C 51开发板


HC-06蓝牙模块的

TXD→51单片机的RXD（P3^0）

RXD→51单片机的TXD(P3^1)

VCC→51单片机的VCC

GND→51单片机的GND


二、程序说明：

main.c 是发送十六进制码控制的代码
