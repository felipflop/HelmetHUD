#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // ensures I2C allocation is valid
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
}

void loop() {
  
  display.setTextColor(WHITE);
  display.setTextSize(3.5);
  display.setCursor(45,0);
  display.print("53");
  display.setCursor(50,30);
  display.setTextSize(2);
  display.print("kW");
  display.fillRect(10,55,4,53,WHITE);
  display.display();
  delay(200);
  
}
