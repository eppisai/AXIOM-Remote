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
#include "CentralDB.h"

#define FRAMEBUFFER_WIDTH 320
#define FRAMEBUFFER_HEIGHT 240

VirtualLCDDevice::VirtualLCDDevice(volatile uint16_t * frameBuffer, volatile uint16_t * transitionframeBuffer, volatile uint16_t * framebuffer,bool& transitionActive) {
  _frameBuffer = frameBuffer;
  _transitionframeBuffer = transitionframeBuffer;
  _framebuffer = framebuffer;
  _transitionActive = transitionActive;

}

void VirtualLCDDevice::DisplayFramebuffer() {
  int x, y;
  int transitionAnimationType = 0;
  int transitionAnimationSpeed = 60;
  int transitionCounter = 255;
  // int transition_animation_speed = 2;
  if (_transitionActive) {
    while (transitionCounter > 0) {
      std::cout << "transition speed    " << transitionAnimationSpeed << std::endl;
      if (transitionCounter <= transitionAnimationSpeed - 1) {
        _transitionActive = false;
        std::cout << "transition active false" << std::endl;
      }
      std::cout << transitionAnimationType << "\n";
      // if (transitionAnimationType == TRANSITION_WIPE_RIGHT) {

      //   float ratio = fabs(((float)(transition_counter) / 255) - 1);

      //   for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
      //     float horizontal_progress = (float)(x) / (float)(FRAMEBUFFER_WIDTH);

      //     if (horizontal_progress < ratio) {
      //       for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[x + y * FRAMEBUFFER_WIDTH];
      //       }
      //     } else {
      //       for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x + y * FRAMEBUFFER_WIDTH];
      //       }
      //     }
      //   }
      // }
      // if (transition_animation_type == TRANSITION_WIPE_LEFT) {

      //   float ratio = ((float)(transition_counter) / 255);

      //   for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
      //     float horizontal_progress = (float)(x) / (float)(FRAMEBUFFER_WIDTH);

      //     if (horizontal_progress > ratio) {
      //       for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[x + y * FRAMEBUFFER_WIDTH];
      //       }
      //     } else {
      //       for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x + y * FRAMEBUFFER_WIDTH];
      //       }
      //     }
      //   }
      // }
      if (transitionAnimationType == TRANSITION_PUSH_LEFT) {

        uint16_t offset = ((float)(transitionCounter) / (float)(255)) * FRAMEBUFFER_WIDTH;

        // for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
        //   if (x <= offset) {
        //     for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
        //       _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[(x + (FRAMEBUFFER_WIDTH - offset)) + y * FRAMEBUFFER_WIDTH];
        //     }
        //   } else {
        //     for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
        //       _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[(x - offset) + y * FRAMEBUFFER_WIDTH];
        //     }
        //   }
        // }

        for(int index = 0; index < FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT; index++){
          if(index%FRAMEBUFFER_WIDTH > offset){
             _framebuffer[index] = _transitionframeBuffer[index + (FRAMEBUFFER_WIDTH - offset)];
          }
          else{
            _framebuffer[index] = _frameBuffer[index - offset];
          }

        }
      }
      // if (transition_animation_type == TRANSITION_PUSH_RIGHT) {

      //   uint16_t offset = fabs((float)(transition_counter) / (float)(255) - 1) * FRAMEBUFFER_WIDTH;

      //   for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
      //     //uint16_t horizontal_progress = (float) (x) / (float) (_width);

      //     if (x > offset) {
      //       //if (((x - offset) < _width) && ((x - offset) >= 0)) {
      //       for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x - offset + y * FRAMEBUFFER_WIDTH];
      //       }
      //       //}
      //     } else {
      //       // if ((((x + (_width - offset)) >= 0) && (x + (_width - offset)) < _width)) {
      //       for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[(x + (FRAMEBUFFER_WIDTH - offset)) + y * FRAMEBUFFER_WIDTH];
      //       }
      //       //}
      //     }
      //   }
      // }
      // if (transition_animation_type == TRANSITION_PUSH_UP) {

      //   uint16_t offset = (float)(transition_counter) / (float)(255) * FRAMEBUFFER_HEIGHT;

      //   for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
      //     for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
      //       if (y <= offset) {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x + (y + (FRAMEBUFFER_HEIGHT - offset)) * FRAMEBUFFER_WIDTH];
      //       } else {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[x + (y - offset) * FRAMEBUFFER_WIDTH];
      //       }
      //     }
      //   }
      // }
      // if (transition_animation_type == TRANSITION_PUSH_DOWN) {
      //   uint16_t offset = fabs(((float)(transition_counter) / (float)(255) - 1) * FRAMEBUFFER_HEIGHT);

      //   for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
      //     for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
      //       if (y > offset) {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x + (y - offset) * FRAMEBUFFER_WIDTH];
      //       } else {
      //         _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[x + (y + (FRAMEBUFFER_HEIGHT - offset)) * FRAMEBUFFER_WIDTH];
      //       }
      //     }
      //   }

      // }
      transitionCounter -= transitionAnimationSpeed;
    }
  } else {
      for(int index = 0; index < FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT; index++){
            _framebuffer[index] = _frameBuffer[index];
        }
  }
}