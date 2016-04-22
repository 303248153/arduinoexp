// 效果
// 在lcd1602的屏幕上打印出hello world，并向左滚动
//
// 接线说明
// LCD1602
// VSS => c1, e1 => -
// VDD => c2, e2 => +
// V0 => c3, 1K电阻 e3 => -
// RS => c4, e4 => 12
// RW => c5, e5 => -
// E => c6, e6 => 13
// D0~D3不接
// D4 => c11, e11 => 4
// D5 => c12, e12 => 5
// D6 => c13, e13 => 6
// D7 => c14, e14 => 7
// A => c15, e15 => +
// K => c16, 1K电阻 e16 => -
// 正负极
// 5V => +
// GND => -

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 13, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2); // columns 16, rows 2
}

void loop() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("hello world");
  for (int i = 0; i < 15; ++i) {
    delay(300);
    lcd.scrollDisplayLeft();
  }
}

