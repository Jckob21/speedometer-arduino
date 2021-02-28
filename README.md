# speedometer-arduino

author: https://github.com/Jckob21
contributors: https://github.com/Michalele2115, https://github.com/wiku0321
This program allows to measure speed using two photoresistors.

The circuit should consist of:
- 2 photoresistors
- 2 resistors (1k)
- lcd (optional)
- adapter I2C (optional)

You can just use serial port monitor instead of LCD.
To use LCD without I2C converter change the library and initializing in setup method.

To configure the program:
1. Measure distance between two photoresistors and change the constant "distance".
2. Set reasonable lightBoundary so the program can easily catch light interuption.
3. Use A1 port for first photoresistor and A2 port for second one.

Hope you enjoy it!
version 1.0
