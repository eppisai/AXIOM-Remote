#include "Histograms.h"
#include "../MenuDefinitions.h"
#include "../ButtonDefinitions.h"
#include "../../../Bootloader/Periphery/USB/IUSBDevice.h"
#include "../IMenuSystem.h"
#include "../../GlobalSettings.h"

# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type)) 

HistogramsScreen::HistogramsScreen(IUSBDevice* usbDevice) :
    IScreen(usbDevice){}

void HistogramsScreen::Draw(IPainter* painter)
{
    Drawheader(painter);
    uint8_t data[] = {0x3C, 0xC9, 0x3F, 0x3E, 0xC1, 0x77, 0x03, 0x00, 0xC0, 0x03, 0x00, 0xC0, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0xC0, 0x0E, 0x00, 0x60, 0xFC, 0xFF, 0x3F,0x3C, 0xC9, 0x3F, 0x3E, 0xC1, 0x77, 0x03, 0x00, 0xC0, 0x03, 0x00, 0xC0, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0xC0, 0x0E, 0x00, 0x60, 0xFC, 0xFF, 0x3F,0x03, 0x00, 0xC0, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x3E, 0xC1, 0x77, 0x03, 0x00, 0xC0, 0x03, 0x00, 0xC0, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0xC0, 0x0E, 0x00, 0x60, 0xFC, 0xFF, 0x3F,0x3C, 0xC9, 0x3F, 0x3E, 0xC1, 0x77, 0x03, 0x00, 0xC0, 0x03, 0x00, 0xC0, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0xC0, 0x0E, 0x00, 0x60, 0xFC, 0xFF, 0x3F,0x03, 0x00, 0xC0, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, };
    BaseGraph Hist(data);
    Hist.Draw(painter);
    
}


void HistogramsScreen::Drawheader(IPainter* painter)
{
    // header background
    painter->DrawFillRectangle(0, 0, GlobalSettings::LCDWidth, 30, (uint16_t)Color565::Black);

    //  header title
    painter->SetFont(Font::FreeSans12pt7b);
    painter->DrawText(45, 22, "Graphs and Histograms", (uint16_t)Color565::White, TextAlign::TEXT_ALIGN_LEFT, 0);

}