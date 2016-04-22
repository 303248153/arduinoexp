// 效果
// LED灯轮流闪
//
// 接线说明
// 电源
// 2 => 2j, 3 => 3j, ..., 7 => 7j
// 电阻 (1K)
// 2i => 2b, 3i => 3b, ..., 7i => 7b
// LED
// 2a => -, 3a => -, ..., 7a => -
// 地线
// GND => -

int startPin = 2;
int nPins = 6;
int index = 0;

void setup() {
  for (int i = startPin, j = startPin + nPins; i < j; ++i) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int prevIndex = (index == 0 ? nPins : index) - 1;
  Serial.print("switch to ");
  Serial.print(index);
  Serial.println();
  digitalWrite(startPin + prevIndex, LOW);
  digitalWrite(startPin + index, HIGH);
  index = (index + 1) % nPins;
  delay(1000);
}

