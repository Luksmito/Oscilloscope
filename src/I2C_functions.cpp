#include "I2C_functions.h"

// Função para iniciar a comunicação I2C
void I2C_Start() {
    Wire.beginTransmission(ADDRESS);
}

// Função para finalizar a comunicação I2C
uint8_t I2C_Stop() {
    return Wire.endTransmission();
}

// Função para enviar uma sequência de bytes via I2C
void I2C_Write(uint8_t dado) {
    Wire.write(dado);
}

