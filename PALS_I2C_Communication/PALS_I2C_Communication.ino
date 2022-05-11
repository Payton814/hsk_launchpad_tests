// try out multiple I2C twowire libs
#include "driverlib/uart.h"
#include "inc/hw_nvic.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <inc/hw_i2c.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_gpio.h>
#include <inc/hw_ints.h>
#include <inc/hw_pwm.h>
#include <driverlib/i2c.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/timer.h>
#include <driverlib/interrupt.h>
#include <driverlib/rom.h>
#include <driverlib/rom_map.h>
#include <driverlib/udma.h>
#include <driverlib/pwm.h>
#include <driverlib/ssi.h>
#include <driverlib/systick.h>
#include <driverlib/adc.h>
#include <string.h>
#include "Wire.h"
#define  WIRE_INTERFACES_COUNT 4
unsigned long  i2c_1=1;
unsigned long i2c_3=3;
// declare 2 two wire objs
TwoWire *wire_1= new TwoWire(i2c_1); // i2C object for the i2c port on the launchpad
//TwoWire Wire1(i2c_1);
//TwoWire Wire3(i2c_3);
#define PCA9539DGVR_I2C_ADDRESS_1 116
#define PCA9539DGVR_I2C_ADDRESS_2 118
char one_byte;
uint8_t CRB = 2;
uint8_t payton;
//this is a comment, im afraid of my computer

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Hello, starting...");
  Serial.print("\n");
// begin both twowire libs (default off LEDs!)
//  wire_1->setModule(i2c_1);
//  Wire1.begin();
  wire_1->begin();
//  Wire3.begin();
}

void loop() {
  while(Serial.available()){
    one_byte=Serial.read();
    Serial.print("I got your stuff!");
//    Serial.print("try writing i to test_prio_array? \n");
//    memcpy(test_prio_array,&i, sizeof(i));

    payton = PCA1();
    PCA1_read();
    
  }
  delay(3000);
}

uint8_t PCA1(){
//    uint32_t err_from_slave=I2CSend2bytes(base, PCF8574_I2C_ADDRESS_1,1, to_write);
// change to wire libs
  wire_1->beginTransmission(PCA9539DGVR_I2C_ADDRESS_1);
  wire_1->write(CRB);
  return wire_1->endTransmission();

/*
  Wire1.beginTransmission(PCF8574_I2C_ADDRESS_1);
  Wire1.write(1);
  Wire1.write(to_write);
  return Wire1.endTransmission();
*/
}

void PCA1_read(){
  Serial.print(wire_1->requestFrom(PCA9539DGVR_I2C_ADDRESS_1, 1));    // request 2 bytes from slave address
  while(wire_1->available()){
    uint8_t c1 = wire_1->read(); // receive a byte as character
    Serial.print(c1);         // print the character
  }
}
