#include "drawings.h"
#include "sprites.h"



Point catmullRomInterpolation(Point p0, Point p1, Point p2, Point p3, float t) {
    float t2 = t * t;
    float t3 = t2 * t;

    float c0 = -0.5f * t3 + t2 - 0.5f * t;
    float c1 = 1.5f * t3 - 2.5f * t2 + 1.0f;
    float c2 = -1.5f * t3 + 2.0f * t2 + 0.5f * t;
    float c3 = 0.5f * t3 - 0.5f * t2;

    Point interpolatedPoint;
    interpolatedPoint.x = c0 * p0.x + c1 * p1.x + c2 * p2.x + c3 * p3.x;
    interpolatedPoint.y = c0 * p0.y + c1 * p1.y + c2 * p2.y + c3 * p3.y;

    return interpolatedPoint;
}

void drawMatrix(uint8_t matrix[COLUMNS_TO_WRITE][7], uint8_t columns, uint8_t pages) {
    uint8_t bytesBuffer = 2;
    initializeCommunication();
    I2C_Write(CONTROL_DATA);
    
    for (uint8_t y = 0; y < pages; y++) { 
        for (uint8_t x = 0; x < columns; x++) {
            I2C_Write(matrix[x][y]);
            bytesBuffer += 1;
            if (bytesBuffer >= WIRE_MAX) {
                I2C_Stop();
                bytesBuffer = 2;
                initializeCommunication();
                I2C_Write(CONTROL_DATA);
            }
        }
    }
}

void drawTimeToShow(Oscilloscope oscilloscope) {
    setColumnAddress(0, 127);
    setPageAddress(0,7);
    uint8_t primeiro = oscilloscope.actualShowTimeLength*100; 
    uint8_t segundo = (int)(oscilloscope.actualShowTimeLength*1000) % 10; 
    uint8_t terceiro = (int)(oscilloscope.actualShowTimeLength*10000) % 10; 
    int quarto = (int)(oscilloscope.actualShowTimeLength*100000) % 10;
    sendSprite8x8(numbers[primeiro], 0);
    sendSprite8x8(numbers[segundo], 0);
    sendSprite(0b11000000, 0);
    sendSprite(0b11000000, 0);
    sendSprite8x8(numbers[terceiro], 0);
    sendSprite8x8(numbers[quarto], 0);
    sendSprite8x8(m,1);
    sendSprite8x8(s,1);
}

void drawAxis() {
    setColumnAddress(0,0);
    setPageAddress(1,7);
    for (uint8_t page = 0; page < N_PAGES-1; page++) {
        sendSprite(0xFF, 0);
    }
    setColumnAddress(1,1);
    setPageAddress(1,7);
    for (uint8_t page = 0; page < N_PAGES-1; page++) {
        if (page == 0) {
            setColumnAddress(1,17);
            sendSprite8x8(five, 0);
            sendSprite8x8(v, 0);
            setColumnAddress(1,1);
            setPageAddress(2,7);
        } else if (page == 6) {
            setColumnAddress(1,19);
            sendSprite(0x18, 0);
            sendSprite(0x18, 0);
            sendSprite8x8(five, 0);
            sendSprite8x8(v, 0);
        } else {
            sendSprite(0x00, 0);
        }
    }
    setColumnAddress(1,4);
    setPageAddress(4,5);
    for (uint8_t i = 0; i < 4; i++) {
        sendSprite(0x80,0);
    }
    for (uint8_t i = 0; i < 4; i++) {
        sendSprite(0x01,0);
    }
}   

void clearDisplayFromColumnToEnd(uint8_t column) {
    setColumnAddress(column,127);
    setPageAddress(0,7);
    uint16_t bytesSend = 0;
    uint8_t bytesBuffer = 0;
    uint16_t max = 1057 - (column+1) * N_PAGES;
    initializeCommunication();
    I2C_Write(CONTROL_DATA);
    while (bytesSend < max) {
        I2C_Write(0x00);
        bytesBuffer += 1;
        if (bytesBuffer >= WIRE_MAX) {
            I2C_Stop();
            bytesSend += bytesBuffer;
            bytesBuffer = 0;
            initializeCommunication();
            I2C_Write(CONTROL_DATA);
        }
    }
}

void drawPixelInMatrix(uint8_t matrix[COLUMNS_TO_WRITE][7], uint8_t x, uint8_t y) {
    matrix[x][y/N_PAGES] |= (1 << y%N_BITS_PER_PAGE);
}