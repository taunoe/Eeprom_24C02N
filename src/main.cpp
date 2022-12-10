/*
Eeprom_24C02N
main.cpp
Tauno Erik
01.12.2022
*/
#include <Arduino.h>
#include <Wire.h>      // TwoWire

// read  0b10100001
// write 0b10100000
const int DEVICE_ADDR = 0b01010000; // 0 + 7bit address
const int MEM_SIZE_BYTES = 256;

/*
  Write Byte
*/
void write_byte(int word_addr, uint8_t data) {
  Wire.beginTransmission(DEVICE_ADDR);
  Wire.write(word_addr);
  Wire.write(data);
  Wire.endTransmission();
}

/*
  Write array to eepromm
*/
void write_array(uint8_t word_addr, int data[], int size) {
  Wire.beginTransmission(DEVICE_ADDR);
  Wire.write(word_addr);
  for (int i = 0; i < size; i++)
  {
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}

/*
  Random Read Byte
*/
uint8_t read_byte(uint8_t word_addr) {
  uint8_t data = 0;

  Wire.beginTransmission(DEVICE_ADDR);
  Wire.write(word_addr);
  Wire.endTransmission();

  //delay(1);
  Wire.requestFrom(DEVICE_ADDR, 1); // read 1 byte
  //delay(1);
  if ( Wire.available() ) {
    data = Wire.read();
  }
  return data;
}


/*
 Read to array
*/
void read_to_array(int addr, int * array, int size ) {
  Wire.beginTransmission(DEVICE_ADDR);
  Wire.write(addr);
  Wire.endTransmission();
  delay(1);

  for (int i = 0; i < size; i++) {
    Wire.requestFrom(DEVICE_ADDR, 1); // read 1 byte
    delay(1);
    if ( Wire.available() ) {
      array[i] = Wire.read();
    }
  }
}

/*
  Print Memory content
*/
void print_ascii_table() {
  int stepp = 16;
  int line[stepp];

  for (int address = 1; address < MEM_SIZE_BYTES; address += stepp) {
    char print_addr[6];
    sprintf(print_addr, "%04x  ", address);
    Serial.print(print_addr);

    for (int byte = 0; byte < stepp; byte++)
    {
      char hex_data[4];
      line[byte] = read_byte(address+byte);
      sprintf(hex_data, "%02x ", line[byte]);
      Serial.print(hex_data);
    }
    Serial.print(" ");

    for (int ascii = 0; ascii < stepp; ascii++) {
       Serial.print((char) line[ascii]);
    }
    Serial.println();
  }
}

/*
  Print Memory content
*/
void print_char_table() {
  int stepp = 16;
  int line[stepp];

  for (int address = 1; address < MEM_SIZE_BYTES; address += stepp) {
    char print_addr[6];
    sprintf(print_addr, "%04x  ", address);
    Serial.print(print_addr);

    for (int byte = 0; byte < stepp; byte++) {
      char hex_data[4];
      line[byte] = read_byte(address+byte);
      sprintf(hex_data, "%02x ", line[byte]);
      Serial.print(hex_data);
    }
    Serial.print(" ");

    // print char
    for (int ascii = 0; ascii < stepp; ascii++) {
      if (line[ascii] < 32 || line[ascii] > 126) {
        Serial.print(".");
      } else {
        Serial.print((char) line[ascii]);
      }
    }
    Serial.println();

  }
}

void print_binary() {
/*
  for (int i = 0; i < 256; i++) // 256 bytes total
  {
    uint8_t data_byte = read_byte(i);
    Serial.print(data_byte, BIN);
    Serial.print(" ");
  }
*/
int stepp = 8;
int line[stepp];

  for (int address = 1; address < MEM_SIZE_BYTES; address += stepp) {
    char print_addr[6];
    sprintf(print_addr, "%04x  ", address);
    Serial.print(print_addr);

    for (int byte = 0; byte < stepp; byte++) {
    //char hex_data[4];
     line[byte] = read_byte(address+byte);
     // sprintf(hex_data, "%02x ", line[byte]);
     // Serial.print(hex_data);
      
      Serial.print(line[byte], BIN);
      Serial.print(" ");
    }

    // print char
    for (int ascii = 0; ascii < stepp; ascii++) {
      if (line[ascii] < 32 || line[ascii] > 126) {
        Serial.print(".");
      } else {
        Serial.print((char) line[ascii]);
      }
    }
    Serial.println();

  }

}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  //write_byte(254, 105);

  //print_ascii_table();
  print_char_table();
  //print_binary();
  /*
  int my_data[10] = {};

  write_array(1, my_data, 10);

  int data[10];
  read_to_array(1, data, 10);

  for (int i = 0; i < 10; i++)
  {
    Serial.print(data[i]);
  }
  */


}

void loop() {
  
}