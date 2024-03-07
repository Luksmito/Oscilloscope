/* 
 * File:   I2C_functions.h
 * Author: lucas
 *
 * Created on 9 de Janeiro de 2024, 20:58
 */

#ifndef I2C_FUNCTIONS_H
#define	I2C_FUNCTIONS_H

#ifndef ADDRESS
#define ADDRESS 0x3C
#endif

#include <Wire.h>

void I2C_Start();

// Função para finalizar a comunicação I2C
uint8_t I2C_Stop();

// Função para enviar uma sequência de bytes via I2C
void I2C_Write(uint8_t dado);


#endif	/* I2C_FUNCTIONS_H */

