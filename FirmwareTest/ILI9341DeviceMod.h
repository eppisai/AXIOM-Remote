#ifndef ILI9341DEVICEMOD_H
#define ILI9341DEVICEMOD_H

#include <iostream>
#include <cstring>

#include "../Bootloader/Periphery/ILI9341/ILI9341Device.h"

#define ILI9341_TFTWIDTH   5     ///smaller for testing
#define ILI9341_TFTHEIGHT  5     ///smaller for testing

class ILI9341DisplayMod : public ILI9341Display
{
    public: 
     bool CorrectArrayBound = true;

     ILI9341DisplayMod(uint16_t* framebuffer, uint16_t* transitionFramebuffer) : 
        ILI9341Display(framebuffer, transitionFramebuffer)
    {
    }

     void DisplayTransitionAnimation(bool& transitionActive, uint16_t* expectedOutput){
        
        uint16_t offset = ((float)(_transitionCounter) / (float)(255)) * ILI9341_TFTHEIGHT;
        for(int index = 0; index < ILI9341_TFTHEIGHT*ILI9341_TFTWIDTH; index++){
            if(index%5 < offset){
                if(expectedOutput[index] != _backFramebuffer[index]) {
                  CorrectArrayBound = false;
                }
            }
            else{
                if(expectedOutput[index] != _frontFramebuffer[index - offset]) {
                  CorrectArrayBound = false;
                } 
            }
        }

        if (_transitionCounter < _transitionAnimationSpeed) {
            transitionActive = false;
            _transitionCounter = 255;
        }
        else {
            _transitionCounter -= _transitionAnimationSpeed;
        }  

     }

     void DisplayFramebuffer(uint16_t* expectedOutput)
     {
            for(int index = 0; index < 25; index++){
                if(expectedOutput[index] != _frontFramebuffer[index]) CorrectArrayBound = false;
            }

     }
};


#endif //ILI9341DEVICEMOD_H