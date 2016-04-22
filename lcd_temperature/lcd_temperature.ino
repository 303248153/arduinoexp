// 效果
// 在lcd1602的屏幕上打印出当前温度和湿度
// 
// 接线说明
// DHT11
// VCC j23, f23 => +
// DAT j24, 4.7K电阻 f24 => +, g24 => 8
// NC j25, f25 => -
// GND j26, f26 => -
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
#include <dht.h>

LiquidCrystal lcd(12, 13, 4, 5, 6, 7);
int dht11Pin = 8;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  int temperature = 0;
  int humidity = 0;
  int ret = dht_read11(dht11Pin, &temperature, &humidity);
  if (ret == 0) {
    Serial.print(temperature);
    Serial.print(" ");
    Serial.println(humidity);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print((int)temperature);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Humi: ");
    lcd.print((int)humidity);
    lcd.print("%");
  } else if (ret == -1) {
    Serial.println("checksum error");
  } else if (ret == -2) {
    Serial.println("timeout");
  } else {
    Serial.print("unknow ret ");
    Serial.println(ret);
  }
  delay(500);
}

