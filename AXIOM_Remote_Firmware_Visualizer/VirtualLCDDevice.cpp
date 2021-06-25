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

#include "VirtualLCDDevice.h";
#include "CentralDB/CentralDB.h"

#define FRAMEBUFFER_WIDTH 320
#define FRAMEBUFFER_HEIGHT 240

VirtualLCDDevice::VirtualLCDDevice(volatile uint16_t * frameBuffer, volatile uint16_t * transitionframeBuffer, volatile uint16_t * framebuffer) {
  _frontFramebuffer = frameBuffer;
  _backFramebuffer = transitionframeBuffer;
  _framebuffer = framebuffer;
}

void VirtualLCDDevice::DisplayFramebuffer(bool& transitionActive) {
  int x, y;
  int transitionAnimationType = 0;
  int transitionAnimationSpeed = 60;
  int transitionCounter = 255;
  // int transition_animation_speed = 2;
  if (transitionActive) {
    while (transitionCounter > 0) {
      std::cout << "transition speed    " << transitionAnimationSpeed << std::endl;
      if (transitionCounter <= transitionAnimationSpeed - 1) {
        transitionActive = false;
        std::cout << "transition active false" << std::endl;
      }
      std::cout << transitionAnimationType << "\n";
      if (transitionAnimationType == TRANSITION_PUSH_LEFT) {

        uint16_t offset = ((float)(transitionCounter) / (float)(255)) * FRAMEBUFFER_WIDTH;

        for(int index = 0; index < FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT; index++){
          if(index%FRAMEBUFFER_WIDTH > offset){
             _framebuffer[index] = _frontFramebuffer[index + (FRAMEBUFFER_WIDTH - offset)];
          }
          else{
            _framebuffer[index] = _backFramebuffer[index - offset];
          }

        }
      }
      transitionCounter -= transitionAnimationSpeed;
    }
  } else {
      for(int index = 0; index < FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT; index++){
            _framebuffer[index] = _frontFramebuffer[index];
        }
  }
}