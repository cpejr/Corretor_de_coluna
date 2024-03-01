#include "Compare.hpp"

Compare::Compare(MPU& Ref_,
                 MPU& Point_,
                 int ToleranceTimes_,
                 int ToleranceAngle_):
  Ref(Ref_),
  Point(Point_),
  ToleranceTimes(ToleranceTimes_),
  ToleranceAngle(ToleranceAngle_),
  referencePhi(0),
  referenceTheta(0),
  referencePsi(0) {}

bool Compare::misaligned(){
  int currentPhi = Point.getAnglePhi() - Ref.getAnglePhi();
  int currentTheta = Point.getAngleTheta() - Ref.getAngleTheta();
  int currentPsi = Point.getAnglePsi() - Ref.getAnglePsi();

  if ((currentPhi) > ToleranceAngle || (currentPhi) < ToleranceAngle){
    DPhi++;
  }
  if ((currentTheta) > ToleranceAngle || (currentTheta) < ToleranceAngle){
    DTheta++;
  }
  if ((currentPsi) > ToleranceAngle || (currentPsi) < ToleranceAngle){
    DPsi++;
  }

  if(DPhi>ToleranceTimes||DTheta>ToleranceTimes||DPsi>ToleranceTimes){
    DPhi = 0;
    DTheta = 0;
    DPsi = 0;
    return 1;
  } else { return 0;}
}

void Compare::reseter(){
    DPhi = 0;
    DTheta = 0;
    DPsi = 0;
}

void Compare::calibrate()
{
  referencePhi = Point.getAnglePhi() - Ref.getAnglePhi();
  referenceTheta = Point.getAngleTheta() - Ref.getAngleTheta();
  referencePsi = Point.getAnglePsi() - Ref.getAnglePsi();
}
