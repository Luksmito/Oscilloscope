#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
#define PERIODO_TIMER 0.000004

/*
Set value to generate the match interrupt in OCR0A
*/
void setCompareMatchA(uint8_t match);

/*
Set the interrupts

bit 0 - Timer/Counter0 Overflow Interrupt Enable
bit 1 - Timer/Counter0 Output Compare Match A Interrupt Enable
bit 2 - Timer/Counter Output Compare Match B Interrupt Enable
*/
void setTimerInterrupts(uint8_t bits);

/*
bit2  bit1  bit0 Description
0      0     0   No clock source (Timer/Counter stopped)
0      0     1   clk/(no prescaling)
0      1     0   clk/8 (from prescaler)
0      1     1   clk/64 (from prescaler)
1      0     0   clk/256 (from prescaler)
1      0     1   clk/1024 (from prescaler)
1      1     0   External clock source on T0 pin. Clock on falling edge.
1      1     1   External clock source on T0 pin. Clock on rising edge.
*/
void setClockPrescaler(uint8_t prescaler);


void setTimerIntervalInMicroSeconds(uint16_t interval);

void setupTimer0();

#endif 