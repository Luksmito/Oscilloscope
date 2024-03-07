#include "oledi2c_ssd1306.h"

void initializeCommunication() {
    I2C_Start();
    //I2C_Write((ADDRESS << 1) & 0b11111110);
}

void sendCommand(uint8_t command) {
    initializeCommunication();
    I2C_Write(CONTROL_COMMAND);
    I2C_Write(command);
    I2C_Stop();
}

void setPageAddress(uint8_t start, uint8_t end)
{
    sendCommand(COMMAND_SET_PAGE_ADDRESS);
    sendCommand(start & 0x07);
    sendCommand(end & 0x07);
}

void setColumnAddress(uint8_t start, uint8_t end)
{
    sendCommand(COMMAND_COLUMN_ADDRESS);
    sendCommand(start);
    sendCommand(end);
}


void initializeOLED() {
    sendCommand(0xAE);
    sendCommand(0xD5);
    sendCommand(0x80);
    sendCommand(0xA8);
    sendCommand(0x40 - 1);
    sendCommand(0xD3);
    sendCommand(0x00);
    sendCommand(0x40 | 0);
    sendCommand(0x8D);
    sendCommand(0x14);
    sendCommand(0x20);
    sendCommand(0x00);
    sendCommand(0xA0 | 0x1);
    sendCommand(0xC8);
    sendCommand(0xDA);
    sendCommand(0x12);
    sendCommand(0x81);
    sendCommand(0xCF);
    sendCommand(0xD9);
    sendCommand(0xF1);
    sendCommand(0xD8);
    sendCommand(0x40);
    sendCommand(0xA4);
    sendCommand(0xA6);
    sendCommand(0x2E);
    sendCommand(0xAF);
    setColumnAddress(0,127);
    setPageAddress(0,7);
}

void setHorizontalAddressingMode () {
    sendCommand(SET_HORIZONTAL_ADDRESSING_MODE);
}


void sendData(uint8_t data) {
    initializeCommunication();
    I2C_Write(CONTROL_DATA);
    I2C_Write(data);
    I2C_Stop();
}

void startHorizontalScrolling(uint8_t direction, uint8_t start, uint8_t end, uint8_t interval) {
    initializeCommunication();
    I2C_Write(CONTROL_COMMAND);
    I2C_Write(0x2E);
    I2C_Write(RIGHT_SCROLL + direction);
    I2C_Write(0x00);
    I2C_Write(start & 0x07);
    I2C_Write(interval & 0x07);
    I2C_Write(end & 0x07);
    I2C_Write(0x00);
    I2C_Write(0xFF);
    I2C_Write(0x2F);
    I2C_Stop();
}