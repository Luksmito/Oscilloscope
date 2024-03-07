/* 
 * File:   graphics.h
 * Author: lucas
 *
 * Created on 9 de Janeiro de 2024, 23:40
 */

#ifndef GRAPHICS_H
#define	GRAPHICS_H


#include "oledi2c_ssd1306.h"
#include <Arduino.h>


#if defined(I2C_BUFFER_LENGTH)
#define WIRE_MAX min(256, I2C_BUFFER_LENGTH) ///< Particle or similar Wire lib
#elif defined(BUFFER_LENGTH)
#define WIRE_MAX min(256, BUFFER_LENGTH) ///< AVR or similar Wire lib
#elif defined(SERIAL_BUFFER_SIZE)
#define WIRE_MAX                                                               \
  min(255, SERIAL_BUFFER_SIZE - 1) ///< Newer Wire uses RingBuffer
#else
#define WIRE_MAX 32 ///< Use common Arduino core default
#endif
#define N_SPRITES_PER_LINE 16
#define HEIGHT 64


void sendSprite(uint8_t sprite, uint8_t inverted);

void sendSprite8x8(const uint8_t sprite[8], uint8_t inverted);

uint8_t posCursorIsValid(uint8_t x, uint8_t y);

void clearDisplay();

void drawPixel(uint8_t x, uint8_t y);

#endif	/* GRAPHICS_H */

