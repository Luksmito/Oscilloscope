#include "timer.h"
#include <Arduino.h>



void setCompareMatchA(uint8_t match) {
    OCR0A = match;
}

void setTimerInterrupts(uint8_t bits) {
    TIMSK0 |= bits;
}

void setClockPrescaler(uint8_t prescaler) {
    TCCR0B |= prescaler;
}

void setTimerIntervalInMicroSeconds(uint16_t intervalInMicroSeconds) {
    uint8_t bits = intervalInMicroSeconds/(PERIODO_TIMER * 1000000);
    OCR0A = bits;
}

void setupTimer0() {
  TCCR0A = 0b00000010;
  setClockPrescaler(0x03);
  setCompareMatchA(50); //Valor que gera a interrupção no match
  setTimerInterrupts(0x02); //ativa a interrupçao por match com OCR0A
}
