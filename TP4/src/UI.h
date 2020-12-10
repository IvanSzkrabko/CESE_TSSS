#include "stdint.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

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



/**
 * @brief 
 * Valida si el comando enviado al dispocitivo fue correcto
 * @param cmd    Comando sobre el dispocitivo que se muestra en al UI
 * @param step   Paso en el cual el dispocitivo debe ser actuado
 * @param patronesOk   Array de referencia con la secuencia correcta de actuacion de cada device
 * @return true     El comando correcto se aplico en el paso correcto sobre el device
 * @return false    El device no fue actuado con el comando o en el momento correcto
 */
_Bool validacionComando(uint8_t  cmd, uint8_t  step, uint8_t * patronesOk);

/**
 * @brief 
 * Actualiza el array que lleva el puntaje del usuario cuando un comando fue erroneo
 * @param step   Paso de la secuencia actual 
 * @param exam   Array que lleva la cuenta de operaciones efectuadas correctamente
 */
void comandoInvalido(uint8_t  step,uint8_t * exam);

/**
 * @brief 
 * Suma los puntajes del usuario luego de que termina de recorrer la FSM
 * @param exam   Array con que lleva la cuenta de todas las operaciones efectuadas
 * @param size   Tamaño del array
 */
uint8_t getScore (uint8_t* exam, uint8_t size);

/**
 * @brief 
 * Actualiza el estado de los dispocitivos en la UI
 * @param state   Nuvo estado del dispocitivo 
 * @param uiElm   Referencia al dispocitivo que se desea actualizar
 */
void updateUiElement(uint8_t state, uiElement* uiElm);

/**
 * @brief 
 * 
 * @param comando   En base al boton elegido en la UI se recibe un comando determinado
 * @param inputArray   Array de referencia con la secuencia correcta de actuacion en cada paso de la FSM
 * @param uiElementos   Referencia al dispocitivo que se actuo
 * @param scoreArray   Array con que lleva la cuenta de todas las operaciones efectuadas en la FSM
 * @param stepCount   Cantidad de pasos dentro de la operacion a realizar en la FSM
 * @param step   Referencia al numero de paso en ejecucion de la FSM
 */
uint8_t updateUIsteps(uint8_t comando, uint8_t *inputArray, uiElement *uiElementos, uint8_t *scoreArray, uint8_t stepCount, uint8_t* step);

