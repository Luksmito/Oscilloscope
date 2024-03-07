# Oscilloscope
A oscilloscope made with Arduino that measure from -5V to 5V. it is a job in progress.

Basically this project uses the TIMER0 from atmega328 to sample the signal, and when the samples are complete draw it in the screen.
The algorithm used to draw the signal on the screen is the catMullRom, a type of spline that contains all the points passed by argument
