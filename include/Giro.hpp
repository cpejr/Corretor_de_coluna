#ifndef GIRO
#define GIRO

#include <Arduino.h>
#include "Wire.h"
#include <math.h>

class Giro
    {
        public:
        Giro(int port);

        float getAnglePhi();
        float getAngleTheta();
        float getAnglePsi();
        float getTemperature();

        void printAngles();
        void printTemperature();

        private:

        int pino;

        const int HighAddr = 0x69;

        float AnglePhi;
        float AngleTheta;
        float AnglePsi;
        float Temperature;

    };


    #endif