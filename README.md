# Oscilloscope
The oscilloscope, made with Arduino, measures from -5V to 5V. It is a work in progress.

Basically, this project uses TIMER0 from the ATmega328 to sample the signal. When the samples are complete, it draws them on the screen. The algorithm used to draw the signal on the screen is Catmull-Rom, a type of spline that contains all the points passed as arguments.
