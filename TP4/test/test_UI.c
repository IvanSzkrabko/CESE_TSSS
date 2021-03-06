#include "unity.h"
#include "UI.h"

//Testeo que la funcion de validacion de comandos funcione correctamente cuando el comando ingresado es valido
void test_validacionComando_ok(void){
    uint8_t  mockArray[3]={cmdOpen,cmdClose,cmdOpen};
    uint8_t cmd=cmdClose;
    uint8_t step=1;
    _Bool rta = validacionComando(cmd, step, mockArray);
    TEST_ASSERT_EQUAL(true,rta);
}

//Testeo que la funcion de validacion de comandos funcione correctamente cuando el comando ingresado es invalido
void test_validacionComando_notOk(void){
    uint8_t  mockArray[3]={cmdOpen,cmdOpen,cmdClose};
    uint8_t cmd=cmdOpen;
    uint8_t step=2;
    _Bool rta = validacionComando(cmd, step, mockArray);
    TEST_ASSERT_EQUAL(false,rta);
}

//Testeo que se actualize correctamente el array que lleva el puntaje de las operaciones, cuando el usuario comete un error
void test_comandoInvalido(void){
    uint8_t  mockArray[3]={1,1,1};
    uint8_t step=2;
    comandoInvalido(step,mockArray);
    TEST_ASSERT_EQUAL(false,mockArray[step]);
}

//Testeo que el puntaje se calcule correctamente 
void test_getScore(void){
    uint8_t  mockArray[5]={1,0,1,0,1};
    uint8_t result=getScore (mockArray,5);
    TEST_ASSERT_EQUAL(3,result);
}


//Testeo que las variables correspondientes a la UI del dispocitivo a actuar se actualizen correctamente segun el estado
void test_updateUiElement(void){
    uint8_t state=1;
    uiElement uiElm[3];
    updateUiElement(state, &uiElm[1]);
    TEST_ASSERT_EQUAL(false,uiElm[1].blocked);
    TEST_ASSERT_EQUAL(pendingColor,uiElm[1].color);
}


//Testeo el caso para el cual el usuario recorre la FSM de manera correcta sin errar en ningun paso, y obtiene el puntaje maximo
void test_updateUIsteps_ScoreMax(void){
    
    uint8_t  inputArray[4]={cmdInit,cmdClose,cmdOpen,cmdOn};
    uint8_t  scoreArray[3]={1,1,1};
    uint8_t steps=0;
    uiElement uiElementos[3];

    uint8_t stepCount = sizeof(uiElementos)/sizeof(uiElementos[0]);  

    updateUIsteps(cmdInit,inputArray,uiElementos,scoreArray,stepCount,&steps);
    TEST_ASSERT_EQUAL(pendingColor,uiElementos[0].color);
    TEST_ASSERT_EQUAL(blockedColor,uiElementos[1].color);
    TEST_ASSERT_EQUAL(blockedColor,uiElementos[2].color);
    
    updateUIsteps(cmdClose,inputArray,uiElementos,scoreArray,stepCount,&steps);
    TEST_ASSERT_EQUAL(doneColor,uiElementos[0].color);
    TEST_ASSERT_EQUAL(pendingColor,uiElementos[1].color);
    TEST_ASSERT_EQUAL(blockedColor,uiElementos[2].color);

    updateUIsteps(cmdOpen,inputArray,uiElementos,scoreArray,stepCount,&steps);
    TEST_ASSERT_EQUAL(doneColor,uiElementos[0].color);
    TEST_ASSERT_EQUAL(doneColor,uiElementos[1].color);
    TEST_ASSERT_EQUAL(pendingColor,uiElementos[2].color);

    updateUIsteps(cmdOn,inputArray,uiElementos,scoreArray,stepCount,&steps);
    TEST_ASSERT_EQUAL(doneColor,uiElementos[0].color);
    TEST_ASSERT_EQUAL(doneColor,uiElementos[1].color);
    TEST_ASSERT_EQUAL(doneColor,uiElementos[2].color);
   
    TEST_ASSERT_EQUAL(3, updateUIsteps(cmdEndFSM,inputArray,uiElementos,scoreArray,stepCount,&steps));
}

//Testeo el caso para el cual el usuario recorre la FSM de manera incorrecta errando todos los pasos, y obtiene un puntaje de cero
void test_updateUIsteps_ScoreCero(void){
    
    uint8_t  inputArray[4]={cmdInit,cmdClose,cmdOpen,cmdOn};
    uint8_t  scoreArray[3]={1,1,1};
    uint8_t steps=0;
    uiElement uiElementos[3];

    uint8_t stepCount = sizeof(uiElementos)/sizeof(uiElementos[0]);  

    updateUIsteps(cmdInit,inputArray,uiElementos,scoreArray,stepCount,&steps);
    
    updateUIsteps(cmdOpen,inputArray,uiElementos,scoreArray,stepCount,&steps);

    updateUIsteps(cmdClose,inputArray,uiElementos,scoreArray,stepCount,&steps);

    updateUIsteps(cmdClose,inputArray,uiElementos,scoreArray,stepCount,&steps);

    updateUIsteps(cmdOpen,inputArray,uiElementos,scoreArray,stepCount,&steps);

    updateUIsteps(cmdOff,inputArray,uiElementos,scoreArray,stepCount,&steps);

    updateUIsteps(cmdOn,inputArray,uiElementos,scoreArray,stepCount,&steps);
   
    TEST_ASSERT_EQUAL(0, updateUIsteps(cmdEndFSM,inputArray,uiElementos,scoreArray,stepCount,&steps));
}

//Testeo el caso para el cual el usuario recorre la FSM de manera incorrecta pero errando solo un paso, y obtiene un puntaje de 2/3
void test_updateUIsteps_ScoreTwo(void){
    
    uint8_t  inputArray[4]={cmdInit,cmdClose,cmdOpen,cmdOn};
    uint8_t  scoreArray[3]={1,1,1};
    uint8_t steps=0;
    uiElement uiElementos[3];

    uint8_t stepCount = sizeof(uiElementos)/sizeof(uiElementos[0]);  

    updateUIsteps(cmdInit,inputArray,uiElementos,scoreArray,stepCount,&steps);
    
    updateUIsteps(cmdClose,inputArray,uiElementos,scoreArray,stepCount,&steps);

    updateUIsteps(cmdClose,inputArray,uiElementos,scoreArray,stepCount,&steps);    

    updateUIsteps(cmdOpen,inputArray,uiElementos,scoreArray,stepCount,&steps);  

    updateUIsteps(cmdOn,inputArray,uiElementos,scoreArray,stepCount,&steps);
   
    TEST_ASSERT_EQUAL(2, updateUIsteps(cmdEndFSM,inputArray,uiElementos,scoreArray,stepCount,&steps));
}