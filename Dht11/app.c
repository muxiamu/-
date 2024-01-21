#include<stdio.h>
#include<wiringPi.h>
#include<stdlib.h>
#include<unistd.h>
#include "jlx1602.h"
#include "dht11.h"


int main(void)
{
float hum, tem;
char h[16];
char t[16];
int fn;

fn = jlx1602_init("/dev/i2c-0");
if(fn<0) exit(-1);
sleep(1);

while(1) 
{
delay(1000);
dht11(&hum, &tem);
printf("%f,%f\n\n",hum,tem);
if(hum!=-1) {sprintf(h, "Humidity:%.2f",hum);sprintf(t, "Temp:%.2f",tem);}
else {sprintf(h, "Humidity:error");sprintf(t, "Temp:error");}


jlx1602_puts(fn, 1, 1, h);
jlx1602_puts(fn, 2, 1, t);
sleep(60);
}
}
