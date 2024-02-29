#ifndef AUTOWIRE
#define AUTOWIRE

#include <Arduino.h>
#include "Wire.h"
#include <math.h>

class autowire
{
    public:
    autowire(const int address);

    void updateData();
    int16_t getAx();
    int16_t getAy();
    int16_t getAz();
    int16_t getGx();
    int16_t getGy();
    int16_t getGz();
    int16_t getTemperature();

    private:

    int16_t Ax, Ay, Az;
    int16_t temperature;
    int16_t Gx, Gy, Gz;
    const int addr;


};

#endif