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
    _cur = AvailableScreens::MainPage;
    _prev = _cur;
}

MenuSystem::~MenuSystem()
{
}

void MenuSystem::SetCurrentScreen(AvailableScreens menu)
{   _currentScreenType = menu;
    _currentScreen = _availableScreens[(uint8_t)menu];
    _cur = menu;
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
void MenuSystem::Draw(IPainter * painter, bool& transitionActive) {
  if (_currentScreen == nullptr) {
    return;
  } else if (_cur != _prev) {
    transitionActive = true;
    _prev = _cur;
  }
  painter -> Fill((uint16_t) _currentScreen -> GetBackgroundColor());

  _currentScreen -> Draw(painter);

}

void MenuSystem::Update(Button button, int8_t knob) {
  _currentScreen -> Update(button, knob, this);
}

// void MenuSystem::SetTransitionType() {
//   switch (_cur) {
//   case AvailableScreens::MainPage:
//     _db -> SetInt32(Attribute::ID::TRANSITION_ANIMATION_TYPE, 0);
//     break;
//   case AvailableScreens::MainMenu:
//     _db -> SetInt32(Attribute::ID::TRANSITION_ANIMATION_TYPE, 0);
//     break;
//   case AvailableScreens::SettingsSubMenu1:
//     _db -> SetInt32(Attribute::ID::TRANSITION_ANIMATION_TYPE, 0);
//     break;
//   case AvailableScreens::WhiteBalance:
//     _db -> SetInt32(Attribute::ID::TRANSITION_ANIMATION_TYPE, 0);
//     break;
//   default:
//     break;
//   }
// }