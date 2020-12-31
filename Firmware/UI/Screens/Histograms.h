#ifndef HISTOGRAMSCREEN_H
#define HISTOGRAMSCREEN_H

#include "IScreen.h"
#include "../Widgets/PushButton.h"
#include "../Widgets/ImageButton.h"

class IPainter;
class IUSBDevice;

class HistogramsScreen : public IScreen
{
    PushButton _cancelButton;
    PushButton _setButton;
    PushButton _addPresetButton;

  public:
    explicit HistogramsScreen(IUSBDevice* usbDevice);

    virtual void Draw(IPainter* painter) override;

    static void CancelButtonHandler(void* sender);
    static void SetButtonHandler(void* sender);
    static void AddPresetButtonHandler(void* sender);
    void Drawheader(IPainter* painter);
    void Drawcartesianplane(IPainter* painter,int origin_x,int origin_y);
    void DrawBaseData(uint8_t data[],IPainter* painter,int origin_x,int origin_y);
};

#endif // HISTOGRAMSCREEN_H
