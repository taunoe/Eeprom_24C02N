/*
File: Tauno_24C02N.cpp
Tauno Erik
04.12.2022
*/
#include "Tauno_24C02N.h"

Tauno_24C02N::Tauno_24C02N(int name, int device_addr) {
  _eeprom_size = name;
  _device_addr = device_addr;
}

Tauno_24C02N::~Tauno_24C02N() {

}

void Tauno_24C02N::begin() {
  Wire.begin();
}