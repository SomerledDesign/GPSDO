/*
  FutabaSD08FA Library - Hello World Demo
 
  Demonstrates the use a Futaba NA202SD08FA VFD.
 
  This sketch prints "Hello world!" to the VFD and
  shows the number of seconds since the sketch started.
  
  Also makes use of cursor positioning function setCursor().
 
  The circuit (feel free to use other Arduino pins):
  
  * Display pins 2 (WRITE STROBE) connected to Arduino pin 8
  * Display pins 3-10 (D7-D0) connected to Arduino pins 2-7 and 10, 11
  * Display pin 11 connected to +5V
  * Display pin 12 (GND) connected to GND
  * Display pins 13 & 14 unconnected
  
  Created Mar 6, 2011.
  Ported to FutabaSD08FA on 24 April 2016.
 
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
  vfd.print("Hello, world!");
}

void loop() {
  // Set the cursor to the first column (0) of the second row (1).
  vfd.setCursor(0, 1);
  // Print the number of seconds since reset.
  vfd.print(millis()/1000);
}
