#include "graphics.h"

void sendSprite(uint8_t sprite, uint8_t inverted) {
    initializeCommunication();
    I2C_Write(CONTROL_DATA);
    if (inverted) {
        I2C_Write(~sprite);
    } else {
        I2C_Write(sprite);
    }
    I2C_Stop();
}

void sendSprite8x8(const uint8_t sprite[8], uint8_t inverted) {
    initializeCommunication();
    I2C_Write(CONTROL_DATA);
    for (uint8_t i = 0; i < 8; i++) {
        if (inverted) {
            I2C_Write(~sprite[i]);
        } else {
            I2C_Write(sprite[i]);
        }
    }
    
    I2C_Stop();
}

uint8_t posCursorIsValid(uint8_t x, uint8_t y) {
    return x <= (N_COLUMNS-1) && x >= 0 && y <= (HEIGHT-1) && y >= 0;
}



void clearDisplay() {
    setColumnAddress(0,127);
    setPageAddress(0,7);
    uint16_t bytesSend = 0;
    uint8_t bytesBuffer = 0;
    initializeCommunication();
    I2C_Write(CONTROL_DATA);
    while (bytesSend < 1057) {
        I2C_Write(0x00);
        bytesBuffer += 1;
        if (bytesBuffer >= WIRE_MAX) {
            I2C_Stop();
            bytesSend+= bytesBuffer;
            bytesBuffer = 0;
            initializeCommunication();
            I2C_Write(CONTROL_DATA);
        }
        
    }
}

void drawPixel(uint8_t x, uint8_t y) {
    setColumnAddress(x,N_COLUMNS);
    setPageAddress(y/N_PAGES, N_PAGES);
    sendSprite(0x01 << (y%N_BITS_PER_PAGE), 0);
}