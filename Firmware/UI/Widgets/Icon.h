#ifndef ICON_H
#define ICON_H

#include <inttypes.h>

struct Icon
{
    uint16_t Width;
    uint16_t Height;
    uint8_t Data[1];
};

#endif //ICON_H