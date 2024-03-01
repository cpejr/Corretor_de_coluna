#include <Arduino.h>
#include <Timer.h>
#include "Compare.hpp"
#include "MPU.hpp"

#define RIGHT 9
#define LEFT 8
#define BOTTOM 7

#define CALIBRATE_BUTTON 12

MPU Referencia(3,-53,-53,0);            // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 3
MPU MPU_L(2,35,-4,35);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 2
MPU MPU_R(4,36,-26,-15);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 0
MPU MPU_B(5,85,82,5);           // Define um objeto para um dispositivo MPU-6050 com AD0 na porta 5

const int TolTimes = 5;              // [Tolerância de tempo] Define o número de vezes que o dispositivo precisa detectar diferenças entre os ângulos antes de reportar um desalinhamento                                  
const int TolGrad = 25;               // [Tolerância de ângulo] Define, em graus, a tolerância de desalinhamento entre os ângulos dos diferentes acelerômetros

// O reseter serve pra evitar que acumulos esporádicos que ocorram nas variáveis de desalinhamento gerem avisos aleatórios para o usuário
int reseter = 0;

// Variavel que define o tempo de vibração dos motores em millisegundos
const int MOTOR_DELAY = 300;
const int RESET_TIME = 5000;

// Cada Timer é relativo a um motor de vibração
Timer timerL;
Timer timerR;
Timer timerB;
Timer ResetTimer;

Compare RightC(Referencia,MPU_R,TolTimes,TolGrad);
Compare LeftC(Referencia,MPU_L,TolTimes,TolGrad);
Compare BottomC(Referencia,MPU_B,TolTimes,TolGrad);

void setup() {

  Serial.begin(115200); 
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(BOTTOM, OUTPUT);

  pinMode(CALIBRATE_BUTTON, INPUT_PULLUP);
  // ResetTimer.start();
}

void loop() {
  // Parte do código responsável por calibrar os acelerometros ao apertar o botão
  if (!digitalRead(CALIBRATE_BUTTON))
  {
    RightC.calibrate();
    LeftC.calibrate();
    BottomC.calibrate();
  }

  if(RightC.misaligned()){
    digitalWrite(RIGHT, HIGH);
    // Serial.println("Desalinhamento no lado direito");
    timerR.start();
  }

  if(LeftC.misaligned()){
    digitalWrite(LEFT, HIGH);
    // Serial.println("Desalinhamento no lado esquerdo");
    timerL.start();
  }

  if(BottomC.misaligned()){
    digitalWrite(BOTTOM, HIGH);
    // Serial.println("Desalinhamento embaixo");
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
  // if (ResetTimer.read() > RESET_TIME)
  // {
  //   RightC.reseter();
  //   LeftC.reseter();
  //   BottomC.reseter();

  //   ResetTimer.start();
  //   Serial.println("Reset");
  // }
  // delay(2000);
  /*Serial.println("Referencia:");
  Referencia.printAngles();
  Serial.println("Left");
  MPU_L.printAngles();
  Serial.println("Right");
  MPU_R.printAngles(); 
  Serial.println("Bottom"); 
  MPU_B.printAngles();
*/}
