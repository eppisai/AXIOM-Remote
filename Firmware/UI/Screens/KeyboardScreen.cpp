#include "KeyboardScreen.h"
#include "../IMenuSystem.h"

#include "../../Media/Icons/up_icon.h"
#include "../../Media/Icons/down_icon.h"

#include "../ButtonDefinitions.h"
#include "../MenuDefinitions.h"
#include "../ButtonDefinitions.h"

#include "../../../Bootloader/Periphery/USB/IUSBDevice.h"


KeyboardScreen::KeyboardScreen(IUSBDevice * usbDevice):
  IScreen(usbDevice), _backspace("Erase"), _keyboard(30, 80, 320, 30), _left("Aa"), _right("123*#"), _enter("Done"), _topButtonBar(ButtonBar(0, 2, 320, 30)), _capsButton("Back"), _clearall("Erase All"), _up( & up_icon), _down( & down_icon) {
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

    _backspace.SetHighlightBackgroundColor((uint16_t) Color565::Navy);
    _topButtonBar.SetButton(ButtonPosition::Center, & _backspace);

    _capsButton.SetHighlightBackgroundColor((uint16_t) Color565::Navy);
    _topButtonBar.SetButton(ButtonPosition::Left, & _capsButton);
    //end 

  }

void KeyboardScreen::Draw(IPainter * painter) {
  painter -> SetFont(Font::FreeSans9pt7b);
  _topButtonBar.Draw(painter);
  _keyboard.Draw(painter);
  DrawBottomButtonBar(painter);
}


void KeyboardScreen::Update(Button button, int8_t knob, IMenuSystem * menuSystem) {

  if (knob != 0) {
    if (knob > 0) {
      if (_keyboard.activeKey == 0) _keyboard.activeKey = 29;
      else _keyboard.activeKey--;
    } else {
      if (_keyboard.activeKey == 29) _keyboard.activeKey = 0;
      else _keyboard.activeKey++;
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
    int toBeRemoved = strlen((char * ) _keyboard.input) - 1;
    // memmove(&_keyboard.input[toBeRemoved],&_keyboard.input[toBeRemoved+1],3);
    memset( & _keyboard.input[toBeRemoved], 0, 1);
  }
  break;
  case Button::BUTTON_3_DOWN:
    break;
  case Button::BUTTON_3_UP:
    memset(_keyboard.input, 0, strlen((char * ) _keyboard.input));
    break;
  case Button::BUTTON_4_DOWN:
    break;
  case Button::BUTTON_4_UP:
    if (_keyboard.currentKeyboardLayout == Keylayout::Uppercase || _keyboard.currentKeyboardLayout == Keylayout::Numeric) {
      _keyboard.activeKeyboardLayout = Keylayout::Lowercase;
    } else {
      _keyboard.activeKeyboardLayout = Keylayout::Uppercase;
    }
    break;
  case Button::BUTTON_5_DOWN:
    break;
  case Button::BUTTON_5_UP:
    if (_keyboard.currentKeyboardLayout == Keylayout::Uppercase || _keyboard.currentKeyboardLayout == Keylayout::Lowercase) {
      _keyboard.activeKeyboardLayout = Keylayout::Numeric;
    } else {
      _keyboard.activeKeyboardLayout = Keylayout::Uppercase;
    }
    break;
  case Button::BUTTON_6_DOWN:
    break;
  case Button::BUTTON_6_UP: {
    unsigned char ks = _keyboard.keysArray[_keyboard.activeKey];
    strcat(_keyboard.input, (char * ) & ks);
    //   _keyboard.input[strlen(_keyboard.input) - 1] = '\0';
  }
  break;
  case Button::E_1_UP: {
    unsigned char ks = _keyboard.keysArray[_keyboard.activeKey];
    strcat(_keyboard.input, (char * ) & ks);
    //   _keyboard.input[strlen(_keyboard.input) - 1] = '\0';
  }
  break;
  case Button::E_1_DOWN:
    break;
  default:
    break;
  }
}