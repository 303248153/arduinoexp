// 效果
// 按下亮灯，再按下关灯，按键可切换LED灯状态
//
// 接线说明
// 按键有四个脚，在同一条线上的脚会一直通电，不同线上的脚按下时通电
// 不同线上的脚一端接h14，另一端接h16
// 然后j14接-，-接GND，i14接11
// LED
// h21接12，LED正极接i21，负极接-
// 按键按下时会读取到LOW，目前使用PULLUP模式因为这个模式更稳定

int buttonPin = 11;
int ledPin = 12;
int ledState = LOW;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ret = digitalRead(buttonPin);
  if (ret == LOW) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    delay(500);
  }
}

