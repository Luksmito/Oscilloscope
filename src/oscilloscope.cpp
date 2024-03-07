#include "oscilloscope.h"
#include "drawings.h"

typedef struct {
    float pointsToPlot;
    float interval;
    float columnsBetweenPoints;
    uint8_t actualPoint;
    uint8_t maxIndex;
}PlotAtributes;

Oscilloscope oscilloscope;

enum {
    TIPO1 = 0,
    TIPO2,
    TIPO7,
    TIPO8
};

void initializeOscilloscope(float timerPeriod, float timeToShow) {
    oscilloscope.timerPeriod = timerPeriod;
    oscilloscope.actualShowTimeLength = timeToShow;
    pinMode(INCREASE_TIME_TO_SHOW, INPUT_PULLUP);
    pinMode(DECREASE_TIME_TO_SHOW, INPUT_PULLUP);
}

//calculateSlopeHelper(x0, x1, y1, y0)
float calculateSlopeHelper(float a, float b, float c, float d) {
    float result = (b - a)/(c - d);
    return result;
}

float calculateSlope(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t tipo) {
    if (tipo == TIPO1) {
        return calculateSlopeHelper(y0, y1, x1, x0);
    } else if (tipo == TIPO8) {
        return -1 * calculateSlopeHelper(y0, y1, x1, x0);
    } else if (tipo == TIPO7) {
        return -1 * calculateSlopeHelper(x0, x1, y1, y0);
    } else {
        return calculateSlopeHelper(x0, x1, y1, y0);
    }
}

uint8_t myMap(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float myMapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float calculatePointsToPlot() {
    float pointsToPlot = oscilloscope.actualShowTimeLength / oscilloscope.timerPeriod;
    return (pointsToPlot > 100) ? 100 : pointsToPlot;
}


float calculateInterval(float pointsToPlot) {
    float interval = 1;
    if (pointsToPlot > 100) {
        interval = pointsToPlot / 100;
    }
    return interval;
}

float calculateColumnsBetweenPoints(float pointsToPlot) {
    float columnsBetweenPoints = 109 / pointsToPlot;
    return (columnsBetweenPoints < 1) ? 1 : columnsBetweenPoints;
}


uint16_t mapValueToScreen(uint8_t value) {
    return myMap(value, 0, 255, 55, 8);
}

uint8_t determineLineType(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    if (x1 > x0 && y1 > y0 && abs(y1 - y0) >= abs(x1 - x0)) {
        return TIPO2;
    } else if (x1 > x0 && y1 < y0 && abs(y1 - y0) >= abs(x1 - x0)) {
        return TIPO7;
    } else if (x1 > x0 && y1 < y0 && x1 <= y1) {
        return TIPO8;
    } else {
        return TIPO1;
    }
}

void drawLine(uint8_t matrix[COLUMNS_TO_WRITE][7],uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    uint8_t tipo = determineLineType(x0,y0,x1,y1);
    float slope = calculateSlope(x0,y0,x1,y1,tipo);
    float err = 0;

    if (tipo == TIPO1) {
        while (x0 < x1) {
            drawPixelInMatrix(matrix, x0,y0);
            err += slope;
            if (err >= 1) {
                err = err-1;
                y0+=1;
                
            }
            x0++;
        }
    } else if (tipo == TIPO8) {
        while (x0 < x1) {
            drawPixelInMatrix(matrix, x0,y0);
            err += slope;
            if (err >= 1) {
                err = err-1;
                y0-=1;
            }
            x0++;
        }
    } else if (tipo == TIPO7) {
        while (x0 < x1) {
            drawPixelInMatrix(matrix, x0,y0);
            err += slope;
            if (err >= 1) {
                err = err-1;
                x0++;
            }
            y0-=1;
        }
    } else if (tipo == TIPO2) {
        while (x0 < x1) {
            drawPixelInMatrix(matrix, x0,y0);
            err += slope;
            if (err >= 1) {
                err = err-1;
                x0++;
            }
            y0+=1;
        }
    }
}

void verifyButtons() {
    if (digitalRead(INCREASE_TIME_TO_SHOW) == LOW) {
        oscilloscope.actualShowTimeLength += 0.00005;
    } else if (digitalRead(DECREASE_TIME_TO_SHOW) == LOW) {
        oscilloscope.actualShowTimeLength -= 0.00005;
    }
    if (oscilloscope.actualShowTimeLength > POINTS_SAMPLED*PERIODO_TIMER*50) {
        oscilloscope.actualShowTimeLength = POINTS_SAMPLED*PERIODO_TIMER*50;
    } else if (oscilloscope.actualShowTimeLength < PERIODO_TIMER*2) {
        oscilloscope.actualShowTimeLength = 2*PERIODO_TIMER;
    }
}


void drawPlotInScreen(uint8_t screen[COLUMNS_TO_WRITE][7]) {
    setColumnAddress(COLUMN_INIT_SIGNAL_DRAW, N_COLUMNS-1);
    setPageAddress(1,N_PAGES-1);
    drawMatrix(screen, COLUMNS_TO_WRITE, 7);
}

void setIndexes(uint8_t indexList[4], float interval, float index) {
    for (uint8_t i = 0; i < 4; i++) {
        indexList[i] = index + (interval*i);
    }
}

void setPoints(PlotAtributes *plotAtributes, Point* p0, Point* p1, Point* p2, Point* p3, uint8_t signal[POINTS_SAMPLED], uint8_t indexes[4]) {
    p0->x = plotAtributes->actualPoint * plotAtributes->columnsBetweenPoints;
    plotAtributes->actualPoint++;
    p0->y = mapValueToScreen(signal[indexes[0]]);

    p1->x = plotAtributes->actualPoint * plotAtributes->columnsBetweenPoints;
    plotAtributes->actualPoint++;
    p1->y = mapValueToScreen(signal[indexes[1]]);

    p2->x = plotAtributes->actualPoint * plotAtributes->columnsBetweenPoints;
    plotAtributes->actualPoint++;
    p2->y = mapValueToScreen(signal[indexes[2]]);

    p3->x = plotAtributes->actualPoint * plotAtributes->columnsBetweenPoints;
    p3->y = mapValueToScreen(signal[indexes[3]]);
    plotAtributes->actualPoint-=2;
}


void setPlotAtributes(PlotAtributes * plotAtributes) {
    plotAtributes->pointsToPlot = oscilloscope.actualShowTimeLength / oscilloscope.timerPeriod;
    plotAtributes->interval = calculateInterval(plotAtributes->pointsToPlot);
    plotAtributes->columnsBetweenPoints = calculateColumnsBetweenPoints(plotAtributes->pointsToPlot);
    plotAtributes->maxIndex = plotAtributes->pointsToPlot * plotAtributes->interval;
    plotAtributes->actualPoint = 0;
}

void plotPointsInScreen(uint8_t screen[COLUMNS_TO_WRITE][7], uint8_t signal[POINTS_SAMPLED]) {
    PlotAtributes plotAtributtes;
    setPlotAtributes(&plotAtributtes);

    float index = plotAtributtes.interval;

    Point point1;
    Point point2;
    Point point3;
    Point point4;

    uint8_t indexes[4];
    
    float t_interval = 1/(plotAtributtes.columnsBetweenPoints*8);
    while (index < plotAtributtes.maxIndex && index < POINTS_SAMPLED - 4) {
        setIndexes(indexes, plotAtributtes.interval, index);
        setPoints(&plotAtributtes, &point1, &point2, &point3, &point4, signal, indexes);
        index ++;
        float t = 0; 
        while (t <= 1) {
            Point res = catmullRomInterpolation(point1, point2, point3, point4, t);
            if (res.y > 55) res.y=55.0;
            if (res.y < 8) res.y=8;
            drawPixelInMatrix(screen, (int) res.x, (int) res.y);
            
            t += t_interval;
         
        }
        
        
    }
}

/*void plotPointsInScreen(uint8_t screen[COLUMNS_TO_WRITE][7], uint8_t signal[POINTS_SAMPLED]) {
    float pointsToPlot = oscilloscope.actualShowTimeLength / oscilloscope.timerPeriod;
    float intervalo = calculateInterval(pointsToPlot);
    float columnsBetweenPoints = calculateColumnsBetweenPoints(pointsToPlot);

    float index = intervalo;
    int indexConverted = (int) index;
    int indexBefore = 0;
    uint16_t point = 0;
    
    do {
        uint16_t x0 = point*columnsBetweenPoints;
        uint16_t x1 = (point+1)*columnsBetweenPoints;
        
        if (x1 > 109) x1 = 109;
        
        uint16_t y0 = mapValueToScreen(signal[indexBefore]);
        uint16_t y1 = mapValueToScreen(signal[indexConverted]);

        point++;
        index += intervalo;
        indexBefore = indexConverted;
        indexConverted = (int) index;
              
        drawLine(screen, x0, y0, x1, y1);
    } while (point < pointsToPlot && index < POINTS_SAMPLED);
}*/


void drawSignal(uint8_t signal[POINTS_SAMPLED]) {
    drawTimeToShow(oscilloscope);
    uint8_t screen[COLUMNS_TO_WRITE][7] = {0};
    plotPointsInScreen(screen, signal);
    drawPlotInScreen(screen);
}
