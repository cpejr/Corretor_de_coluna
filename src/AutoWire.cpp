#include"AutoWire.hpp"
#include "Wire.h"

autowire::autowire(const int address) : addr(address){};    //Constructor

void autowire::updateData(){

    Wire.begin();
    Wire.beginTransmission(addr);                     // Inicia a transissão para o I2C slave com o endereço especificado
    Wire.write(0x6B);                                 // PWR_MGMT_1 register (power management)
    Wire.write(0);                                    // Setar para zero "acorda" o MPU-6050
    Wire.endTransmission(true);
    Wire.beginTransmission(addr);
    Wire.write(0x3B);                                 // Iniciando pelo registrador 0x3B do MPU-6050
    Wire.endTransmission(false);                      // Mantem a transmissão ativa
    Wire.requestFrom(addr, 14, true);                // Total de registradores a serem lidos (14, dois para cada parâmetro lido);

    Ax = Wire.read()<<8 | Wire.read();                //Lendo os dados do Acelerômetro dos registradores de forma sequencial
    Ay = Wire.read()<<8 | Wire.read();
    Az = Wire.read()<<8 | Wire.read();

    temperature = Wire.read()<<8 | Wire.read();       //Lendo os dados de temperatura

    Gx = Wire.read()<<8 | Wire.read();                //Lendo os dados do giroscópio
    Gy = Wire.read()<<8 | Wire.read();
    Gx = Wire.read()<<8 | Wire.read();
  
    Wire.endTransmission(true);                       //Finaliza a transmissão

}


// As próximas funções são apenas retornos para os dados adquiridos pela função anterior

int16_t autowire::getAx(){
    this->updateData();
    return this->Ax;
}
int16_t autowire::getAy(){
    this->updateData();
    return this->Ay;
}
int16_t autowire::getAz(){
    this->updateData();
    return this->Az;
}
int16_t autowire::getGx(){
    this->updateData();
    return this->Gx;
}
int16_t autowire::getGy(){
    this->updateData();
    return this->Gy;
}
int16_t autowire::getGz(){
    this->updateData();
    return this->Gz;
}
int16_t autowire::getTemperature(){
    this->updateData();
    return this->temperature;
}

