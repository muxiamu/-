#include<stdio.h>
#include<stdint.h>
#include<unistd.h>
#include<fcntl.h>


int main(void)
{
float hum, tem;
int fn;

fn = open("/home/pi/C_raspi/dht11/log.txt",O_RDONLY);

if(fn==-1) printf("error\n");
read(fn,&hum,sizeof(float));
read(fn,&tem,sizeof(float));
close(fn);

printf("Contenttype:text/html\n\n");
printf("<html>\n");
printf("<head><title>An HTML Page From a CGI</title></h ead>\n");
printf("<body><br>\n");
printf("<h2> Humidity:%.2f%    Temperature:%.2fC </h2>\n",hum,tem);
printf("<hr><p>\n");
printf("</body>\n");
printf("</html>\n");
  
fflush(stdout);
}
