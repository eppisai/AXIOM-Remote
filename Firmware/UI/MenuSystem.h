#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include "IMenuSystem.h"

#include "MenuDefinitions.h"

#include "Screens/MainPage.h"
#include "Screens/SettingsMenu.h"

class Painter;
class IScreen;
class IUSBDevice;

class MenuSystem : public IMenuSystem
{
    IScreen* _currentScreen;

    // TODO: Length has to be adjusted manually, as currently we use static init to save space on the MCU
    IScreen* _availableScreens[3];

    IUSBDevice* _usbDevice;

    // Menus, static init
    MainPage _mainPage;
    SettingsMenu _settingsMenu;

    void InitializeAvailableScreens();

  public:
    MenuSystem(IUSBDevice* usbDevice);
    virtual ~MenuSystem();

    void SetCurrentScreen(AvailableScreens menu);

    void Draw(Painter* painter);

    void Update(Button button, int8_t knob, IUSBDevice* cdcDevice);
};

#endif // MENUSYSTEM_H
