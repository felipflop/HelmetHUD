#define one 8
#define two 9
#define three 10
#define four 11


void setup() {
  Serial.begin(9600);

  pinMode(one,OUTPUT);
  pinMode(two,OUTPUT);
  pinMode(three,OUTPUT);
  pinMode(four,OUTPUT);
  

}

void loop() {

  Serial.print(one);
  Serial.print(two);
  Serial.print(three);
  Serial.print(four);

}
