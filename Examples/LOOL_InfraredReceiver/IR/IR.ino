#include <LOOL_IR.h>
double lastTime = 0.0;
double lastIRTime = 0.0;
double currentTime = 0.0;
int irDelay = 0;
int irIndex = 0;
char irRead = 0;
boolean irReady = false;
String irBuffer = "";
boolean irPressed = false;

LOOL_IR ir;
void setup() {
  Serial.begin(9600);
    ir.begin(); 
}
void get_ir_command()
{
  static long time = millis();
    currentTime = millis()/1000.0-lastTime;//
  if (ir.decode())
  {
    irRead = ((ir.value>>8)>>8)&0xff;
    lastIRTime = millis()/1000.0;
    irPressed = true;
    if(irRead==0xa||irRead==0xd){
      irIndex = 0;
      irReady = true;
    }else{
      irBuffer+=irRead; 
      irIndex++;
      if(irIndex>64){
        irIndex = 0;
        irBuffer = "";
      }
    }
    irDelay = 0;
    uint32_t value = ir.value;
    time = millis();
    Serial.println(value >> 16 & 0xff);
  }
  else{                    
    irDelay++;
    if(irRead>0){
    if(irDelay>5000){
      irRead = 0;
      irDelay = 0;
     }
   }
  }                          
}
void loop() {
 get_ir_command();
}

