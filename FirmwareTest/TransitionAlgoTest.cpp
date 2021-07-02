    #include "catch2/catch.hpp"

    TEST_CASE("DisplayDriver test"){
    bool framebufferSelection = true;
    bool transitionActive = false;
    while (1)
    {
        
        if(centralDB.GetBoolean(Attribute::ID::TRANSITION_ACTIVE)){
            if(framebufferSelection){
              painter->SetActiveFramebuffer(transitionFramebuffer);
              display.SetActiveFramebuffer(transitionFramebuffer, framebuffer);
              framebufferSelection = !framebufferSelection;
            }
            else{
              painter->SetActiveFramebuffer(framebuffer);  
              display.SetActiveFramebuffer(framebuffer, transitionFramebuffer);
              framebufferSelection = !framebufferSelection;
            }
            transitionActive = true;
            centralDB.SetBoolean(Attribute::ID::TRANSITION_ACTIVE, false);
        }
        menuSystem.Draw(painter);
        
        counter++;
        sprintf(debugText, "%d\r\n", counter);
        painter->DrawText(3, 90, debugText, (uint16_t)Color565::Red, TextAlign::TEXT_ALIGN_LEFT, 0);

        display.DisplayFramebuffer(transitionActive);

        // DelayMs(30);
    }
    }
