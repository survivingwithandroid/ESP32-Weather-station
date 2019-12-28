#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BMP_SDA 21
#define BMP_SCL 22

Adafruit_BMP280 bmp280;
 Adafruit_SSD1306 display(128, 64, &Wire, -1);
 

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing BMP280");
  boolean status = bmp280.begin(0x76);
  if (!status) {
    Serial.println("Not connected");
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}


void loop() {
  float temp = bmp280.readTemperature();
  float press = bmp280.readPressure() / 100;

  Serial.println("Temperature:");
  Serial.println(temp);

  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Temperature:");
  display.println(temp);
  display.print("Pressure:");
  display.println(press);
  display.display();

  delay(6000);
}

