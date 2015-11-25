#include <EEPROM.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*char * tmp;
 int in=0;
  char *p[20];
  char *outer_ptr=NULL;
  char *inner_ptr=NULL;
  char buffer[14]="1,A 0 1,B 1 0";
  char *cmd=buffer;
  char * str;
  str = strtok_r(cmd, " ", &tmp);  
  while((str=strtok_r(0, " ", &tmp))!=NULL)
    cmd=p[in];
    while((p[in]=strtok_r(cmd, " ", &inner_ptr))!=NULL)
    {
      in++;
      cmd=NULL;
    }
    cmd=NULL;
  Serial.println(in);
  for (int j=0; j<in; j++)
{
Serial.println(p[j]);
}*/
char buffer[14]="1 A031 B10";
char *cmd=buffer;
char * tmp;
  char * str;
  str = strtok_r(cmd, " ", &tmp);             
  while((str=strtok_r(0, " ", &tmp))!=NULL)
  {
    if(str[0]=='A')
    {
      Serial.println(str[2]);
      //Serial.println(atof(str+2));
    }
   if(str[0]=='B') 
    {
      Serial.println(str[1]);
      //Serial.println(atof(str+2));
    }
  }
}
