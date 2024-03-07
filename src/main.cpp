#include <Arduino.h>
#include "oscilloscope.h"
#include "timer1ForTesting.h"
#define INPUT_SIGNAL A0

typedef struct {
  uint8_t values[POINTS_SAMPLED];
  uint16_t posValues;
  bool bufferFull; 
}Buffer;

Buffer lista;

bool flagBufferFull;

void saveValue(Buffer *buffer, uint16_t value) {
  buffer->values[buffer->posValues] = value; 
  buffer->posValues++;
}

void printaLista() {
  for (int i = 0; i < 100; i++) {
    Serial.println(lista.values[i]);
  }
}
ISR(TIMER0_COMPA_vect) {

}

ISR(ADC_vect) {
  TIFR0=(1<<OCF0A);
  saveValue(&lista, ADCH);

  if (lista.posValues == POINTS_SAMPLED) {
    lista.bufferFull=true;
    disableADCinterrupts();
    disableADC();
  }
}

void setupListADC() {
  lista.posValues = 0;
}

void setup() {
  lista.bufferFull = false;
  Serial.begin(9600);
  setupTimer1();

  setupListADC();
  
  Wire.begin();
  initializeOLED();
  clearDisplay();
  
  setupTimer0();
  setupADC();
  
  drawAxis();
  initializeOscilloscope(PERIODO_TIMER, 0.0002);
  sei();
}

void loop() {
  if (lista.bufferFull) {
    verifyButtons();
    //uint8_t signal[50] = {127, 233, 242, 144, 30, 5, 91, 210, 252, 179, 57, 0, 58, 180, 252, 209, 90, 4, 31, 146, 242, 233, 125, 19, 11, 110, 223, 248, 161, 42, 1, 75, 197, 253, 194, 72, 1, 45, 164, 249, 221, 106, 10, 21, 129, 235, 241, 142, 29, 5};
    drawSignal(lista.values);
    lista.bufferFull = false;
    lista.posValues = 0;
    enableADC();
    enableInterruptADC();
  }
}
