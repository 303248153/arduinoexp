// 效果
// 舵机轮流摆动
//
// 接线说明
// 舵机 红线正极 黑线负极 黄线数据
// 正极 => 5V
// 负极 => GND
// 数据 => 3

int servoPin = 3;

void setup() {
  pinMode(servoPin, OUTPUT);
}

void setServoPosition(int pin, int pos) {
  for (int i = 0; i < 5; ++i) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pos);
    digitalWrite(pin, LOW);
    delay(20);
  }
}

void loop() {
  for (int pos = 1000; pos <= 2500; pos += 100) {
    setServoPosition(servoPin, pos);
    delay(100);
  }
  for (int pos = 2500; pos >= 1000; pos -= 100) {
    setServoPosition(servoPin, pos);
    delay(100);
  }
}

