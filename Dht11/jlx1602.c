#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/ioctl.h>
#include<linux/i2c-dev.h>
#include "jlx1602.h"

int jlx1602_init(const char * dev) //初始化函数
{
int fn;
char buf[5];
fn=open(dev,O_RDWR);
if(fn<0){

//printf("Can not open device\r\n");

return(fn);
}
if(ioctl(fn,I2C_SLAVE,0x3c)<0){
  
//printf("Can not control device\r\n");

return(-2);
}

buf[0]=0x00; //控制字
buf[1]=0x38; //N=1 2行
buf[2]=0x0c; //D=1 C=0 B=0
buf[3]=0x01; //Clear
buf[4]=0x06; //I/D=1，光标增

if(write(fn,buf,5)<5)
{
close(fn);
return -4;
}
return fn;
}


int jlx1602_puts(int fn,unsigned char line, unsigned char col, char * strs)   //字符串输出函数
{
int i,n;
char buf[20];
n=strlen(strs);
  
if(n+col-1>16) n=16-col+1;
buf[0]=0x80; //控制字
buf[1]=0x80+(line-1)*0x40+(col-1); //设定DDRAM
buf[2]=0x40; //控制字
  
for(i=0;i<n;i++)
buf[3+i]=strs[i];
return write(fn,buf,n+3);
}


int jlx1602_close(int fn)     //关闭设备
{
return close(fn);
}
