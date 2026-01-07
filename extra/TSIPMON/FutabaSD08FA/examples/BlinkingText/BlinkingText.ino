/*
  FutabaSD08FA Library - Blinking Text Demo
 
  Demonstrates the use a Futaba NA202SD08FA VFD.
 
  This sketch blinks some text.
 
  The circuit (feel free to use other Arduino pins):
  
  * Display pins 2 (WRITE STROBE) connected to Arduino pin 8
  * Display pins 3-10 (D7-D0) connected to Arduino pins 2-7 and 10, 11
  * Display pin 11 (connected to +5V
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
  vfd.print("Some ");
  vfd.blinkingText();
  vfd.print("blinking");
  vfd.noBlinkingText();
  vfd.print(" text.");
}

void loop() {
  while(true){}
}
