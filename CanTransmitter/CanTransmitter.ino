// CAN
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);

// pots
#define potPin0 A3
#define potPin1 A2
#define potPin2 A1

int potValue0 = 0;
int potValue1 = 0;
int potValue2 = 0;


void setup() {
  Serial.begin(9600);

  // CAN setup
  SPI.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  canMsg.can_id = 0x036;
  canMsg.can_dlc = 3;
}

void loop() {
  potValue0 = analogRead(potPin0);
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);

  potValue0 = map(potValue0, 0, 1023, 0, 255);
  potValue1 = map(potValue1, 0, 1023, 0, 255);
  potValue2 = map(potValue2, 0, 1023, 0, 255);

  Serial.print("The pot values being sent are: ");
  Serial.print(" ");
  Serial.print(potValue0);
  Serial.print(" and ");
  Serial.print(potValue1);
  Serial.print(" and ");
  Serial.println(potValue2);

  // place data in CAN message array
  canMsg.data[0] = potValue0;
  canMsg.data[1] = potValue1;
  canMsg.data[2] = potValue2;

  mcp2515.sendMessage(&canMsg);
  delay(200);
}
