#include "MPU.hpp"
#include "AutoWire.hpp"

MPU::MPU(int port,int offset_Phi, int offset_Theta, int offset_Psi) : pino(port),offsetPhi(offset_Phi),offsetTheta(offset_Theta),offsetPsi(offset_Psi){        // Constructor

    pinMode(port,OUTPUT);                 // Define a porta conectada ao ADD0 do MPU-6050 como saída

}

float MPU::getAnglePhi(){

  digitalWrite(pino,HIGH);                /* Coloca a porta ADD0 do MPU-5060 em HIGH. Isso muda o endereço do dispositivo de 0x68 para 0x69.
                                             Esse passo é necessário porque não é possível ler dados com vários MPU-6050 no mesmo barramento (eles possuem o mesmo endereço)
                                             Então muda-se o endereço apenas do que vai ser lido antes da aquisição de dados e volta para o endereço padrão ao terminar */

  autowire sensor(HighAddr);              // Cria um objeto para a aquisição de dados

  AnglePhi = (((360*(atan((sqrt((pow(sensor.getAx(),2)+(pow(sensor.getAy(),2))))/sensor.getAz()))))/(2*PI))+offsetPhi);     /* Calcula Phi, um dos ângulos que definem o posicionamento
                                                                                                                 tridimensional do dispositivo com base em informações
                                                                                                                 adquiridas pelo acelerômetro */

  digitalWrite(pino,LOW);                // Volta a porta ADD0 do MPU-6050 para LOW e, consequentemente, o endereço para 0x68
  return AnglePhi;
}

// As próximas funções repetem o mesmo comportamento da anterior

float MPU::getAngleTheta(){

  digitalWrite(pino,HIGH);

  autowire sensor(HighAddr);

  AngleTheta = ((360*(atan((sensor.getAx())/sqrt(pow(sensor.getAy(),2)+pow(sensor.getAz(),2))))/(2*PI))+offsetTheta);;

  digitalWrite(pino,LOW); 
  return AngleTheta;
}

float MPU::getAnglePsi(){

  digitalWrite(pino,HIGH);

  autowire sensor(HighAddr);

  AnglePsi = ((360*(atan((sensor.getAy())/sqrt(pow(sensor.getAx(),2)+pow(sensor.getAz(),2))))/(2*PI))+offsetPsi);;

  digitalWrite(pino,LOW); 
  return AnglePsi;
}

float MPU::getTemperature(){

  digitalWrite(pino,HIGH);

  autowire sensor(HighAddr);
  Temperature = sensor.getTemperature();

  digitalWrite(pino,LOW); 
  return (Temperature/340.00+36.53);
}

// As duas funções a seguir servem apenas para printar, no monitor serial, o ângulos calculados e a temperatura, obtidos
// a partir das funções anteriores

void MPU::printAngles(){
  Serial.print(" | Ângulo Φ: "); Serial.print(this->getAnglePhi());Serial.print("°");
  Serial.print(" | Ângulo 𝛙: "); Serial.print(this->getAnglePsi());Serial.print("°");
  Serial.print(" | Ângulo θ: "); Serial.print(this->getAngleTheta());Serial.print("°");
  Serial.println();

}

void MPU::printTemperature(){

  Serial.print("Temperatura: "); Serial.print(this->getTemperature()); Serial.println(" °C");

}

void MPU::auto_offset(){
  offsetPhi = (this->getAnglePhi() == 0) ? offsetPhi : (this->getAnglePhi())*(-1);
  offsetTheta = (this->getAngleTheta() == 0) ? offsetTheta : (this->getAngleTheta())*(-1);
  offsetPsi = (this->getAnglePsi() == 0) ? offsetPsi : (this->getAnglePsi())*(-1);
}