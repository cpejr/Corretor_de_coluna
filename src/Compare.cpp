#include "Compare.hpp"

Compare::Compare(MPU& Ref_, MPU& Point_,int ToleranceTimes_, int ToleranceAngle_):Point(Point_),Ref(Ref_),ToleranceTimes(ToleranceTimes_),ToleranceAngle(ToleranceAngle_){}

bool Compare::unaligned(){
  
    if ((abs(Ref.getAnglePhi() - Point.getAnglePhi()))>ToleranceAngle){
    DPhi++;
  }
  if ((abs(Ref.getAngleTheta() - Point.getAngleTheta()))>ToleranceAngle){
    DTheta++;
  }
  if ((abs(Ref.getAnglePsi() - Point.getAnglePsi()))>ToleranceAngle){
    DPsi++;
  }

  if(DPhi>ToleranceTimes||DTheta>ToleranceTimes||DPsi>ToleranceTimes){
    DPhi = 0;
    DTheta = 0;
    DPsi = 0;
    return 1;
  } else { return 0;};
}

void Compare::reseter(){
    DPhi = 0;
    DTheta = 0;
    DPsi = 0;
}

