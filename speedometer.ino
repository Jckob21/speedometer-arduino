/*  author: https://github.com/Jckob21
 *  contributors: https://github.com/Michalele2115, https://github.com/wiku0321
 *
 *  This program allows to measure speed using two photoresistors.
 *  
 *  The circuit should consist of:
 *  - 2 photoresistors
 *  - 2 resistors (1k)
 *  - lcd (optional)
 *  - adapter I2C (optional)
 * 
 *  You can just use serial port monitor instead of LCD.
 *  To use LCD without I2C converter change the library and lcd initializing in setup.
 *  
 *  To configure the program:
 *  1. Measure distance between two photoresistors and change the constant "distance".
 *  2. Set reasonable lightBoundary so the program can easily catch light interuption.
 *  3. Use A1 port for first photoresistor and A2 port for second one.
 *  
 *  Hope you enjoy it!
 *  version 1.0
 */


//////////////////////////////// LCD ///////////////////////////////////////

// you can just use normal LiquidCrystal library if you don't use I2C adapter
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

////////////////////////// PROGRAM VARIABLES ///////////////////////////////

double time1;
double time2;
double timeInterval;
double speedCalculated;

////////////////////////////// SETTINGS ////////////////////////////////////

/* this is light boundary of light sensor, if you are using
 * laser the boundary can be higher (the speedometer will be more accurate)
 */
const double lightBoundary = 250;

//this is the distance between your 2 light sensors given in cm
const double distance = 14.0;


void setup() {
  // UART initialization (for easier light boundary detection etc)
  Serial.begin(9600);

  // lcd initialization
  lcd.init();
  lcd.backlight();
  lcd.setCursor(6,0);
  lcd.print("0.00");
  lcd.setCursor(6,1);
  lcd.print("km/h");
}

void loop() {
  //first photoresistor catch light interuption
  if(analogRead(A1) < lightBoundary)
  {
    time1 = millis();
    Serial.println("First resistor light absorption interupted");

    //wait for second photoresistor light interuption
    while(analogRead(A2) > lightBoundary)
    {
      delay(1);
    }
    
    time2 = millis();
    Serial.println("Second resistor light absorption interupted");

    //calculate time difference
    timeInterval = abs(time2 - time1);

    Serial.print("Time difference: ");
    Serial.print(timeInterval);
    Serial.println("ms.");

    //calculate speed (currently km/h, see below for different speed measures)
    speedCalculated = (distance / timeInterval) * 36;

    Serial.print("Calculated speed: ");
    Serial.println(speedCalculated);
    Serial.println();

    //clean LCD first row
    lcd.setCursor(6,0);
    lcd.print("       ");

    //print speed
    lcd.setCursor(6,0);
    lcd.print(speedCalculated);
    delay(200);
  }
}

/*  Calculating different speed measures:
 * cm/s -> speedCalculated = distance / timeInterval / 1000
 * km/h -> speedCalculated = (distance / timeInterval) * 36 (used in the code)
 * feel free to commit new speed measures :)
 */
