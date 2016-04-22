// 效果
// 循环显示显示9, 8, 7, ... 0, 小数点
//
// 接线说明
// 共阳数码管SM41056，中间是COM，小数点在abc这边
// 上管脚 h13 ~ h17
// 下管脚 d13 ~ d17
// 正极 5v => a26
// 电阻 (1K) b26 => b15 (COM)
// 负极
// a17 => 0, a16 => 1, a14 => 2, a13 => 3
// j17 => 4, j16 => 5, j14 => 6, j13 => 7
// 接口对应LED
// |--5--|
// 6     4
// |--7--|
// 3     1
// |--2--|0

int startPin = 0;
int numericLedMask[] = {
  B01111110, // 0
  B00010010, // 1
  B10111100, // 2
  B10110110, // 3
  B11010010, // 4
  B11100110, // 5
  B11101110, // 6
  B00110010, // 7
  B11111110, // 8
  B11110110, // 9
};
int dotLedMask = B00000001;

void display(int mask) {
  for (int i = startPin, j = startPin + 7; i <= j; ++i) {
    int on = mask & (1 << (i - startPin));
    digitalWrite(i, on ? LOW : HIGH);
  }
}

void setup() {
  for (int i = startPin, j = startPin + 7; i <= j; ++i) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int i = 9; i >= 0; --i) {
    display(numericLedMask[i]);
    delay(1000);
  }
  for (int i = 0; i < 3; ++i) {
    display(dotLedMask);
    delay(500);
    display(0);
    delay(500);
  }
}

