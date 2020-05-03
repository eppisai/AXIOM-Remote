#include <stdint.h>

static const struct
{
	    uint16_t width;
	    uint16_t height;
		  uint8_t help_data[24 * 24 + 1];
} help = {
	    24, 24,
	    {   0x00, 0x7E, 0x00, 0x80, 0xFF, 0x00, 0xC0, 0xC3, 0x03, 0xC0, 0x00, 0x03, 
          0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x0E, 0x30, 0x00, 0x06, 
          0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 
          0x00, 0xC0, 0x01, 0x00, 0xF0, 0x00, 0x00, 0x30, 0x00, 0x00, 0x38, 0x00, 
          0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00}
};