#ifndef KEYBOARDSCREEN_H
#define KEYBOARDSCREEN_H

#include "IScreen.h"
#include "../Widgets/PushButton.h"
#include "../Widgets/ImageButton.h"
#include "../Widgets/IButton.h"


class IPainter;
class IUSBDevice;
class IButton;

class KeyboardScreen : public IScreen
{   
  ButtonBar _topButtonBar;
 
  PushButton _capsButton;

  PushButton _backspace;
  PushButton _clearall;

  // in case we want to add side buttons 
  ImageButton _up,_down;

  PushButton _left;
  PushButton _right;
  PushButton _enter;
  
  //keyboard variables,
  static const uint8_t _maxButtonNumber = 12;

  //dimensions of keyboard
  // _x,_y are start of keyboard
  uint16_t _x,_y,_width,_height;
  uint8_t _marginTop;
  uint8_t _buttonMargin;

  //used for changing keyboard layout in screen.
   enum class Keylayout
    {
      Numeric,
      Uppercase,
      Lowercase
    };
  //the various keyboard layout that are passed to pointer _keyboard, to draw on screen.
  char* _keyboard;
  char _num[30];
  char _capital[30];
  char _small[30];
  //_current_key is used to move the pointer in keyboard
  int _current_key;
  Keylayout _keyboardLayout, _currentKeyboardLayout;
  uint8_t _buttonDimension;
  uint16_t _currentBackgroundColorkey;
  uint16_t _highlightBackgroundColorkey;
  //input is text that user types in.
  char input[64];
  void DrawTextField(IPainter* painter,char* input);
  void KeyboardLayout();
  void DrawKeyboard(IPainter* painter);
  void DrawKey(char key,IPainter* painter,uint8_t buttonMargin,uint16_t y,bool highlighted);

  

  
  public:    
        explicit KeyboardScreen(IUSBDevice* usbDevice);
        virtual void Draw(IPainter* painter) override;
        void Update(Button button, int8_t knob, IMenuSystem* menuSystem) override;
    
  
};

#endif // KEYBOARDSCREEN_H

