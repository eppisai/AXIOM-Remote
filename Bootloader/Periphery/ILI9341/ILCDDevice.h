#ifndef ILCDDEVICE_H
#define ILCDDEVICE_H


#include <stdint.h>

class ILCDDevice 
{ 
public:
  virtual void DisplayFramebuffer() = 0;
};

#endif //ILCDDEVICE_H