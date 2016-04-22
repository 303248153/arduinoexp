// 效果
// 周围光线不足时点亮LED灯，光线足够时关闭LED灯
// 注意光敏电阻会受到LED灯本身的影响
//
// 接线说明
// 光敏电阻
// 两个脚不区分，分别接j11和j13
// 正极 5V => F11
// 负极 电阻 (10K) h13 => h21, j21 => -, - => GND
//      读取电压值 f13 => A0
// LED
// 正极 j26, 电阻(1K) i26 => e26, d26 => 11
// 负极 -

int resistorPin = A0;
int ledPin = 11;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ret = analogRead(resistorPin);
  Serial.println(ret);
  if (ret < 512) { // (2.5V) use which value dependent on environment
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(100);
}

