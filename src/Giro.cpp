#include "Giro.hpp"
#include "AutoWire.hpp"

Giro::Giro(int port) : pino(port){

    pinMode(port,OUTPUT);                 // Define a porta conectada ao ADD0 do MPU-6050 como saída

}

float Giro::getAnglePhi(){

  digitalWrite(pino,HIGH);                // Coloca a porta ADD0 do MPU-5060 em HIGH. Isso muda o endereço do dispositivo de 0x68 para 0x69.
                                          // Esse passo é necessário porque não é possível ler dados com vários MPU-6050 no mesmo barramento (eles possuem o mesmo endereço)
                                          // Então muda-se o endereço apenas do que vai ser lido antes da aquisição de dados e volta para o endereço padrão ao terminar

  autowire sensor(HighAddr);              // Cria um objeto para a aquisição de dados

  AnglePhi = (360*(atan((sqrt((pow(sensor.getAx(),2)+(pow(sensor.getAy(),2))))/sensor.getAz()))))/(2*PI);     // Calcula um dos ângulos que definem o posicionamento
                                                                                                              // tridimensional do dispositivo com base em informações
                                                                                                              // adquiridas pelo acelerômetro
  digitalWrite(pino,LOW);                // Volta a porta ADD0 do MPU-6050 para LOW e, consequentemente, o endereço para 0x68
  return AnglePhi;
}

// As próximas funções repetem o mesmo comportamento da anterior

float Giro::getAngleTheta(){

  digitalWrite(pino,HIGH);

  autowire sensor(HighAddr);

  AngleTheta = (360*(atan((sensor.getAx())/sqrt(pow(sensor.getAy(),2)+pow(sensor.getAz(),2))))/(2*PI));;

  digitalWrite(pino,LOW); 
  return AngleTheta;
}

float Giro::getAnglePsi(){

  digitalWrite(pino,HIGH);

  autowire sensor(HighAddr);

  AnglePsi = (360*(atan((sensor.getAy())/sqrt(pow(sensor.getAx(),2)+pow(sensor.getAz(),2))))/(2*PI));;

  digitalWrite(pino,LOW); 
  return AnglePsi;
}

float Giro::getTemperature(){

  digitalWrite(pino,HIGH);

  autowire sensor(HighAddr);
  Temperature = sensor.getTemperature();

  digitalWrite(pino,LOW); 
  return (Temperature/340.00+36.53);
}

// As duas funções a seguir servem apenas para printar, no monitor serial, o ângulos calculados e a temperatura, obtidos
// a partir das funções anteriores

void Giro::printAngles(){

  Serial.print(" | Ângulo Φ: "); Serial.print(this->getAnglePhi());Serial.print("°");
  Serial.print(" | Ângulo 𝛙: "); Serial.print(this->getAnglePsi());Serial.print("°");
  Serial.print(" | Ângulo θ: "); Serial.print(this->getAngleTheta());Serial.print("°");
  Serial.println();

}

void Giro::printTemperature(){

  Serial.print("Temperatura: "); Serial.print(this->getTemperature()); Serial.println(" °C");

}