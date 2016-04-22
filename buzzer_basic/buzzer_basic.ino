// 效果
// 根据电位器传入的参数调整蜂鸣器的声音频率
// 
// 接线说明
// 电位器
// 三个脚分别插a18, a20, a22
// 电源 a22, e22 => 5V
// 数据 a20, e20 => A0
// 地线 a18, e18 => GND
// 蜂鸣器
// 正极 a29, e29 => 11
// 负极 a26, e26 => d18

int buzzer = 11;
int potPin = A0;

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(potPin);
  Serial.println(val);
  if (val == 0) {
    delay(100);
    return;
  }
  int ms = val >= 512 ? 1 : 2;
  for (int i = 0, j = val / ms; i < j; ++i) {
    digitalWrite(buzzer, HIGH);
    delay(ms);
    digitalWrite(buzzer, LOW);
    delay(ms);
  }
  delay(100);
}

