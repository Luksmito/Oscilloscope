/* 
 * File:   oledi2c_ssd1306.h
 * Author: lucas
 *
 * Created on 9 de Janeiro de 2024, 20:52
 */

#ifndef OLEDI2C_SSD1306_H
#define	OLEDI2C_SSD1306_H

#include "I2C_functions.h"

#define ADDRESS 0x3C
#define N_PAGES 8
#define N_COLUMNS 128
#define N_BITS_PER_PAGE 8

#define CONTROL_COMMAND 0x00
#define CONTROL_DATA 0x40
#define DISPLAY_ON 0xAF
#define SET_HORIZONTAL_ADDRESSING_MODE 0x20
#define COMMAND_SET_PAGE_ADDRESS 0x22
#define COMMAND_COLUMN_ADDRESS 0x21
#define CLEAR_DISPLAY 0xA4
#define TURN_ON_WHOLE_DISPLAY 0xA5
#define RIGHT_SCROLL 0x26
#define LEFT_SCROLL 0x27


void initializeCommunication();

void sendCommand(uint8_t command);

void setPageAddress(uint8_t start, uint8_t end);

void setColumnAddress(uint8_t start, uint8_t end);

void initializeOLED();

void setHorizontalAddressingMode ();

void sendData(uint8_t data);

void startHorizontalScrolling(uint8_t direction, uint8_t start, uint8_t end, uint8_t interval);

#endif	/* OLEDI2C_SSD1306_H */

