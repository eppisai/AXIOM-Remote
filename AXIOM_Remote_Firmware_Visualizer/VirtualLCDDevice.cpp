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

VirtualLCDDevice::VirtualLCDDevice(volatile uint16_t * frameBuffer, volatile uint16_t * transitionframeBuffer, volatile uint16_t * framebuffer, CentralDB * db) {
  _frameBuffer = frameBuffer;
  _transitionframeBuffer = transitionframeBuffer;
  _framebuffer = framebuffer;
  _db = db;

}

void VirtualLCDDevice::DisplayFramebuffer() {
  int x, y;
  int transition_animation_type = _db -> GetUint32(Attribute::ID::TRANSITION_ANIMATION_TYPE);
  int transition_animation_speed = _db -> GetUint32(Attribute::ID::TRANSITION_ANIMATION_SPEED);
  int transition_counter = _db -> GetUint32(Attribute::ID::TRANSITION_COUNTER);
  if (_db -> GetBoolean(Attribute::ID::TRANSITION_ACTIVE)) {
    while (transition_counter > 0) {
      std::cout << "transition speed    " << transition_animation_speed << std::endl;
      if (transition_counter <= transition_animation_speed - 1) {
        _db -> SetBoolean(Attribute::ID::TRANSITION_ACTIVE, false);
        _db -> SetUint32(Attribute::ID::TRANSITION_ACTIVE, 0);
        std::cout << "transition active false" << std::endl;
      }
      std::cout << transition_animation_type << "\n";
      if (transition_animation_type == TRANSITION_WIPE_RIGHT) {

        float ratio = fabs(((float)(transition_counter) / 255) - 1);

        for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
          float horizontal_progress = (float)(x) / (float)(FRAMEBUFFER_WIDTH);

          if (horizontal_progress < ratio) {
            for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[x + y * FRAMEBUFFER_WIDTH];
            }
          } else {
            for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x + y * FRAMEBUFFER_WIDTH];
            }
          }
        }
      }
      if (transition_animation_type == TRANSITION_WIPE_LEFT) {

        float ratio = ((float)(transition_counter) / 255);

        for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
          float horizontal_progress = (float)(x) / (float)(FRAMEBUFFER_WIDTH);

          if (horizontal_progress > ratio) {
            for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[x + y * FRAMEBUFFER_WIDTH];
            }
          } else {
            for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x + y * FRAMEBUFFER_WIDTH];
            }
          }
        }
      }
      if (transition_animation_type == TRANSITION_PUSH_LEFT) {

        uint16_t offset = (float)(transition_counter) / (float)(255) * FRAMEBUFFER_WIDTH;

        for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
          if (x <= offset) {
            for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[(x + (FRAMEBUFFER_WIDTH - offset)) + y * FRAMEBUFFER_WIDTH];
            }
          } else {
            for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[(x - offset) + y * FRAMEBUFFER_WIDTH];
            }
          }
        }
      }
      if (transition_animation_type == TRANSITION_PUSH_RIGHT) {

        uint16_t offset = fabs((float)(transition_counter) / (float)(255) - 1) * FRAMEBUFFER_WIDTH;

        for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
          //uint16_t horizontal_progress = (float) (x) / (float) (_width);

          if (x > offset) {
            //if (((x - offset) < _width) && ((x - offset) >= 0)) {
            for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x - offset + y * FRAMEBUFFER_WIDTH];
            }
            //}
          } else {
            // if ((((x + (_width - offset)) >= 0) && (x + (_width - offset)) < _width)) {
            for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[(x + (FRAMEBUFFER_WIDTH - offset)) + y * FRAMEBUFFER_WIDTH];
            }
            //}
          }
        }
      }
      if (transition_animation_type == TRANSITION_PUSH_UP) {

        uint16_t offset = (float)(transition_counter) / (float)(255) * FRAMEBUFFER_HEIGHT;

        for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
          for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
            if (y <= offset) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x + (y + (FRAMEBUFFER_HEIGHT - offset)) * FRAMEBUFFER_WIDTH];
            } else {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[x + (y - offset) * FRAMEBUFFER_WIDTH];
            }
          }
        }
      }
      if (transition_animation_type == TRANSITION_PUSH_DOWN) {
        uint16_t offset = fabs(((float)(transition_counter) / (float)(255) - 1) * FRAMEBUFFER_HEIGHT);

        for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
          for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
            if (y > offset) {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _transitionframeBuffer[x + (y - offset) * FRAMEBUFFER_WIDTH];
            } else {
              _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[x + (y + (FRAMEBUFFER_HEIGHT - offset)) * FRAMEBUFFER_WIDTH];
            }
          }
        }

      }
      transition_counter -= transition_animation_speed;
    }
  } else {
    for (x = 0; x < FRAMEBUFFER_WIDTH; x++) {
      for (y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
        //for (y=_height; y>0; y--) { // we flip y axis so the origin in the lower left corner
        _framebuffer[y * FRAMEBUFFER_WIDTH + x] = _frameBuffer[(y) * FRAMEBUFFER_WIDTH + x];
      }
    }
  }
}