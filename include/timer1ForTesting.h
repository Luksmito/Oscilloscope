#ifndef TIMER1FORTESTING_H
#define TIMER1FORTESTING_H

#include <Arduino.h>

#define output_test_signal PB0

const uint16_t T1_init = 0;
const uint16_t T1_comp = 31250;
// ======================================================================================================
// --- Interrupção ---
ISR(TIMER1_COMPA_vect)
{
  
  TCNT1 = T1_init;      //reinicializa TIMER1
  PORTB ^= (1 << output_test_signal);  //inverte nível lógico do pino do led
  
} //end ISR


// ======================================================================================================
// --- Configurações Iniciais ---
void setupTimer1() {
  DDRB |= (1 << output_test_signal);  //configura pino do led como saída

  //Modo de Comparação
  TCCR1A = 0;

  //Prescaler 1:256
  TCCR1B &= ~(1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= (1 << CS10);

  //Inicializa Registradores
  TCNT1 = T1_init;
  OCR1A = T1_comp;

  //Habilita Interrupção do Timer1
  TIMSK1 = (1 << OCIE1A);
}

#endif