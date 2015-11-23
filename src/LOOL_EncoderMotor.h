#ifndef LOOL_EncoderMotor_h
#define LOOL_EncoderMotor_h

#include <stdbool.h>
#include "LOOL_Config.h"
#include "LOOL_Port.h"

///@brief Class for Encoder Motor Driver
class LOOL_EncoderMotor: public LOOL_Port{
    public:
        LOOL_EncoderMotor(uint8_t addr,uint8_t slot);
        LOOL_EncoderMotor(uint8_t slot);
        LOOL_EncoderMotor();
        void begin();
        boolean reset();
        boolean move(float angle, float speed);
        boolean moveTo(float angle, float speed);
        boolean runTurns(float turns, float speed);
        boolean runSpeed(float speed);
        boolean runSpeedAndTime(float speed, float time);
        float getCurrentSpeed();
        float getCurrentPosition();
    private:
		void request(byte *writeData, byte *readData, int wlen, int rlen);
        uint8_t _slot;    
		uint8_t _slaveAddress;
};
#endif
