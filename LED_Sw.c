#include<stdio.h>
#include<wiringPi.h>

int main(void)
{
    if(wiringPiSetup()==-1) printf("error\n");
    else printf("ok\n");

    int SWpin = 23;     // SW1
    int LEDpin = 15;    // D1

  
    while(1)
    {
        pinMode(SWpin, INPUT);
        pinMode(LEDpin, OUTPUT);

        // press the SW1 to HIGH
        if(digitalRead(SWpin)==HIGH) {digitalWrite(LEDpin,HIGH);}
        else {digitalWrite(LEDpin,LOW);}
    }

}

