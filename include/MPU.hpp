#ifndef MPU_
#define MPU_

#include <Arduino.h>
#include "Wire.h"
#include <math.h>

class MPU
    {
        public:
        MPU(int port, int offset_Phi, int offset_Theta, int offset_Psi);

        float getAnglePhi();
        float getAngleTheta();
        float getAnglePsi();
        float getTemperature();

        void printAngles();
        void printTemperature();
        void auto_offset();

        private:

        int pino;
        int offsetPhi;
        int offsetTheta;
        int offsetPsi;

        const int HighAddr = 0x69;

        float AnglePhi;
        float AngleTheta;
        float AnglePsi;
        float Temperature;

    };


    #endif