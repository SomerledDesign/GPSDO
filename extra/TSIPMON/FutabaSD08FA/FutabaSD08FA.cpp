/*
  FutabaSD08FA Library - Implementation

  Originally created 5 March 2011
  Based on the IeeFlipNoFrills library
  Ported to Futaba NA202SD08FA display on 24 April 2016.  
  Added eolWrap/eolNoWrap/eolScroll 29 August 2016. (KM)

  This file is in the public domain.  
*/

#include "FutabaSD08FA.h"
#include "Arduino.h"

FutabaSD08FA::FutabaSD08FA(uint8_t writeStrobePin,
                                 uint8_t data0Pin, uint8_t data1Pin, uint8_t data2Pin, uint8_t data3Pin,
                                 uint8_t data4Pin, uint8_t data5Pin, uint8_t data6Pin, uint8_t data7Pin)
{
  // Copy pin values.
  _writeStrobePin = writeStrobePin;
  
  _dataPins[0] = data0Pin;
  _dataPins[1] = data1Pin;
  _dataPins[2] = data2Pin;
  _dataPins[3] = data3Pin;
  _dataPins[4] = data4Pin;
  _dataPins[5] = data5Pin;
  _dataPins[6] = data6Pin;
  _dataPins[7] = data7Pin;

  // Init screen character dimensions to something harmless.
  _numDisplayColumns = 1;
  _numDisplayRows = 1;
  _numDisplayCharacters = _numDisplayColumns * _numDisplayRows;

  // Initialize pin states. Everything to output.
  pinMode(writeStrobePin, OUTPUT);
  digitalWrite(writeStrobePin, HIGH);

  for (int i=0; i<NUM_DATA_PINS; i++)
  {
    uint8_t pin = _dataPins[i];
    pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
  }
}

void FutabaSD08FA::begin(uint8_t numColumns, int numRows)
{
  _numDisplayColumns = numColumns;
  _numDisplayRows = numRows;
  _numDisplayCharacters = numColumns * numRows;

  // Make sure hardware has time to power up.
  delay(RESET_TIME_IN_MS);
  
  // Soft reset the display to get back to default state.
  writeInternal(RESET_CHARACTER);
  delayMicroseconds(SOFT_RESET_TIME_IN_US);
  writeInternal(CURSOR_OFF_CHARACTER);
}

void FutabaSD08FA::clear()
{
  writeInternal(DISPLAY_CLEAR_CHARACTER);  
}

void FutabaSD08FA::home()
{
  writeInternal(CURSOR_HOME_CHARACTER);  
}
  
void FutabaSD08FA::noBlink()
{
  writeInternal(CURSOR_OFF_CHARACTER);
}

void FutabaSD08FA::blink()
{
  writeInternal(BLINK_CURSOR_ON_CHARACTER);
}

void FutabaSD08FA::noCursor()
{
  writeInternal(CURSOR_OFF_CHARACTER);
}

void FutabaSD08FA::cursor()
{
  writeInternal(SOLID_CURSOR_ON_CHARACTER);
}

void FutabaSD08FA::eolWrap()
{
  writeInternal(END_OF_LINE_WRAP_CHARACTER);
}

void FutabaSD08FA::eolNoWrap()
{
  writeInternal(END_OF_LINE_NO_ADVANCE_CHARACTER);
}

void FutabaSD08FA::eolScroll()
{
  writeInternal(END_OF_LINE_HORIZONTAL_SCROLL_CHARACTER);
}

void FutabaSD08FA::setCursor(uint8_t column, uint8_t row)
{
  uint8_t address = row * _numDisplayColumns + column;
  if (address >= _numDisplayCharacters)
  {
    address = 0;
  }
  
  writeInternal(CURSOR_SET_CHARACTER);
  writeInternal(address);
}

void FutabaSD08FA::brightness(uint8_t level)
{
  writeInternal(BRIGHTNESS_PREAMBLE_CHARACTER);
  writeInternal(level);
}

void FutabaSD08FA::blinkingText()
{
  writeInternal(BLINK_TEXT_ON_CHARACTER);
}

void FutabaSD08FA::noBlinkingText()
{
  writeInternal(BLINK_TEXT_OFF_CHARACTER);
}

void FutabaSD08FA::underline()
{
  writeInternal(UNDERLINE_PREAMBLE_CHARACTER);
  writeInternal(UNDERLINE_ON);
}

void FutabaSD08FA::blinkingUnderline()
{
  writeInternal(UNDERLINE_PREAMBLE_CHARACTER);
  writeInternal(BLINKING_UNDERLINE_ON);
}

void FutabaSD08FA::noUnderline()
{
  writeInternal(UNDERLINE_PREAMBLE_CHARACTER);
  writeInternal(UNDERLINE_OFF);
}

/*virtual*/ size_t FutabaSD08FA::write(uint8_t character)
{
  writeInternal(character);
  return(1);
}

void FutabaSD08FA::writeInternal(uint8_t character)
{
    // Place character onto data pins.
    uint8_t tmpCharacter = character;
    for (int i=0; i<NUM_DATA_PINS; i++)
    {
      uint8_t pin = _dataPins[i];
 
      // Set pin value.
      digitalWrite(pin, (tmpCharacter & 1) ? HIGH : LOW);
          
      tmpCharacter >>= 1;
    }  
    
    // Pull write strobe low then high.
    digitalWrite(_writeStrobePin, LOW);
    delayMicroseconds(STROBE_DELAY_IN_US);
    digitalWrite(_writeStrobePin, HIGH);
}