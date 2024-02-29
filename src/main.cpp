#include <Arduino.h>
#include "Giro.hpp"
#define Right 9
#define Left 8
#define Bottom 7


Giro Referencia(3);            // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 3
Giro GiroscopioE(2);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 18
Giro GiroscopioR(0);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 18
Giro GiroscopioB(5);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 18


int DPhi, DTheta, DPsi;         // Essas variáveis armazenam quantas vezes os ângulos desviaram. 
                                /* A ideia por trás disso é indicar um desvio de postura somente quando a diferença entre ângulos é detectada 
                                   e permanece ocorrendo dentro de um certo período de tempo. A taxa de aquisição de dados do acelerômetro
                                   multiplicada pela tolerância de tempo resulta no tempo necessário pra indicar desalinhamento. */

int TolTimes = 20;              // [Tolerância de tempo] Define o número de vezes que o dispositivo precisa detectar diferenças entre os ângulos antes de reportar um desalinhamento
                                   

int TolGrad = 30;               // [Tolerância de ângulo] Define, em graus, a tolerância de desalinhamento entre os ângulos dos diferentes acelerômetros
                                   

void setup() {

  Serial.begin(115200); 
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  
}

void loop() {


/* As linhas comentadas a seguir printam os ângulos calculados a partir dos dados do acelerômetro
   foram comentadas para facilitar a leitura das comparações no monitor serial */


  delay(3000);
  Serial.print("Referencia: ");
  Referencia.printAngles();
  Referencia.printTemperature();
  Serial.print("GiroE: ");
  GiroscopioE.printAngles();
  GiroscopioE.printTemperature();
  Serial.print("GiroR: ");
  GiroscopioR.printAngles();
  GiroscopioR.printTemperature();
  Serial.print("GiroB: ");
  GiroscopioB.printAngles();
  GiroscopioB.printTemperature();
  digitalWrite(Bottom,HIGH);
  delay(1000);
  digitalWrite(Bottom, LOW);
  Serial.println();



/* As funções a seguir fazer a comparação entre os ângulos dos diferentes acelerômetros, considerando a tolerância de ângulo
   e armazenam o número de vezes que ocorrem diferenças */

  if (((Referencia.getAnglePhi())>((GiroscopioE.getAnglePhi())+TolGrad)) || ((GiroscopioE.getAnglePhi())<((GiroscopioE.getAnglePhi())-TolGrad))){
    DPhi++;
  }
  if (((Referencia.getAngleTheta())>((GiroscopioE.getAngleTheta())+TolGrad)) || ((Referencia.getAngleTheta())<((GiroscopioE.getAngleTheta())-TolGrad))){
    DTheta++;
  }
  if (((Referencia.getAnglePsi())>((GiroscopioE.getAnglePsi())+TolGrad)) || ((Referencia.getAnglePsi())<((GiroscopioE.getAnglePsi())-TolGrad))){
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

// O reseter serve pra evitar que acumulos esporádicos que ocorram nas variáveis de desalinhamento gerem avisos aleatórios para o usuário

  int reseter;
  reseter++;
  if(reseter>=200){
    reseter =0;
    DPhi = 0;
    DTheta = 0;
    DPsi = 0;
  }
}