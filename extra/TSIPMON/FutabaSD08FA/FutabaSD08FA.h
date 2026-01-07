/*
  FutabaSD08FA Library - Declaration file
  
  Originally created 5 March 2011
  Based on the IeeFlipNoFrills library
  Ported to Futaba NA202SD08FA display on 24 April 2016.  
  Added eolWrap/eolNoWrap/eolScroll 29 August 2016. (KM)

  This file is in the public domain.  
*/

#ifndef FutabaSD08FA_h
#define FutabaSD08FA_h

#include <inttypes.h>
#include "Print.h"
#include "Arduino.h"

class FutabaSD08FA : public Print {
public:

  // Special control characters supported by the display.
  static const uint8_t BACKSPACE_CHARACTER = 0x08; 
  static const uint8_t ADVANCE_CURSOR_CHARACTER = 0x09; // Move forward 1 character.
  static const uint8_t LINE_FEED_CHARACTER = 0x0A; // Move down 1 line, same column
  static const uint8_t CARRIAGE_RETURN_CHARACTER = 0x0D; // Move down 1 line, first column
  static const uint8_t BLINK_CURSOR_ON_CHARACTER = 0x07;
  static const uint8_t SOLID_CURSOR_ON_CHARACTER = 0x0F;
  static const uint8_t CURSOR_OFF_CHARACTER = 0x0E;
  static const uint8_t BLINK_TEXT_ON_CHARACTER = 0x0B;
  static const uint8_t BLINK_TEXT_OFF_CHARACTER = 0x0C; 

  static const uint8_t END_OF_LINE_WRAP_CHARACTER = 0x11; // Wraps from end of second line to start for first line. (Character Overwrite Mode)
  static const uint8_t END_OF_LINE_NO_ADVANCE_CHARACTER = 0x12; // Cursor stops on the last position at end of display line two. (Scroll Up Mode)
  static const uint8_t END_OF_LINE_HORIZONTAL_SCROLL_CHARACTER = 0x13; // Second line scrolls. No effect on first line. (Horizontal Scroll Mode)

  static const uint8_t RESET_CHARACTER = 0x14;
  static const uint8_t DISPLAY_CLEAR_CHARACTER = 0x15;
  static const uint8_t CURSOR_HOME_CHARACTER = 0x16;
  static const uint8_t BIT_7_HIGH_FOR_NEXT_BYTE_CHARACTER = 0x19; // Allows use of 7 data lines. Use two-byte sequence to print extended ASCII characters.

  static const uint8_t CURSOR_SET_CHARACTER = 0x1B; // Position cursor.

  //Constants needed for the brightness() function.
  static const uint8_t BRIGHTNESS_PREAMBLE_CHARACTER = 0X04;
  static const uint8_t DIM = 0x20;
  static const uint8_t MID1 = 0x40;
  static const uint8_t MID2 = 0x60;
  static const uint8_t FULL = 0xFF;

  //Constants needed for the Underline functions.
  static const uint8_t UNDERLINE_PREAMBLE_CHARACTER = 0X17;
  static const uint8_t UNDERLINE_ON = 0x44;
  static const uint8_t BLINKING_UNDERLINE_ON = 0x46;
  static const uint8_t UNDERLINE_OFF = 0x45;
  
  // This library MAY support multiple displays. In this case, all pins
  // can be shared except write strobe. This library does not support
  // sharing pins with other devices. Arduino pin 13 (the one connected
  // to the on board LED) can be used for data lines but it can not
  // be used for the control line.
  // TODO: Test multiple displays.
  // Works with following displays:
  //    NA202SD08FA     Futaba
  //    CU20025-T300A   Noritake
  //
  FutabaSD08FA(uint8_t writeStrobePin,
                  uint8_t data0Pin, uint8_t data1Pin, uint8_t data2Pin, uint8_t data3Pin,
                  uint8_t data4Pin, uint8_t data5Pin, uint8_t data6Pin, uint8_t data7Pin);
             
  // Sets the character dimensions of the display.
  void begin(uint8_t numColumns, int numRows);

  void clear();
  void home();
  void blink();
  void noBlink();
  void cursor();
  void noCursor();
  void setCursor(uint8_t column, uint8_t row); 
  
//  Methods supported by LiquidCrystal but not by this library.
//  void noDisplay();
//  void display();
//  void scrollDisplayLeft();
//  void scrollDisplayRight();
//  void leftToRight();
//  void rightToLeft();
//  void autoscroll();
//  void noAutoscroll();
//  void command(uint8_t);
//  void createChar(uint8_t, uint8_t[]);

// Methods unique to this display.
  void brightness(uint8_t);
  void blinkingText();
  void noBlinkingText();
  void underline();
  void blinkingUnderline();
  void noUnderline();
  void eolWrap();   // only on second line
  void eolNoWrap(); // only on second line
  void eolScroll(); // only on second line
  void scrollWindow(uint8_t character);

  virtual size_t write(uint8_t character);

private:

  static const uint8_t NUM_DATA_PINS = 8;
  
  static const uint16_t RESET_TIME_IN_MS = 600;
  static const uint16_t SOFT_RESET_TIME_IN_US = 5000;
  static const uint16_t STROBE_DELAY_IN_US = 250;
  
  uint8_t _writeStrobePin;
  uint8_t _dataPins[NUM_DATA_PINS];
  
  uint8_t _numDisplayColumns;
  uint8_t _numDisplayRows;
  uint8_t _numDisplayCharacters;

  void writeInternal(uint8_t character);
};
  
#endif // FutabaSD08FA_h
