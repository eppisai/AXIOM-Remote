#include "MenuSystem.h"
#include "Painter/IPainter.h"
#include "Screens/IScreen.h"
#include "TransitionDefinitions.h"

MenuSystem::MenuSystem(IUSBDevice* usbDevice, CentralDB* centraldb) :
    _currentScreen(nullptr), _usbDevice(usbDevice), _mainPage(usbDevice), _MainMenu(usbDevice, centraldb),
    _settingsSubMenu1(usbDevice, centraldb), _whiteBalance(usbDevice),_db(centraldb)
{
    InitializeAvailableScreens();

    SetCurrentScreen(AvailableScreens::MainPage);
    _cur = (uint8_t)AvailableScreens::MainPage;
    _prev = _cur;
}

MenuSystem::~MenuSystem()
{
}

void MenuSystem::SetCurrentScreen(AvailableScreens menu)
{   _prev = _cur;
    _currentScreenType = menu;
    _currentScreen = _availableScreens[(uint8_t)menu];
    _cur = (uint8_t)menu;
}

AvailableScreens MenuSystem::GetCurrentScreen()
{   
    return _currentScreenType;
}

void MenuSystem::InitializeAvailableScreens()
{
    _availableScreens[0] = &_mainPage;
    _availableScreens[1] = &_MainMenu;
    _availableScreens[2] = &_settingsSubMenu1;
    _availableScreens[3] = &_whiteBalance;
}
void MenuSystem::Draw(IPainter * painter) {
  if (_currentScreen == nullptr) {
    return;
  } else if (_cur != _prev) {
    _db->SetUint32(Attribute::ID::TRANSITION_ANIMATION_SPEED, 60);
    painter -> SetTransitionFramebuffer();
    _db -> SetBoolean(Attribute::ID::TRANSITION_ACTIVE, true);
    _db -> SetUint32(Attribute::ID::TRANSITION_COUNTER, 255);
    SetTransitionType();
    _prev = _cur;
  }
  painter -> Fill((uint16_t) _currentScreen -> GetBackgroundColor());

  _currentScreen -> Draw(painter);

}

void MenuSystem::Update(Button button, int8_t knob) {
  _currentScreen -> Update(button, knob, this);
}

void MenuSystem::SetTransitionType() {
  switch (_cur) {
  case (uint8_t) AvailableScreens::MainPage:
    _db -> SetInt32(Attribute::ID::TRANSITION_ANIMATION_TYPE, TRANSITION_PUSH_UP);
    break;
  case (uint8_t) AvailableScreens::MainMenu:
    _db -> SetInt32(Attribute::ID::TRANSITION_ANIMATION_TYPE, TRANSITION_PUSH_DOWN);
    break;
  case (uint8_t) AvailableScreens::SettingsSubMenu1:
    _db -> SetInt32(Attribute::ID::TRANSITION_ANIMATION_TYPE, TRANSITION_PUSH_LEFT);
    break;
  case (uint8_t) AvailableScreens::WhiteBalance:
    _db -> SetInt32(Attribute::ID::TRANSITION_ANIMATION_TYPE, TRANSITION_PUSH_RIGHT);
    break;
  default:
    break;
  }
}