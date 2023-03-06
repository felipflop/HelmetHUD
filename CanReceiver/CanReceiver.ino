// CAN
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(5);//Chip Select Pin 5

// OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Bitmaps.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// push button declaration
#define ButtonPinL 14
#define ButtonPinR 15

// CAN fault LED
#define CANfaultPin 1

// tracks display selection state
int Selection = 0;

// function prototypes
void oledSetup();
void canSetup();
void checkSelection();


void setup() {
  Serial.begin(9600);

  canSetup();
  oledSetup();

  //Button 
  pinMode(ButtonPinL, INPUT);
  pinMode(ButtonPinR, INPUT);
  pinMode(CANfaultPin, OUTPUT);
  digitalWrite(CANfaultPin, LOW);
}


void loop() {

  // checks to see if CAN is supported
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {

    // checks transmitting node's id
    if (canMsg.can_id == 0x036) {
      digitalWrite(CANfaultPin, LOW);
      int x = canMsg.data[0];
      int y = canMsg.data[1];
      int z = canMsg.data[2];
      checkSelection();

      //display 0
      if (Selection == 0) {
        // display information here
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.print("x: ");
        display.setTextSize(2);
        display.setCursor(0, 20);
        display.print(x); //variable 0
        display.print(" unit");
        //display.flipHoriz();
      }

      // display 1
      else if (Selection == 1) {
        // display information here
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.print("y: ");
        display.setTextSize(2);
        display.setCursor(0, 20);
        display.print(y); //variable 1
        display.print(" unit");
        //display.flipHoriz();
      }

      // display 2
      else if (Selection == 2) {
        // display information here
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.print("z: ");
        display.setTextSize(2);
        display.setCursor(0, 20);
        display.print(z); //variable 2
        display.print(" unit");
        //display.flipHoriz();
      }
    }
  }
  
  //CAN error procedure
  else {
    digitalWrite(CANfaultPin, HIGH);
    Serial.println("Nothing Received...");
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Nothing");
    display.print("received");
    //display.flipHoriz();
  }
  
  display.display();
  delay(200);

}

void canSetup() {
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void oledSetup() {

  // ensures I2C allocation is valid
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // draws a scrolling bitmap of a helmet
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.drawBitmap(0, 0, Logo, 128, 64, WHITE);
  //display.flipHoriz();
  display.display();
  display.startscrollright(0, 7);
  delay(4300);

  // prints "HELMET HUD" in the centre of the display
  display.stopscroll();
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(13, 10);
  display.print("HELMET");
  display.setCursor(38, 40);
  display.print("HUD");
  display.display();
  delay(3000);
}

void checkSelection() {
  if (digitalRead(ButtonPinL) == HIGH) {
    Selection--;
    
    //latches the button
    while (digitalRead(ButtonPinL) == HIGH) {
      Selection = Selection;
    }

    if (Selection == -1) {
      Selection = 2;
    }
  }

  if (digitalRead(ButtonPinR) == HIGH) {
    Selection++;
    
    //latches button
    while (digitalRead(ButtonPinR) == HIGH) {
      Selection = Selection;
    }
    
    if (Selection == 3) {
      Selection = 0;
    }
  }
}
