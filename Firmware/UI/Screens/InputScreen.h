#ifndef INPUTSCREEN_H
#define INPUTSCREEN_H

#include "IScreen.h"
#include "../Widgets/PushButton.h"
#include "../Widgets/ImageButton.h"
#include "../Widgets/Keyboard.h"
#include "../Widgets/IButton.h"


class IPainter;
class IUSBDevice;
class IButton;

class InputScreen : public IScreen
{   
  Keyboard _keyboard;
  ButtonBar _topButtonBar;
 
  PushButton _capsButton;

  PushButton _backspace;
  PushButton _clearall;

  // In case we want to add side buttons 
  ImageButton _up,_down;

  PushButton _left;
  PushButton _right;
  PushButton _enter;
  
  public:    
        explicit InputScreen(IUSBDevice* usbDevice);
        virtual void Draw(IPainter* painter) override;
        void Update(ButtonID ButtonID, int8_t knob, IMenuSystem* menuSystem) override; 
};

#endif // INPUTSCREEN_H

