#ifndef LOOL_Buzzer_H
#define LOOL_Buzzer_H

#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"

#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif // LOOL_PORT_DEFINED

#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556
#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278
#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112
///@brief Class for LOOL_Buzzer module
class LOOL_Buzzer : public LOOL_Port
{
public:
#ifdef LOOL_PORT_DEFINED
  LOOL_Buzzer();
  LOOL_Buzzer(uint8_t port);
  LOOL_Buzzer(uint8_t port, uint8_t slot);
#else // LOOL_PORT_DEFINED
  LOOL_Buzzer(int pin);
#endif // LOOL_PORT_DEFINED
  void setpin(int pin);
  void tone(int pin, uint16_t frequency, uint32_t duration);
  void tone(uint16_t frequency, uint32_t duration = 0);
  void noTone(int pin);
  void noTone();
};

#endif
