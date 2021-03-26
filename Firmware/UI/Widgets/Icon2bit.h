#ifndef ICON2BIT_H
#define ICON2BIT_H

#include <inttypes.h>

#include "../../Utils.h"
enum class ImageDataFormat : uint8_t
{
	Monochrome = 0,
	Indexed2Bit = 1
};

struct Icon2bit
{
    const uint16_t Width;
    const uint16_t Height;
    ImageDataFormat Format;
    uint16_t IndexedColors[4];
    const uint8_t* Data;
};

#endif // ICON2BIT_H
