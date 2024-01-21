#include<stdio.h>
#include<wiringPi.h>
#include<stdint.h>
#include<unistd.h>
#include<fcntl.h>
#include "dht11.h"


int main(void)
{
float hum,h,tem,t;
int fn;


while(1) {
delay(1000);
dht11(&hum, &tem);
  
// printf("%f\t",hum);
// printf("%f\n",tem);

if(hum!=-1) {fn = open("/home/pi/C_raspi/dht11/log.txt",O_RDWR);
if(fn==-1) printf("error\n");
write(fn,&hum,sizeof(float));
write(fn,&tem,sizeof(float));
close(fn);}
sleep(60);}
}
