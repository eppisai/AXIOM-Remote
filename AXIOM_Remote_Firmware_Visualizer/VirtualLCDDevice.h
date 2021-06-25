#ifndef VIRTUALLCDDEVICE_H
#define VIRTUALLCDDEVICE_H

#include <stdint.h>
#include <CentralDB/CentralDBObserver.h>>

#include "../Bootloader/Periphery/ILI9341/ILCDDevice.h"
#include "../Firmware/UI/TransitionDefinitions.h"

class VirtualLCDDevice: public ILCDDevice {
  volatile uint16_t * _framebuffer;
  volatile uint16_t * _frontFramebuffer;
  volatile uint16_t * _backFramebuffer;
  public:
    explicit VirtualLCDDevice(volatile uint16_t * frameBuffer, volatile uint16_t * transitionframeBuffer, volatile uint16_t * framebuffer);

    void DisplayFramebuffer(bool& transitionActive);

};

#endif //VIRTUALLCDDEVICE_H