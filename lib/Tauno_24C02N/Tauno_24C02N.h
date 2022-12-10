/*
File: Tauno_24C02N.h
Tauno Erik
04.12.2022
*/
#if !defined(LIB_TAUNO_24C02N_H)
#define LIB_TAUNO_24C02N_H

#include <Arduino.h>
#include <Wire.h>

// EEPROM Size Bytes
#define AT24C01  128
#define AT24C02  256
#define AT24C04  512
#define AT24C08  1024
#define AT24C016 2048

class Tauno_24C02N {
  private:
  int _eeprom_size;
  int _device_addr;

  public:
  Tauno_24C02N(int name, int device_addr);
  ~Tauno_24C02N();

  void begin();
  void write_byte(int word_addr, uint8_t data);
  void write_array(uint8_t word_addr, int data[], int size);
  uint8_t read_byte(uint8_t word_addr);
  void read_to_array(int addr, int * array, int size );
  void print_ascii_table();
  void print_char_table();
  void print_binary_table();
};

#endif  // LIB_TAUNO_24C02N_H