#ifndef COMPARE_
#define COMPARE_

#include <Timer.h>
#include "MPU.hpp"

class Compare
{
  public:
    Compare(MPU& Ref, MPU& Point, int ToleranceTimes_, int ToleranceAngle_);

    bool misaligned();
    void reseter();

    // Ajusta os valores de referencia para cada angulo
    void calibrate();

    MPU& Ref;
    MPU& Point;

    int DPhi, DTheta, DPsi;
    int ToleranceTimes;
    int ToleranceAngle;

    int referencePhi;
    int referenceTheta;
    int referencePsi;
};

#endif
