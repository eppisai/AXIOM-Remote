#ifndef ILCDDEVICE_H
#define ILCDDEVICE_H


#include <stdint.h>

class ILCDDevice 
{ 
public:
  virtual void DisplayFramebuffer(bool& transitionActive) = 0;
};

#endif //ILCDDEVICE_H