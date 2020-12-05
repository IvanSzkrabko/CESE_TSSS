#include "stdint.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

typedef void (*LedError_t)(void);

#define blockedColor 100
#define pendingColor 150
#define doneColor 200

#define bloquedState 0
#define pendingState 1
#define doneState 2

#define cmdInit 0
#define cmdOpen 1
#define cmdOn 4
#define cmdClose 2
#define cmdOff 5
#define cmdEndFSM 99

typedef struct  {
    bool blocked;
    uint8_t color;
}uiElement;

_Bool validacionComando(uint8_t  cmd, uint8_t  step, uint8_t * patronesOk);
void comandoInvalido(uint8_t  step,uint8_t * exam);
uint8_t getScore (uint8_t* exam, uint8_t size);
void updateUiElement(uint8_t state, uiElement* uiElm);
uint8_t updateUIsteps(uint8_t comando, uint8_t *inputArray, uiElement *uiElementos, uint8_t *scoreArray, uint8_t stepCount, uint8_t* step);

