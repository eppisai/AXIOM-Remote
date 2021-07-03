#include "catch2/catch.hpp"

#include <cstring>

#include "PainterMod.h"

// Test data
#include "Images/FramebufferData.h"
#include "Images/TransitionFramebufferData.h"

uint16_t frontFramebuffer[] = {0x0, 0x0, 0x0, 0x0, 0x0,//
                               0x0, 0x0, 0x0, 0x0, 0x0,//
                               0x0, 0x0, 0x0, 0x0, 0x0,//
                               0x0, 0x0, 0x0, 0x0, 0x0,//
                               0x0, 0x0, 0x0, 0x0, 0x0,};

uint16_t backFramebuffer[] =  {0x1, 0x1, 0x1, 0x1, 0x1,//
                               0x1, 0x1, 0x1, 0x1, 0x1,//
                               0x1, 0x1, 0x1, 0x1, 0x1,//
                               0x1, 0x1, 0x1, 0x1, 0x1,//
                               0x1, 0x1, 0x1, 0x1, 0x1,};

int transitionCounter = 255, transitionAnimationSpeed = 60, framebufferSize = 5*5;

void DisplayFramebuffer(bool& transitionActive)
{
    if(transitionActive){
            if (transitionCounter < transitionAnimationSpeed) {
              transitionActive = false;
              transitionCounter = 255;
            }
            uint16_t offset = ((float)(transitionCounter) / (float)(255)) * 320;
            for(int index = 0; index < framebufferSize; index++){
               if(index%320 < offset){
                  WritePMP(backFramebuffer[index]);
               }
               else{
                  WritePMP(frontFramebuffer[index - offset]);
               }
            }
            transitionCounter -= transitionAnimationSpeed;
        
    } 
    else {
        for(int index = 0; index < framebufferSize; index++){
            WritePMP(_frontFramebuffer[index]);
        }
    }

}