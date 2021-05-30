#ifndef VIRTUALLCDDEVICE_H
#define VIRTUALLCDDEVICE_H

#include <stdint.h>
#include <CentralDBObserver.h>

#include "../Bootloader/Periphery/ILI9341/ILCDDevice.h"
#include "../Firmware/UI/TransitionDefinitions.h"

class VirtualLCDDevice: public ILCDDevice {
  volatile uint16_t * _framebuffer;
  volatile uint16_t * _transitionframeBuffer;
  volatile uint16_t * _frameBuffer;
  CentralDB * _db;
  public:
    explicit VirtualLCDDevice(volatile uint16_t * frameBuffer, volatile uint16_t * transitionframeBuffer, volatile uint16_t * framebuffer, CentralDB * db);

    void DisplayFramebuffer();

};

#endif //VIRTUALLCDDEVICE_H