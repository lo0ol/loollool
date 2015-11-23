#include "LOOL_Buzzer.h"

uint8_t buzzer_pin;
#ifdef LOOL_PORT_DEFINED
LOOL_Buzzer::LOOL_Buzzer()
{
  buzzer_pin = 8;
}

LOOL_Buzzer::LOOL_Buzzer(uint8_t port):LOOL_Port(port)
{
  buzzer_pin = s2;
}

LOOL_Buzzer::LOOL_Buzzer(uint8_t port, uint8_t slot):LOOL_Port(port)
{
  buzzer_pin = s2;
  if(slot == SLOT2)
  {   
    buzzer_pin = s2;
  }
  else
  {
    buzzer_pin = s1;
  }
}
#else // LOOL_PORT_DEFINED
LOOL_Buzzer::LOOL_Buzzer(int pin)
{
  buzzer_pin = pin;
}
#endif // LOOL_PORT_DEFINED

void LOOL_Buzzer::setpin(int pin)
{
  buzzer_pin = pin;
}

// frequency (in hertz) and duration (in milliseconds).
void LOOL_Buzzer::tone(int pin, uint16_t frequency, uint32_t duration)
{
  buzzer_pin = pin;
  int period = 1000000L / frequency;
  int pulse = period / 2;
  for (long i = 0; i < duration * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
  }
}

// frequency (in hertz) and duration (in milliseconds).
void LOOL_Buzzer::tone(uint16_t frequency, uint32_t duration)
{
  int period = 1000000L / frequency;
  int pulse = period / 2;
  for (long i = 0; i < duration * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
  }
}

void LOOL_Buzzer::noTone(int pin)
{
  buzzer_pin = pin;
  digitalWrite(buzzer_pin, LOW);
}

void LOOL_Buzzer::noTone()
{
  digitalWrite(buzzer_pin, LOW);
}