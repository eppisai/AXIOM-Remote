#ifndef ILI9341DEVICEMOD_H
#define ILI9341DEVICEMOD_H

#include <iostream>
#include <cstring>

class ILI9341DisplayMod
{
   
    volatile uint16_t* _frontFramebuffer; 
    volatile uint16_t* _backFramebuffer;
    int _transitionAnimationSpeed;
    int _transitionCounter;

    public: 
     bool CorrectArrayBound = true;

     ILI9341DisplayMod(uint16_t* framebuffer, uint16_t* transitionFramebuffer){
        _frontFramebuffer = framebuffer;
        _backFramebuffer = transitionFramebuffer;
        _transitionAnimationSpeed = 60;
        _transitionCounter = 255;       
     }

     void SetActiveFramebuffer(volatile uint16_t* frontFramebuffer,volatile uint16_t* backFramebuffer){
       _frontFramebuffer = frontFramebuffer;
       _backFramebuffer = backFramebuffer;
     }

     void DisplayTransitionAnimation(bool& transitionActive, uint16_t* expectedOutput){
        
        uint16_t offset = ((float)(_transitionCounter) / (float)(255)) * 5;
        for(int index = 0; index < 25; index++){
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