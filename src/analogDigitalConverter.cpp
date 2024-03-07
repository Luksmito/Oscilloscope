

#include "analogDigitalConverter.h"

void setupADC() {
  ADMUX |= (1 << REFS0); //set the reference voltage 
  ADMUX |= (1 << ADLAR); //set the left adjust
  DIDR0 = 0;
  PRR |= (0 << PRADC);
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); // set the prescaler to 32
  ADCSRA |= (1 << ADEN); // enable ADC
  ADCSRA |= (1 << ADATE); //enable auto trigger
  ADCSRA |= (1 << ADIE); //enable interrupt
  ADCSRB |= (1 << ADTS0) | (1 << ADTS1); //enable auto trigger to TIMER0 compare match A
  ADCSRA |= (1 << ADSC); //start conversions
}

void enableADC() {
    ADCSRA |= (1 << ADEN); // enable ADC
}

void enableInterruptADC() {
    ADCSRA |= (1 << ADIE); //enable interrupt
}

void disableADC() {
    ADCSRA &= ~(1 << ADEN);
}

void disableADCinterrupts() {
    ADCSRA &= ~(1 << ADIE);
}