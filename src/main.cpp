#include <Arduino.h>
#include <Timer.h>

#include "Giro.hpp"

#define RIGHT 9
#define LEFT 8
#define BOTTOM 7


Giro Referencia(3);            // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 3
Giro GiroscopioL(2);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 2
Giro GiroscopioR(0);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 0
Giro GiroscopioB(5);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 5

int DPhi, DTheta, DPsi;         // Essas variáveis armazenam quantas vezes os ângulos desviaram. 
                                /* A ideia por trás disso é indicar um desvio de postura somente quando a diferença entre ângulos é detectada 
                                   e permanece ocorrendo dentro de um certo período de tempo. A taxa de aquisição de dados do acelerômetro
                                   multiplicada pela tolerância de tempo resulta no tempo necessário pra indicar desalinhamento. */

const int TolTimes = 20;              // [Tolerância de tempo] Define o número de vezes que o dispositivo precisa detectar diferenças entre os ângulos antes de reportar um desalinhamento
                                   
const int TolGrad = 30;               // [Tolerância de ângulo] Define, em graus, a tolerância de desalinhamento entre os ângulos dos diferentes acelerômetros


// O reseter serve pra evitar que acumulos esporádicos que ocorram nas variáveis de desalinhamento gerem avisos aleatórios para o usuário
int reseter = 0;

// Variavel que define o tempo de vibração dos motores em millisegundos
const int MOTOR_DELAY = 300;

// Cada Timer é relativo a um motor de vibração
Timer timerL;
Timer timerR;
Timer timerB;

void setup() {

  Serial.begin(115200); 
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {


/* As linhas comentadas a seguir printam os ângulos calculados a partir dos dados do acelerômetro
   foram comentadas para facilitar a leitura das comparações no monitor serial */


  // delay(3000);
  // Serial.print("Referencia: ");
  // Referencia.printAngles();
  // Referencia.printTemperature();
  // Serial.print("GiroE: ");
  // GiroscopioE.printAngles();
  // GiroscopioE.printTemperature();
  // Serial.print("GiroR: ");
  // GiroscopioR.printAngles();
  // GiroscopioR.printTemperature();
  // Serial.print("GiroB: ");
  // GiroscopioB.printAngles();
  // GiroscopioB.printTemperature();
  // digitalWrite(BOTTOM,HIGH);
  // delay(1000);
  // digitalWrite(BOTTOM, LOW);
  // Serial.println();



/* As funções a seguir fazer a comparação entre os ângulos dos diferentes acelerômetros, considerando a tolerância de ângulo
   e armazenam o número de vezes que ocorrem diferenças */

  if (((Referencia.getAnglePhi())>((GiroscopioL.getAnglePhi())+TolGrad)) || ((Referencia.getAnglePhi())<((GiroscopioL.getAnglePhi())-TolGrad))){
    DPhi++;
  }
  if (((Referencia.getAngleTheta())>((GiroscopioL.getAngleTheta())+TolGrad)) || ((Referencia.getAngleTheta())<((GiroscopioL.getAngleTheta())-TolGrad))){
    DTheta++;
  }
  if (((Referencia.getAnglePsi())>((GiroscopioL.getAnglePsi())+TolGrad)) || ((Referencia.getAnglePsi())<((GiroscopioL.getAnglePsi())-TolGrad))){
    DPsi++;
  }

  /* As próximas funções indicam desalinhamento quando o número de vezes que ocorrem diferenças de ângulos ultrapassa uma certa tolerância.
     A variável que conta o número de vezes que ocorrem desalinhamentos é zerada logo que um desalinhamento é notificado */

  // FIX: Os lados dos motores estão relacionados aqui com os diferentes ângulos, e não aos lados dos acelerômetros
  if(DPhi>TolTimes){
    Serial.println("desalinhamento em Phi");
    DPhi=0;

    digitalWrite(LEFT, HIGH);
    timerL.start();
  }
  if(DTheta>TolTimes){
    Serial.println("desalinhamento em Theta");
    DTheta=0;

    digitalWrite(RIGHT, HIGH);
    timerR.start();
  }
  if(DPsi>TolTimes){
    Serial.println("desalinhamento em Psi");
    DPsi=0;

    digitalWrite(BOTTOM, HIGH);
    timerB.start();
  }

  // Os motores sao desligados quando os timers ultrapassam o tempo definido e os timers sao resetados
  if (timerL.read() > MOTOR_DELAY)
  {
    digitalWrite(LEFT, LOW);
    timerL.start();
    timerL.pause();
  }
  if (timerR.read() > MOTOR_DELAY)
  {
    digitalWrite(RIGHT, LOW);
    timerR.start();
    timerR.pause();
  }
  if (timerB.read() > MOTOR_DELAY)
  {
    digitalWrite(BOTTOM, LOW);
    timerB.start();
    timerB.pause();
  }


  // Lógica de funcionamento do resetter
  reseter++;
  if(reseter>=200){
    reseter =0;
    DPhi = 0;
    DTheta = 0;
    DPsi = 0;
  }
}
