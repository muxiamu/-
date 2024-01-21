#include<stdio.h>
#include<stdint.h>
#include<unistd.h>
#include<fcntl.h>
#include<wiringPi.h>

#define D1pin 15
#define D2pin 16


int main(void)
{
float hum, tem;
int fn;
char *d1 = "ukn";
char *d2 = "ukn";

if(wiringPiSetup()==-1) printf("error\n");
if(digitalRead(D1pin)==HIGH) d1 = "on";else d1 = "off";
if(digitalRead(D2pin)==HIGH) d2 = "on";else d2 = "off";


fn = open("/home/pi/C_raspi/dht11/log.txt",O_RDONLY);

if(fn==-1) printf("error\n");
read(fn,&hum,sizeof(float));
read(fn,&tem,sizeof(float));
close(fn);


printf("Contenttype:text/html\n\n");
printf("<html>\n");
printf("<head>\n");
printf("<meta charset='utf-8'>\n");
printf("<meta http-equiv='refresh' content='5'>\n");
printf("<title>thttpd远程控制</title>\n");
printf("</head>\n");
printf("<body>\n");
        printf("<h1 align='center'>网页温、湿度显示</h1>\n");
        printf("<h2 align='center'><br>湿度:%.2f% &emsp;&emsp; 温度:%.2f℃</h2>\n",hum,tem);
        printf("<br><hr><br>\n");
        printf("<h1 align='center'>网页控制LED亮灭</h2>\n");
        printf("<h2 align='center'><br>D1:%s &emsp;&emsp; D2:%s</h2>\n",d1,d2);
        printf("<form action='led.cgi' method='get'>\n");
        printf("<h2 align='center'><input type='submit' value='on'>");
        printf("&emsp;&emsp;&emsp;&emsp; <input type='submit' value='on'>\n");
        printf("<br><input type='submit' value='off'>");
        printf("&emsp;&emsp;&emsp;&emsp; <input type='submit' value='off'></h2>\n");
        printf("</form>\n");
printf("</body>\n");
printf("</html>\n");
  
fflush(stdout);
}
