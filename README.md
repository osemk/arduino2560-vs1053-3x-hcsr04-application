# arduino2560-vs1053-3x-hcsr04-application

This is an arduino application that has VS1053 (music player module for arduino) and 3X HC-SR04 ultrasonic sensor (that can measure distance between sensor and things). 

I made this project for a restaurant chain in Turkey in 2018. We put sensores behind the mirrors in women toilets. If women stay in front of mirror for a long time, the application play sound to warn her to finish her job. The customer wanted this project because they researched that women are stay in toilet even they finish their job. I made this proeject in 2018 and they are still using this system in their over 100 branches women toilet.
There are 3 sounds in SD Card, it plays 3 sounds step by step.


# Compiling 

For VS1053 i used Adafruit_VS1053 lib (https://github.com/adafruit/Adafruit_VS1053_Library). 
Use serial 9600 port. Board at Com4

You can modify sensors pins according to your connection. 
