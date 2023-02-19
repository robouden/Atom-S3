/*
*******************************************************************************
* Copyright (c) 2023 YR-Design
* Contact email: rob@yr-design.biz                          
*
* Visit for more information: 
*    https://docs.m5stack.com/en/core/m5stickc_plus
*    I2C modified code from https://github.com/paulh002/VFO-ESP32-Si5351
*
* Describe: Display and Si5351 setup test
* Date: 2023/01/25
*******************************************************************************
*/
// #include "M5StickC.h"
#include <M5AtomS3.h>
#include "si5351.h"
#include <Wire.h>

bool i2c_found=0 ;


// Inits
Si5351 si5351;
float frequency=0.01; //in MHz
unsigned long long test_freq_CL0 ;

static char strbuffer[20];


void setup() {
  bool i2c_found;

  // test_freq_CL0 = frequency*100000000;
   test_freq_CL0 = 2712000000;//for Henry
  //  test_freq_CL0 = 6410700;//for Tesla coil 641.07kHz
  // Start serial and initialize the Si5351
  // Serial.begin(9600);
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);

  M5.begin();
  Wire.begin(38,39);
  // Lcd display
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(3);
  delay(500);

  //P

  //Check I2C
  if(!i2c_found)
  {
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.println("Error I2C bus!");
  }
  else {
    M5.Lcd.println("si5351 Ok");
  }

  delay(1000);
    // text print
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setRotation(3);
    M5.Lcd.println("Si5351" );
    M5.Lcd.println();

  // Set CLK0 to output 27.12 MHz
  si5351.set_freq(test_freq_CL0, SI5351_CLK0);

  //Setup output for 8mA
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA);

  //Display data
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println(test_freq_CL0);
  delay(3000);
}

void loop() {
//   // while (not M5.BtnA.wasPressed()){
//   // Increase frequency
//   i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
//   Wire.begin(38,39);
//   //sent data to register
//   // test_freq_CL0 = frequency*100000000;
//   si5351.set_freq(test_freq_CL0, SI5351_CLK0);
//   M5.Lcd.fillScreen(BLACK);
//   M5.Lcd.setTextColor(WHITE);
//   M5.Lcd.setCursor(10, 10);
//   M5.Lcd.println("Si5351 V1.0");
//   M5.Lcd.setTextColor(GREEN);
//   M5.Lcd.setCursor(0, 60);
//   M5.Lcd.print(test_freq_CL0);
//   M5.Lcd.println("MHz");
//   if(!i2c_found) {
//   M5.Lcd.setTextColor(BLUE);
//   M5.Lcd.setCursor(0, 60);
//   M5.Lcd.print(test_freq_CL0);
//   M5.Lcd.println("MHz");
// }
//   // frequency=frequency+0.1;
//   delay(4000);
  
//   // }
//   // // Button setup 
//   // M5.update();  
//   // if (M5.BtnA.wasPressed()) {  
//   //       M5.Lcd.print('A');//Button A is the M5 big button B is small side button close to external connector
//   //       }


}

