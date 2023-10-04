#include <Arduino.h>
#include "Giro.hpp"

Giro Giroscopio(17);            // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 17
Giro Giroscopio2(18);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 18

int DPhi, DTheta, DPsi;         // Essas variáveis armazenam quantas vezes os ângulos desviaram. 
                                /* A ideia por trás disso é indicar um desvio de postura somente quando a diferença entre ângulos é detectada 
                                   e permanece ocorrendo dentro de um certo período de tempo. A taxa de aquisição de dados do acelerômetro
                                   multiplicada pela tolerância de tempo resulta no tempo necessário pra indicar desalinhamento. */

int TolTimes = 20;              // [Tolerância de tempo] Define o número de vezes que o dispositivo precisa detectar diferenças entre os ângulos antes de reportar um desalinhamento
                                   

int TolGrad = 30;               // [Tolerância de ângulo] Define, em graus, a tolerância de desalinhamento entre os ângulos dos diferentes acelerômetros
                                   

void setup() {

  Serial.begin(115200); 
  
}

void loop() {


/* As linhas comentadas a seguir printam os ângulos calculados a partir dos dados do acelerômetro
   foram comentadas para facilitar a leitura das comparações no monitor serial */

//   Serial.print("Giro1: ");
//   Giroscopio.printAngles();
//   Giroscopio.printTemperature();
//   Serial.println();
// // 
//   Serial.print("Giro2: ");
//   Giroscopio2.printAngles();
//   Giroscopio2.printTemperature();
//   Serial.println();



/* As funções a seguir fazer a comparação entre os ângulos dos diferentes acelerômetros, considerando a tolerância de ângulo
   e armazenam o número de vezes que ocorrem diferenças */

  if (((Giroscopio.getAnglePhi())>((Giroscopio2.getAnglePhi())+TolGrad)) || ((Giroscopio.getAnglePhi())<((Giroscopio2.getAnglePhi())-TolGrad))){
    DPhi++;
  }
  if (((Giroscopio.getAngleTheta())>((Giroscopio2.getAngleTheta())+TolGrad)) || ((Giroscopio.getAngleTheta())<((Giroscopio2.getAngleTheta())-TolGrad))){
    DTheta++;
  }
  if (((Giroscopio.getAnglePsi())>((Giroscopio2.getAnglePsi())+TolGrad)) || ((Giroscopio.getAnglePsi())<((Giroscopio2.getAnglePsi())-TolGrad))){
    DPsi++;
  }

  /* As próximas funções indicam desalinhamento quando o número de vezes que ocorrem diferenças de ângulos ultrapassa uma certa tolerância.
     A variável que conta o número de vezes que ocorrem desalinhamentos é zerada logo que um desalinhamento é notificado */

  if(DPhi>TolTimes){
    Serial.println("desalinhamento em Phi");
    DPhi=0;
  }
  if(DTheta>TolTimes){
    Serial.println("desalinhamento em Theta");
    DTheta=0;
  }
  if(DPsi>TolTimes){
    Serial.println("desalinhamento em Psi");
    DPsi=0;
  }
}