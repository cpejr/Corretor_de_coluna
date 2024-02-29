#ifndef COMPARE_
#define COMPARE_

#include <Timer.h>
#include "MPU.hpp"

class Compare

{
    public:
        Compare(MPU& Ref, MPU& Point,int ToleranceTimes_, int ToleranceAngle_);
        bool unaligned();
        void reseter();
        int DPhi, DTheta, DPsi;
        int ToleranceTimes;
        int ToleranceAngle;
        MPU& Ref;
        MPU& Point;
};

#endif