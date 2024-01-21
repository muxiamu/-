#include<stdio.h>
#include<wiringPi.h>
#include<stdlib.h>

#define LEDpin1 15
#define LEDpin2 16



int main(void)
{
    unsigned int i;
    if (wiringPiSetup() == -1)
    {
        printf("setup error\n");
        exit(-1);
    }

    pinMode(LEDpin1,OUTPUT);
    pinMode(LEDpin2,OUTPUT);

    while(1){
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,LOW);
    delay(100);
    digitalWrite(LEDpin1,LOW);
    digitalWrite(LEDpin2,HIGH);
    delay(100);
}
}
