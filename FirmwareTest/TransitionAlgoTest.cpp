#include "catch2/catch.hpp"

#include "ILI9341DeviceMod.h"

// Test data
#include "Images/frontFramebufferData.h"
#include "Images/backFramebufferData.h"
#include "Images/expectedFrames.h"


//Transition Animation is nothing but collection of different frames played very fast consequently one after other.
//In our case the transition consititutes of six different frames(each is combination of front framebuffer and back framebuffer)
//In below test case we are checking, the output of each frame produced by DisplayTransitionAnimation() and checking if each pixel of 
//each frame matches with pixel of each expected frames.  
TEST_CASE("DisplayTransitionAnimation TEST"){
  
  //ARRANGE
  ILI9341DisplayMod display(frontFramebuffer, backFramebuffer);

  //ACT
  int fps = 0;
  bool transitionActive = true;
  while(fps < 6){
    if(transitionActive){
      display.DisplayTransitionAnimation(transitionActive, expectedFrames[fps]);
    }
    fps++;
  }

  //ASSERT
  REQUIRE(display.CorrectArrayBound == true);
}


// TEST_CASE("SetActiveFramebuffer"){

//   //ARRANGE
//   ILI9341DisplayMod display(frontFramebuffer, backFramebuffer);

//   //ACT
//   display.SetActiveFramebuffer(backFramebuffer, frontFramebuffer);

//   //ASSERT
// }