// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//      2013-05-08 - added multiple output formats
//                 - added seamless Fastwire support
//      2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;

char *ReplyArray[12] = {
  "Yes! For sure", "Nope. Never", "Maybe?", "Stop shaking me", "Would you ask a paper fortune teller that?", "Oh definitely not", "Abso-freaking-lutely", "I'm not sure, but I believe in you!", "You should have learned that in EE305", "Ask Dr. Dvorak", "Ask Toby-I mean Robbie", "6d 61 64 65 20 79 6f 75 20 6c 6f 6f 6b 20 68 61 68 61"
};                      //the array of possible replies

// const int ACC = A4 && A5;     //the accelerometer is connected to pin A4
float thresholdx = -2600;  //threshold the sensor must surpass to activate reply


#define LED_PIN 13
bool blinkState = false;

const int buttonPin = 1;      // button connected to pin 1
const int displayScreen = 13; // display connected to pin 13

int button;                   // the button is variable
int oldButton = 0;            // the button's initial state is zero
int state = 0;


void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

 pinMode(buttonPin, INPUT);
 pinMode(displayScreen, OUTPUT);

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


    // configure Arduino LED pin for output
    pinMode(LED_PIN, OUTPUT);
}

void loop() {

digitalRead(buttonPin);
 if(button && !oldButton)      // same as if(button == high && oldbutton == low)
 {                             // ^comment from forum I got the code from. think it means
                                   // the button used to be inactive and is now active
                                   // so the button was pushed
   if(state == 0)              // if the state was "off"
   {
     digitalWrite (13, HIGH);  // sends voltage to the screen
     state = 1;                // turns the state "on"
   }
   else                        // if the state was "on"
   {
     digitalWrite (13, LOW);   // sends no voltage to the screen
     state = 0;                // turns the state "off"
   }
   oldButton = 1;              // changes button's state from 0 to 1. becomes the "old" state
 }
 else if(!button && oldButton) // same as if(button == low && oldbutton == high)
 {                             // ^from forum. based on the if statement, think it means
                                   // the button used to be active and is now inactive
                                   // so the button was released
   oldButton = 0;              // returns the button state to its initial state
 }

    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);
    

float sensorValueAccelerometer = analogRead(A4 && A5); //naming a variable for what the sensor is reading

// Serial.println (sensorValueAccelerometer);       //printing what the sensor is reading
String Reply = ReplyArray[random(12)];           //assigning "Reply" variable to be random choice from array
if (ax > thresholdx){
  delay (1500);
  
  Serial.println (Reply);                        //printing "Reply" if sensor reads beyond threshold
}
delay (1000);                                    //delay for testing

    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        //Serial.print("a/g:\t");
        //Serial.print(ax); Serial.print("\t");
       // Serial.print(ay); Serial.print("\t");
       // Serial.println(az); Serial.print("\t");

       // delay (1000);
    #endif

    #ifdef OUTPUT_BINARY_ACCELGYRO
        Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));

        delay (1000);
    #endif
    
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
