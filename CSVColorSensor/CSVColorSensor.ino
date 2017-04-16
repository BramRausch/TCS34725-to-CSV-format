#include <Wire.h>
#include "Adafruit_TCS34725.h"
   
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

int buttonState;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup(void) {
  Serial.begin(9600);
  tcs.begin();

  pinMode(D4, INPUT_PULLUP);
  Serial.println("Color Temp,Lux,R,G,B,C");
}

void loop(void) {
  int reading = digitalRead(D4);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        for(int i = 0; i < 10; i++){
          uint16_t r, g, b, c, colorTemp, lux;
    
          tcs.getRawData(&r, &g, &b, &c);
          colorTemp = tcs.calculateColorTemperature(r, g, b);
          lux = tcs.calculateLux(r, g, b);
  
          Serial.print(colorTemp);
          Serial.print(",");
          Serial.print(lux);
          Serial.print(",");
          Serial.print(r);
          Serial.print(",");
          Serial.print(g);
          Serial.print(",");
          Serial.print(b);
          Serial.print(",");
          Serial.print(c);
        
          Serial.println();
        }
      }
    }
  }
  
  lastButtonState = reading;
}
