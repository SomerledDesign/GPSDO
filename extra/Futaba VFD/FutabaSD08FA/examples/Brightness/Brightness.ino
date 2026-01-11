/*
  FutabaSD08FA Library - Brightness Demo
 
  Demonstrates the use a Futaba NA202SD08FA VFD.
 
  This sketch demonstrates setting the four brightness levels.
 
  The circuit (feel free to use other Arduino pins):
  
  * Display pins 2 (WRITE STROBE) connected to Arduino pin 8
  * Display pins 3-10 (D7-D0) connected to Arduino pins 2-7 and 10, 11
  * Display pin 11 connected to +5V
  * Display pin 12 (GND) connected to GND
  * Display pins 13 & 14 unconnected
  
  Created on 24 April 2016.
 
  This example code is in the public domain.
*/

// Include the library code.
#include <FutabaSD08FA.h>

// Initialize the library with the numbers of the interface pins
FutabaSD08FA vfd(8, /* control pin */
                    10, 11, 2, 3, 4, 5, 6, 7 /* data pins */);

void setup() {
  // Start the library and specify the number of columns, rows.
  vfd.begin(20, 2);
  // Print a message to the VFD.
  vfd.print("Brightness demo.");
}

void loop() {
  delay(2000);
  vfd.brightness(FutabaSD08FA::DIM);
  vfd.setCursor(0,1);
  vfd.print("    ");
  vfd.setCursor(0,1);
  vfd.print("DIM");
  delay(2000);
  vfd.brightness(FutabaSD08FA::MID1);
  vfd.setCursor(0,1);
  vfd.print("    ");
  vfd.setCursor(0,1);
  vfd.print("MID1");
  delay(2000);
  vfd.brightness(FutabaSD08FA::MID2);
  vfd.setCursor(0,1);
  vfd.print("    ");
  vfd.setCursor(0,1);
  vfd.print("MID2");
  delay(2000);
  vfd.brightness(FutabaSD08FA::FULL);
  vfd.setCursor(0,1);
  vfd.print("    ");
  vfd.setCursor(0,1);
  vfd.print("FULL");
}
