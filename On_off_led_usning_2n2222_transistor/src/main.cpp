#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

#define transistorBase A2 

void setup() {
    pinMode(transistorBase, OUTPUT);
    Serial.begin(9600);
    Wire.begin();
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void loop() {
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    if (rtc.now().second() % 3 == 0) {
    digitalWrite(transistorBase, HIGH);  // Turn on LED
      } else {
    digitalWrite(transistorBase, LOW);  // Turn off LED
      }
      
  delay(1000);
}
