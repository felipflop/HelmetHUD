// OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define pushBut 3

int power = 0;
int rectWidth = 0;
int randomNum1 = 0;
int randomNum2 = 0;

int checkVal(int data);
void checkBut();
int but = 0;
int lastBut = 0;

void setup() {

  pinMode(pushBut, INPUT);

  Serial.begin(9600);
  oledSetup();
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();

  but = digitalRead(pushBut);

  if (but > lastBut) {
    randomNum1=random(0,100);
    randomNum2=random(0,100);
    Serial.print(randomNum1);
    Serial.print("       ");
    Serial.println(millis());
    power  = randomNum2;
  }

  lastBut = but;

  /*if (digitalRead(pushBut == HIGH)) {
    power = random(0, 100);
    }
  */

  if (power >= 0 && power < 10) {
    display.setCursor(59, 0);
  }

  else {
    display.setCursor(50, 0);
  }

  display.setTextSize(3.5);
  display.print(power);
  display.setCursor(55, 30);
  display.setTextSize(2);
  display.print("kW");
  display.fillRect(6, 55, rectWidth, 7, WHITE);
  display.flipHoriz();
  display.display();

  delay(100);


}

void oledSetup() {

  // ensures I2C allocation is valid
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

/*int checkVal(int data) {

  if (Serial.available() > 0) {

    data = Serial.parseInt(SKIP_WHITESPACE);
    power = data;
    int randomNum = random(0, 100);
    int count = 0;
    int placeholder = randomNum;
    int millisec = millis();

    while (randomNum == placeholder && count == 1) {
      randomNum = random(0, 100);
    }

    Serial.print(randomNum);
    Serial.print("   ");
    Serial.println(millisec);
    while (Serial.available() > 0) {
      Serial.read();
    }

    count++;

    if (count == 2) {
      count = 0;
    }
  }
  }
*/
