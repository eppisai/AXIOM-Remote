#ifndef HISTOGRAMSCREEN_H
#define HISTOGRAMSCREEN_H

#include "IScreen.h"
#include "../Widgets/BaseGraph.h"

class IPainter;
class IUSBDevice;

class HistogramsScreen : public IScreen
{
  public:
    explicit HistogramsScreen(IUSBDevice* usbDevice);

    virtual void Draw(IPainter* painter) override;
    void Drawheader(IPainter* painter);
};

#endif // HISTOGRAMSCREEN_H
