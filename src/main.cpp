#include <Arduino.h>
#include "Giro.hpp"

Giro Giroscopio(17);            //Define um objeto para um dispositivo MPU-6050 com AD0 na porta 17
Giro Giroscopio2(18);           //Define um objeto para um dispositivo MPU-6050 com AD0 na porta 18

int DPhi, DTheta, DPsi;

void setup() {
  Serial.begin(115200); 
  
}

void loop() {

//   Serial.print("Giro1: ");
//   Giroscopio.printAngles();
//   Giroscopio.printTemperature();
//   Serial.println();
// // 
//   Serial.print("Giro2: ");
//   Giroscopio2.printAngles();
//   Giroscopio2.printTemperature();
//   Serial.println();

  if (((Giroscopio.getAnglePhi())>((Giroscopio2.getAnglePhi())+30))||((Giroscopio.getAnglePhi())<((Giroscopio2.getAnglePhi())-30))){
    DPhi++;
  }
  if (((Giroscopio.getAngleTheta())>((Giroscopio2.getAngleTheta())+30))||((Giroscopio.getAngleTheta())<((Giroscopio2.getAngleTheta())-30))){
    DTheta++;
  }
  if (((Giroscopio.getAnglePsi())>((Giroscopio2.getAnglePsi())+30))||((Giroscopio.getAnglePsi())<((Giroscopio2.getAnglePsi())-30))){
    DPsi++;
  }

  if(DPhi>20){
    Serial.println("desalinhamento em Phi");
    DPhi=0;
  }
  if(DTheta>20){
    Serial.println("desalinhamento em Theta");
    DTheta=0;
  }
  if(DPsi>20){
    Serial.println("desalinhamento em Psi");
    DPsi=0;
  }  

}