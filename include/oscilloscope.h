#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include "graphics.h"
#include "timer.h"
#include "analogDigitalConverter.h"
#include <math.h>

#define COLUMN_INIT_SIGNAL_DRAW 19
#define STEP_TIMER_CONTROL 0.0001
#define PERIODS_ON_SCREEN 2 
#define COLUMNS_TO_WRITE N_COLUMNS - COLUMN_INIT_SIGNAL_DRAW
#define POINTS_SAMPLED 250

#define INCREASE_TIME_TO_SHOW 5
#define DECREASE_TIME_TO_SHOW 4

/**
 * @brief Initializes the oscilloscope with the given timer period and time to show.
 * 
 * This function initializes the oscilloscope with the specified timer period.
 * timer period is the interval that the samples are made   
 * and time to show. It also configures the input pins for increasing and
 * decreasing the time to show.
 * 
 * @param timerPeriod The period of the timer.
 * @param timeToShow The duration of time to show.
 */
void initializeOscilloscope(float timerPeriod, float timeToShow);


/**
 * @brief 
 * 
 */
void verifyButtons();

/**
 * @brief Draws the axis on the display.
 * 
 * This function draws the axis on the display, including the vertical and horizontal
 * lines and labels for the axes.
 */
void drawAxis();

/**
 * @brief Draws the signal on the display.
 * 
 * This function draws the signal on the display, including the time to show, the plotted points,
 * and the plot itself.
 * 
 * @param signal The array containing the sampled points of the signal.
 */
void drawSignal(uint8_t signal[POINTS_SAMPLED]);


#endif