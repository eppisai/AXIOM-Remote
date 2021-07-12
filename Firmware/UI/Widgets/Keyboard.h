#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "IButton.h"
#include "../Painter/IPainter.h"
#include "../../GlobalSettings.h"
#include "../Color565.h"

//used for changing keyboard layout in screen.
enum class Keylayout {
    Numeric,
    Uppercase,
    Lowercase
};

class Keyboard: public IWidget {
  //keyboard variables,
  static const uint8_t _maxButtonNumber = 12;

  uint8_t _buttonMargin;

  //the various keyboard layout that are passed to pointer keysArray, to draw on screen.
  char _num[30];
  char _capital[30];
  char _small[30];

  uint8_t _buttonDimension;
  uint16_t _currentBackgroundColorkey;
  uint16_t _highlightBackgroundColorkey;

  void DrawTextField(IPainter * painter, char * input) {
    painter -> DrawFillRectangle(5, 40, GlobalSettings::LCDWidth - 10, 30, (uint16_t) Color565::White);
    uint8_t textwidth = painter->GetStringFramebufferWidth(input) + 10;
    painter -> DrawFillRectangle(textwidth, 42, 5, 25, (uint16_t) Color565::AXIOM_Orange);
    //TODO: Add a check variable to update/call DrawText()  only when user inputs.
    painter -> DrawText(9, 62, (char * ) input, (uint16_t) Color565::Black, TextAlign::TEXT_ALIGN_LEFT, 0);

    //For the pointer in the text feild that blinks in every one second 

    //     int milli_seconds = 1000;
    //     time_t start, end;
    //     start=time(0);
    //     while(1)
    //    {

    //    if(time(0)-start==1)
    //    {
    //     painter->DrawFastVLine(GetTextWidth(input) + 5,40,28,(uint16_t)Color565::AXIOM_Orange);
    //     start=start+1;
    //    }

  }
  void KeyboardLayout() {
    switch (activeKeyboardLayout) {
    case Keylayout::Uppercase:
      keysArray = _capital;
      currentKeyboardLayout = Keylayout::Uppercase;
      break;
    case Keylayout::Lowercase:
      keysArray = _small;
      currentKeyboardLayout = Keylayout::Lowercase;
      break;
    case Keylayout::Numeric:
      keysArray = _num;
      currentKeyboardLayout = Keylayout::Numeric;
      break;
    }
  }
  void DrawKeyboard(IPainter * painter) {
    KeyboardLayout();
    uint16_t temp = _y;
    bool highlighted = false;
    for (uint8_t position = 0; position < 30; position++) {

      if (position == activeKey) highlighted = true;
      uint8_t buttonMargin = _buttonDimension * (uint8_t) position + _buttonMargin * ((uint8_t) position + 1);

      //keys drawing on screen
      DrawKey(keysArray[position], painter, buttonMargin, temp, highlighted);
      if (position == 9 || position == 19) temp += 32;
      highlighted = false;
    }
  }
  void DrawKey(char key, IPainter * painter, uint8_t buttonMargin, uint16_t y, bool highlighted) {
    uint16_t color = (highlighted) ? _highlightBackgroundColorkey : _currentBackgroundColorkey;
    painter -> DrawFillRoundRectangle(_x + buttonMargin, y, _buttonDimension, _height, 3, color);
    uint8_t textPosY = _height / 2 + painter -> GetCurrentFontHeight() / 2;
    painter -> DrawCharacter(key, _x + buttonMargin + _buttonDimension / 2 - 7, y + textPosY, (uint16_t) Color565::Black);

  }

  public:
    char * keysArray;
    //input is text that user types in.
    char input[64];
    //activeKey is used to move the pointer in keyboard
    uint8_t activeKey;
    Keylayout activeKeyboardLayout, currentKeyboardLayout;
    Keyboard(uint16_t x, uint16_t y, uint16_t width, uint16_t height): IWidget(x, y, width, height) {
      
      _buttonMargin = 1;

      //the input array of char had some garbage value at the start.
      memset(input, 0, strlen((char * ) input));

      //easy initialization of keyboard layout,so will be easy to change later
      strcpy(_num, "1234567890!@#$%^&*()-={}./.-?~");
      strcpy(_capital, "QWERTYUIOPASDFGHJKLZXCVBNM.-?~");
      strcpy(_small, "qwertyuiopasdfghjklzxcvbnm.-?~");

      //activeKey is used to move between keys in keyboard
      activeKey = 0;

      //enum varibales used for switching keyboard layouts
      activeKeyboardLayout = Keylayout::Uppercase;
      currentKeyboardLayout = Keylayout::Uppercase;

      //button dimensions
      _buttonDimension = _width / _maxButtonNumber - _buttonMargin;
      _currentBackgroundColorkey = utils::RGB565(220, 220, 220);
      _highlightBackgroundColorkey = (uint16_t) Color565::AXIOM_Blue;

    }

  virtual void Draw(IPainter * painter) override
  {
    DrawTextField(painter, input);
    DrawKeyboard(painter);
  }
};

#endif // KEYBOARD_H