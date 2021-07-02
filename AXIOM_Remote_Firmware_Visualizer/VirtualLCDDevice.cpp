#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <thread>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory>
#include <cmath>
#include<iostream>
#include "VirtualLCDDevice.h";
#include "CentralDB/CentralDB.h"

#define FRAMEBUFFER_WIDTH 320
#define FRAMEBUFFER_HEIGHT 240

VirtualLCDDevice::VirtualLCDDevice(volatile uint16_t * frameBuffer, volatile uint16_t * transitionframeBuffer, volatile uint16_t * framebuffer) {
  _frontFramebuffer = frameBuffer;
  _backFramebuffer = transitionframeBuffer;
  _framebuffer = framebuffer;
}

void VirtualLCDDevice::SetActiveFramebuffer(volatile uint16_t* frontFramebuffer,volatile uint16_t* backFramebuffer)
{
    _frontFramebuffer = frontFramebuffer;
    _backFramebuffer = backFramebuffer;
}

void VirtualLCDDevice::DisplayFramebuffer(bool& transitionActive) {
    
    if(transitionActive){
            if (_transitionCounter < _transitionAnimationSpeed) {
              transitionActive = false;
              _transitionCounter = 255;
            }

            uint16_t offset = (float)(_transitionCounter) / (float)(255) * FRAMEBUFFER_WIDTH;
            for(int index = 0; index < FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT; index++){
               if(index%FRAMEBUFFER_WIDTH > offset){
                  _framebuffer[index] = _frontFramebuffer[index - offset];
               }
               else{
                  _framebuffer[index] = _backFramebuffer[index];
               }
            }
            _transitionCounter -= _transitionAnimationSpeed;
    } 
    else {
        for(int index = 0; index < FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT; index++){
            _framebuffer[index] = _frontFramebuffer[index];
        }
    }
}