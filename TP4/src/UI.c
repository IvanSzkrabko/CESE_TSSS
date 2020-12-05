#include "UI.h"

_Bool validacionComando(uint8_t cmd, uint8_t step, uint8_t *patronesOk)
{
  if (patronesOk[step] == cmd)
  {
    return true;
  }
  return false;
}

void comandoInvalido(uint8_t step, uint8_t *scoreArray)
{
  scoreArray[step] = 0;
}

uint8_t getScore(uint8_t *scoreArray, uint8_t size)
{
  uint8_t sum = 0;
  for (uint8_t i = 0; i < size; i++)
  {
    sum = scoreArray[i] + sum;
  }
  return sum;
}

void updateUiElement(uint8_t state, uiElement *uiElm)
{

  switch (state)
  {
  case 0:
    uiElm->color = blockedColor;
    uiElm->blocked = true;
    break;

  case 1:
    uiElm->color = pendingColor;
    uiElm->blocked = false;
    break;

  case 2:
    uiElm->color = doneColor;
    uiElm->blocked = true;
    break;

  default:
    break;
  }
}


uint8_t updateUIsteps(uint8_t comando, uint8_t *inputArray, uiElement *uiElementos, uint8_t *scoreArray, uint8_t stepCount, uint8_t *step)
{
  uint8_t score = 0;

  switch (*step)
  {
  case 0: //init
    for (uint8_t i = 0; i < stepCount; i++)
    {
      updateUiElement(bloquedState, &uiElementos[i]);
    }
    updateUiElement(pendingState, &uiElementos[*step]);
    (*step)++;
    break;

  case 1: //device 1

    if (validacionComando(comando, *step, inputArray))
    {
      updateUiElement(doneState, &uiElementos[(*step) - 1]);
      updateUiElement(pendingState, &uiElementos[*step]);
      (*step)++;
    }
    else
    {
      comandoInvalido((*step)- 1, scoreArray);
    }
    break;

  case 2: //device 2
    if (validacionComando(comando, *step, inputArray))
    {
      updateUiElement(doneState, &uiElementos[(*step) - 1]);
      updateUiElement(pendingState, &uiElementos[*step]);
      (*step)++;
    }
    else
    {
      comandoInvalido((*step)- 1, scoreArray);
    }
    break;

  case 3: //device 3
    if (validacionComando(comando, *step, inputArray))
    {
      updateUiElement(doneState, &uiElementos[(*step)- 1]);
      (*step)++;
    }
    else
    {
      comandoInvalido((*step) - 1, scoreArray);
    }
    break;

  case 4: //stats
    if (comando == cmdEndFSM)
      score = getScore(scoreArray, stepCount);
    break;

  default:
    break;
  }

  return score;
}


