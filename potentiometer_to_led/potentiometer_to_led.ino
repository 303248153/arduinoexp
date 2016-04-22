// 效果
// 电位器控制LED灯亮度
//
// 接线说明
// 电位器
// 三个脚分别插a26, a28, a30，电位器不分电源和地线
// 电源 a26, e26 => 5V
// 数据 a28, e28 => A5
// 地线 a30, d30 => GND
// LED
// 正极 a15，负极 a17
// 电阻 (1K) b15 => i15
// 电源 j15 => 3
// 地线 e17 => e30

int ledPin = 3;
int analogPin = A5;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(analogPin);
  Serial.println(val);
  analogWrite(ledPin, val/4);
  delay(100);
}

