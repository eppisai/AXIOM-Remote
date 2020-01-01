#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "IMenu.h"
#include "../Painter.h"
//#include "IWidget.h"

#include "../Widgets/MainPageButton.h"

#include "../ButtonDefinitions.h"

#include "../../../Bootloader/Periphery/USB/IUSBDevice.h"

class SettingsMenu : public IMenu {
    IUSBDevice* _usbDevice;

    MainPageButton _fpsButton;
    MainPageButton _analogGainButton;
    MainPageButton _digitalGainButton;
    MainPageButton _menuButton;
    MainPageButton _shutterButton;
    MainPageButton _whiteBalanceButton;

    IButton* _widgetArray[6] = {&_fpsButton, nullptr, nullptr, nullptr, nullptr, nullptr};

    Color565 _backgroundColor;

  public:
    explicit SettingsMenu(IUSBDevice* cdcDevice) :
        _usbDevice(cdcDevice),
        _fpsButton(MainPageButton(10, 0, 90, "FPS")),
        _analogGainButton(MainPageButton(115, 0, 90, "A. Gain")),
        _digitalGainButton(MainPageButton(220, 0, 90, "D. Gain")),
        _menuButton(MainPageButton(10, 210, 90, "MENU", true)),
        _shutterButton(MainPageButton(115, 180, 90, "Shutter", true)),
        _whiteBalanceButton(MainPageButton(220, 180, 90, "WB", true)),
        _backgroundColor(Color565::MenuBackground)
    {
        _menuButton.SetCaptionHeight(30);
        _menuButton.HideValue(true);
        _menuButton.SetCaptionFont(Font::FreeSans12pt7b);
        _menuButton.SetHandler(&MenuButtonHandler);

        _analogGainButton.SetHandler(&AnalogGainButtonHandler);
        _digitalGainButton.SetHandler(&DigitalGainButtonHandler);
    }

  protected:
    virtual Color565 GetBackgroundColor() override
    {
        return _backgroundColor;
    }

    virtual void SetBackgroundColor(Color565 color)
    {
        _backgroundColor = color;
    }

    static void MenuButtonHandler(void* sender)
    {
        SettingsMenu* menu = static_cast<SettingsMenu*>(sender);
        menu->SetBackgroundColor(Color565::Red);
    }

    static void AnalogGainButtonHandler(void* sender)
    {
        SettingsMenu* menu = static_cast<SettingsMenu*>(sender);
        menu->SetBackgroundColor(Color565::Green);
    }

    static void DigitalGainButtonHandler(void* sender)
    {
        SettingsMenu* menu = static_cast<SettingsMenu*>(sender);
        menu->SetBackgroundColor(Color565::MenuBackground);
    }

    void Draw(Painter* painter) override
    {
        for (uint8_t index = 0; index < 6; index++)
        {
            IWidget* widget = _widgetArray[index];
            if (widget == nullptr)
            {
                return;
            }

            widget->Draw(painter);
        }
    }

    void Update(Button button) override
    {
        switch (button)
        {
        case Button::BUTTON_1_UP:
            _fpsButton.SetValue((char*)"1U");
            _usbDevice->Send((uint8_t*)"Button 1 Up\r\n", 10);
            break;
        case Button::BUTTON_1_DOWN:
            _fpsButton.SetValue((char*)"1D");
            _usbDevice->Send((uint8_t*)"Button 1 Down\r\n", 10);
            break;
        case Button::BUTTON_2_UP:
            _fpsButton.SetValue((char*)"2");
            _analogGainButton.Activate(this);
            _usbDevice->Send((uint8_t*)"Button 2\r\n", 10);
            break;
        case Button::BUTTON_3_UP:
            _fpsButton.SetValue((char*)"3");
            _digitalGainButton.Activate(this);
            _usbDevice->Send((uint8_t*)"Button 3\r\n", 10);
            break;
        case Button::BUTTON_4_UP:
            _fpsButton.SetValue((char*)"4");
            _menuButton.Activate(this);
            _usbDevice->Send((uint8_t*)"Button 4\r\n", 10);
            break;
        default:
            break;
        }
    }
};

#endif //SETTINGSMENU_H