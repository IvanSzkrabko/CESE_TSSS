#include "stdint.h"

typedef void (*LedError_t)(void);

void Leds_Create(uint16_t *puerto, LedError_t handler);
void Leds_On (uint8_t led);
void Leds_Off (uint8_t led);
void Leds_AllOn ();
void Leds_AllOff ();
_Bool Leds_PinState (uint8_t led);