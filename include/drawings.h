#ifndef DRAWINGS_H
#define DRAWINGS_H

#include "graphics.h"

#define COLUMN_INIT_SIGNAL_DRAW 19
#define COLUMNS_TO_WRITE N_COLUMNS - COLUMN_INIT_SIGNAL_DRAW

typedef struct {
    float timerPeriod;
    float actualShowTimeLength;
} Oscilloscope;

typedef struct {
    float x;
    float y;
} Point;

/// @brief CatmullRom algorithm to draw splines
/// @param p0 first point
/// @param p1 second point
/// @param p2 third point
/// @param p3 fourth point
/// @param t parameter of the spline
/// @return Point for the given t
Point catmullRomInterpolation(Point p0, Point p1, Point p2, Point p3, float t);


/// @brief Takes a matrix representing the screen and draws it
/// @param matrix the representaiton of the screen
/// @param columns number of columns
/// @param pages number of pages
void drawMatrix(uint8_t matrix[COLUMNS_TO_WRITE][7], uint8_t columns, uint8_t pages);

/// @brief Draw in the screen the indicator of what period of time the screen is showing
/// @param oscilloscope The struct that represents the oscilloscope variables
void drawTimeToShow(Oscilloscope oscilloscope);


/// @brief Draw the axis on screen
void drawAxis();

/// @brief Reset all the screen after the given column
/// @param column the column which should start to reset
void clearDisplayFromColumnToEnd(uint8_t column);


/// @brief Sets a pixel in the given coordinates
/// @param matrix the representation of the screen;
/// @param x column
/// @param y line
void drawPixelInMatrix(uint8_t matrix[COLUMNS_TO_WRITE][7], uint8_t x, uint8_t y);
#endif