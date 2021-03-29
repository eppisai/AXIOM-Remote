#include "Keyboard.h"
#include "../IMenuSystem.h"

#include "../../Media/Icons/up_icon.h"
#include "../../Media/Icons/down_icon.h"

#include "../ButtonDefinitions.h"
#include "../MenuDefinitions.h"
#include "../../GlobalSettings.h"
#include "../ButtonDefinitions.h"

#include "../../../Bootloader/Periphery/USB/IUSBDevice.h"


KeyboardScreen::KeyboardScreen(IUSBDevice * usbDevice):
  IScreen(usbDevice), _BACKSPACE("Erase"), _marginTop(1), _buttonMargin(1), _x(30), _y(80), _width(320), _height(30), _left("Aa"), _right("123*#"), _enter("Done"), _topButtonBar(ButtonBar(0, 2, 320, 30)), _capsButton("Back"), _clearall("Erase All"), _up( & up_icon), _down( & down_icon) {
    //bottom button bar
    _bottomButtonBar.SetButton(ButtonPosition::Left, & _left);

    _right.SetHighlightBackgroundColor((uint16_t) Color565::Navy);
    _bottomButtonBar.SetButton(ButtonPosition::Center, & _right);

    _enter.SetBackgroundColor((uint16_t) Color565::AXIOM_Blue);
    _enter.SetHighlightBackgroundColor((uint16_t) Color565::Navy);
    _bottomButtonBar.SetButton(ButtonPosition::Right, & _enter);

    //top button bar
    _clearall.SetHighlightBackgroundColor((uint16_t) Color565::Navy);
    _topButtonBar.SetButton(ButtonPosition::Right, & _clearall);

    _BACKSPACE.SetHighlightBackgroundColor((uint16_t) Color565::Navy);
    _topButtonBar.SetButton(ButtonPosition::Center, & _BACKSPACE);

    _capsButton.SetHighlightBackgroundColor((uint16_t) Color565::Navy);
    _topButtonBar.SetButton(ButtonPosition::Left, & _capsButton);
    //end 

    //the input array of char had some garbage value at the start.
    memset(input, 0, strlen((char * ) input));

    //easy initialization of keyboard layout,so will be easy to change later
    strcpy(_num, "1234567890!@#$%^&*()-={}./.-?~");
    strcpy(_capital, "QWERTYUIOPASDFGHJKLZXCVBNM.-?~");
    strcpy(_small, "qwertyuiopasdfghjklzxcvbnm.-?~");

    //_current_key is used to move the pointer in keyboard
    _current_key = 0;

    //enum varibales used for switching keyboard layouts
    _keyboardlayout = Keylayout::Uppercase;
    _currentkeyboardlayout = Keylayout::Uppercase;

    //button dimensions
    _buttonDimension = _width / _maxButtonNumber - _buttonMargin;
    _currentBackgroundColorkey = RGB565(220, 220, 220);
    _highlightBackgroundColorkey = (uint16_t) Color565::AXIOM_Blue;

  }

void KeyboardScreen::Draw(IPainter * painter) {
  painter -> SetFont(Font::FreeSans9pt7b);
  Drawtextfeild(painter, input);
  DrawBottomButtonBar(painter);
  DrawKeyboard(painter);
}

void KeyboardScreen::Drawtextfeild(IPainter * painter, char * input) {

  _topButtonBar.Draw(painter);
  painter -> DrawFillRectangle(5, 40, GlobalSettings::LCDWidth - 10, 30, (uint16_t) Color565::White);
  uint8_t textwidth = utils::GetTextWidth(input, Font::FreeSans12pt7b) + 10;
  painter -> DrawFillRectangle(textwidth, 42, 5, 25, (uint16_t) Color565::AXIOM_Orange);
  painter -> DrawText(9, 62, (char * ) input, (uint16_t) Color565::Black, TextAlign::TEXT_ALIGN_LEFT, 0);

  //for the pointer in the text feild that blinks in every one second  

  //     int milli_seconds=1000;
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

void KeyboardScreen::DrawKeyboard(IPainter * painter) {
  Keyboardlayout();
  uint16_t temp = _y;
  bool highlighted = false;
  for (int position = 0; position < 30; position++) {

    if (position == _current_key) highlighted = true;
    uint8_t buttonMargin = _buttonDimension * (uint8_t) position + _buttonMargin * ((uint8_t) position + 1);

    //keys drawing on screen
    DrawKey(_keyboard[position], painter, buttonMargin, temp, highlighted);
    if (position == 9 || position == 19) temp += 32;
    highlighted = false;
  }

}

// Draws keys in the keyboard
void KeyboardScreen::DrawKey(char key, IPainter * painter, uint8_t buttonMargin, uint16_t y, bool highlighted = false) {
  uint16_t color = (highlighted) ? _highlightBackgroundColorkey : _currentBackgroundColorkey;

  painter -> DrawFillRoundRectangle(_x + buttonMargin, y, _buttonDimension, _height, 3, color);
  uint8_t textPosY = _height / 2 + painter -> GetCurrentFontHeight() / 2;
  painter -> DrawCharacter(key, _x + buttonMargin + _buttonDimension / 2 - 7, y + textPosY, (uint16_t) Color565::Black);

}

void KeyboardScreen::Keyboardlayout() {
  switch (_keyboardlayout) {
  case Keylayout::Uppercase:
    _keyboard = _capital;
    _currentkeyboardlayout = Keylayout::Uppercase;
    break;
  case Keylayout::Lowercase:
    _keyboard = _small;
    _currentkeyboardlayout = Keylayout::Lowercase;
    break;
  case Keylayout::Numeric:
    _keyboard = _num;
    _currentkeyboardlayout = Keylayout::Numeric;
    break;
  }
}

void KeyboardScreen::Update(Button button, int8_t knob, IMenuSystem * menuSystem) {

  if (knob != 0) {
    if (knob > 0) {
      if (_current_key == 0) _current_key = 29;
      else _current_key--;
    } else {
      if (_current_key == 29) _current_key = 0;
      else _current_key++;
    }
  }
  switch (button) {
  case Button::BUTTON_1_DOWN:
    break;
  case Button::BUTTON_1_UP:
    menuSystem -> SetCurrentScreen(AvailableScreens::MainPage);
    break;
  case Button::BUTTON_2_DOWN:
    break;
  case Button::BUTTON_2_UP: {
    int toBeRemoved = strlen((char * ) input) - 1;
    // memmove(&input[toBeRemoved],&input[toBeRemoved+1],3);
    memset( & input[toBeRemoved], 0, 1);
  }
  break;
  case Button::BUTTON_3_DOWN:
    break;
  case Button::BUTTON_3_UP:
    memset(input, 0, strlen((char * ) input));
    break;
  case Button::BUTTON_4_DOWN:
    break;
  case Button::BUTTON_4_UP:
    if (_currentkeyboardlayout == Keylayout::Uppercase || _currentkeyboardlayout == Keylayout::Numeric) {
      _keyboardlayout = Keylayout::Lowercase;
    } else {
      _keyboardlayout = Keylayout::Uppercase;
    }
    break;
  case Button::BUTTON_5_DOWN:
    break;
  case Button::BUTTON_5_UP:
    if (_currentkeyboardlayout == Keylayout::Uppercase || _currentkeyboardlayout == Keylayout::Lowercase) {
      _keyboardlayout = Keylayout::Numeric;
    } else {
      _keyboardlayout = Keylayout::Uppercase;
    }
    break;
  case Button::BUTTON_6_DOWN:
    break;
  case Button::BUTTON_6_UP: {
    unsigned char ks = _keyboard[_current_key];
    strcat(input, (char * ) & ks);
    //   input[strlen(input) - 1] = '\0';
  }
  break;
  case Button::E_1_UP: {
    unsigned char ks = _keyboard[_current_key];
    strcat(input, (char * ) & ks);
    //   input[strlen(input) - 1] = '\0';
  }
  break;
  case Button::E_1_DOWN:
    break;
  default:
    break;
  }
}