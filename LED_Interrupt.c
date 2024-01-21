#include<stdio.h>
#include<wiringPi.h>

#define LEDpin 15       // D1
#define SWpin 23        // SW1
int flag = 0;   // interrupt flag


// interrupt function
void blank(void) {flag = 1;}

int main(void)
{
    wiringPiSetup();
    pinMode(LEDpin, OUTPUT);
    pinMode(SWpin, INPUT);
    wiringPiISR(SWpin, INT_EDGE_RISING, &blank);

    while(1)
    {
    if(flag==1) {if(digitalRead(SWpin)==HIGH) digitalWrite(LEDpin, HIGH);else flag = 0;}
    else digitalWrite(LEDpin, LOW);
    }
}
