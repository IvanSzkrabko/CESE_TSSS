#include "unity.h"
#include "leds.h"
#include "stdbool.h"

/*
TP3:
Las pruebas deben ser pensadas como individuales
prender todos de una vez
apagar todos de una vez
ver el estado 
probar el 1 y el 16 con su estado

TP4:
generar 5 pruebas de codigo real
*/

uint16_t ledsVirtuales;
bool error_informado = false;

void RegistrarError(void){
    error_informado = true;
}

void setUp(void){ //se llama antes de cada test
    error_informado = false;
    Leds_Create(&ledsVirtuales, RegistrarError);
}

void tearDown(void){ //se llama despues de cada test
}

void test_inicializacion(void){
//TEST_FAIL_MESSAGE("Empezamos");
}

void test_LedsOffAfterCreate(void){
    uint16_t ledsVirtuales = 0xFFFF;
    Leds_Create(&ledsVirtuales,RegistrarError);//incializo los leds
    TEST_ASSERT_EQUAL_HEX16(0,ledsVirtuales);//verifico que arranquen en cero
}

void test_prender_led_individual (void){
     Leds_On(1);
     TEST_ASSERT_EQUAL_HEX16(1,ledsVirtuales);
}

void test_apagar_led_individual (void){
     Leds_On(1);
     Leds_Off(1);
     TEST_ASSERT_EQUAL_HEX16(0,ledsVirtuales);
}

void test_prender_apagar_multiples(void){
    Leds_On(3);
    Leds_On(4);
    Leds_Off(3);
    TEST_ASSERT_EQUAL_HEX16(1<<3,ledsVirtuales);
}

void test_prender_led_invalido(void){
    Leds_On(17);
    TEST_ASSERT(error_informado);
}

void test_todos_prendidos(void){

    Leds_AllOn ();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF,ledsVirtuales);
}

void test_todos_apagados(void){
    Leds_AllOn();
    Leds_AllOff();
    TEST_ASSERT_EQUAL_HEX16(0,ledsVirtuales);
}


void test_consulta_estado(void){
    Leds_AllOn();    
    Leds_Off(3);
    TEST_ASSERT_EQUAL_HEX16(0,Leds_PinState(3));
}

