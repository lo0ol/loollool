#include "LOOL_Smart.h"
LOOL_Buzzer Buzzer(3);
void setup() {
  Buzzer.tone(NTD1, 300); 
  delay(300);
  Buzzer.tone(NTD2, 300);
  delay(300);
  Buzzer.tone(NTD3, 300);
  delay(300);
  Buzzer.noTone();
}

void loop() {

}
