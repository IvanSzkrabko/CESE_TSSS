#include "leds.h"

#define LEDS_ALL_OFF 0x0000
#define LEDS_ALL_ON 0xFFFF

static uint16_t *direccion;

static LedError_t RegistrarError;


  uint16_t LedToMask (uint8_t led){
      if (led>16){
          RegistrarError();
          return 0;
      }
      return (1<<(led-1));
  }

  void Leds_Create(uint16_t *puerto, LedError_t handler){
      direccion = puerto;
      RegistrarError = handler;
      *direccion=LEDS_ALL_OFF;
  }

  void Leds_On (uint8_t led){//led 1 a 15
    *direccion |= LedToMask(led);
  }

   void Leds_Off (uint8_t led){//led 1 a 15
    *direccion &= ~LedToMask(led);
  }

   void Leds_AllOn (){
    *direccion = LEDS_ALL_ON;
  }

   void Leds_AllOff (){
    *direccion = LEDS_ALL_OFF;
  }

   uint8_t Leds_PinState (uint8_t led){
    uint8_t state = LedToMask(led) & *direccion;
    return(state);
  }