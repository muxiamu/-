#include<stdio.h>
#include<wiringPi.h>
#include<stdint.h>
#include "dht11.h"

float epochs = 0.0;
float rate = 0.0;


// int main(void)
// {while(1) {delay(1000);dht11();epochs += 1;delay(5000);printf("错误率:%.3f%\n\n",rate*100.0/epochs);}}


float getIntValue(int i, int input)
{
    int n;
    float output;
    if(input==1) output = 1.0; else output = 0.0;
    for(n=0;n<7-i;n++) {output = output * 2.0;}
    return output;
}


float getDecValue(int i, int input)
{
    int n;
    float output;
    if(input==1) output = 1.0;else output = 0.0;
    for(n=0;n<i+1;n++) {output = output * 0.5;}
    return output;
}


void dht11(float *H, float *T)
{
    int DHTpin = 7;
    int flag = 0;
    uint8_t state = HIGH;

    if(wiringPiSetup()==-1) printf("error\n");
    // else printf("Let's go!\n");
  
    pinMode(DHTpin, INPUT);
  
    // if(digitalRead(DHTpin)==HIGH) printf("DHT11 is ready\n");
  
    // call dht11
    pinMode(DHTpin, OUTPUT);
    digitalWrite(DHTpin, LOW);
    delay(20);
    digitalWrite(DHTpin, HIGH);


    // respond to calls
    pinMode(DHTpin, INPUT);

    int i, t[84];
  
    for(i=0;i<10000;i++)
    {
// flag += 1 when the level flips
if(state==digitalRead(DHTpin)) {state = state;flag = flag;}
else
{
state = digitalRead(DHTpin);
t[flag] = i; // time when flips
flag += 1;
}
delayMicroseconds(1);
    }
  
    // printf("The num of flips : %d\n",flag);

    int dt, check = 0;
    int data[40];
    float hum, tem = 0.0;
    int a, b, c, d, e;
    a = b = c = d = e = 0x00;
    for(i=4;i<=82;i+=2) {dt = t[i] + t[i-2] - 2 * t[i-1];if(dt>=0) data[i/2 - 2] = 1;else data[i/2 - 2] = 0;} // data[] = 0x00 00 00 00 00
    for(i=0;i<40;i++)
{

if((i<8)) {hum += getIntValue(i, data[i]);a = a<<1;a += data[i];}
else if((i>=8)&(i<16)) {hum += getDecValue(i-8, data[i]);b = b<<1;b += data[i];}
else if((i>=16)&(i<24)) {tem += getIntValue(i-16, data[i]);c = c<<1;c += data[i];}
else if((i>=24)&(i<32)) {tem+= getDecValue(i-24, data[i]);d = d<<1;d += data[i];}
else {e = e<<1;e += data[i];}
  
if(i==39)
{if(a+b+c+d==e) {*H = hum;*T = tem;} else {*H = -1;*T = -1;rate+=1;}}
}
}
