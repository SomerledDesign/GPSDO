/*
  FutabaSD08FA Library - Underlines Demo
 
  Demonstrates the use a Futaba NA202SD08FA VFD.
 
  This sketch prints some text to the VFD and demonstrates
  the use of underlines and blinking underlines.
  
  Also makes use of cursor positioning function setCursor().
 
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
}

void loop() {
  vfd.print("Test1 ");
  vfd.underline();
  vfd.print("Test2");
  vfd.noUnderline();
  vfd.print(" Test3 ");
  vfd.blinkingUnderline();
  vfd.setCursor(0,1);
  vfd.print("Test4");
  vfd.noUnderline();
  while(true){};
}