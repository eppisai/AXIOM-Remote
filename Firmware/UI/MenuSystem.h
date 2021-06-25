#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include "IMenuSystem.h"

#include "MenuDefinitions.h"

#include "Screens/MainPage.h"
#include "Screens/MainMenu.h"
#include "Screens/SettingsSubMenu1.h"
#include "Screens/WhiteBalanceScreen.h"
//#include "../CentralDB.h"

class Painter;
class IScreen;
class IUSBDevice;

class MenuSystem : public IMenuSystem
{
  protected:
    IScreen* _currentScreen;
    AvailableScreens _currentScreenType;
    AvailableScreens _cur,_prev;

    CentralDB* _db;
    bool* transition_active;

    // TODO: Length has to be adjusted manually, as currently we use static init to save space on the MCU
    IScreen* _availableScreens[4];

    IUSBDevice* _usbDevice;

    // Menus, static init
    MainPage _mainPage;
    MainMenu _MainMenu;
    SettingsSubMenu1 _settingsSubMenu1;
    WhiteBalanceScreen _whiteBalance;
    bool* _transitionActive;
    void InitializeAvailableScreens();

  public:
    explicit MenuSystem(IUSBDevice* usbDevice, CentralDB* centraldb, bool* transitionActive);
    virtual ~MenuSystem();
    
    // void SetTransitionType();
    void SetCurrentScreen(AvailableScreens menu) override;
    AvailableScreens GetCurrentScreen();

    void Draw(IPainter* painter);

    void Update(Button button, int8_t knob);
};

#endif // MENUSYSTEM_H