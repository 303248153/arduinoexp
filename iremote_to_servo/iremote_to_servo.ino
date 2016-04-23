// 效果
// 红外遥控器控制舵机，按下+时逆时针转，按下-时顺时针转
//
// 提示找不到TKD2时
// 原因是因为RobotIRremote库中的ITremoteTools需要这个macro，但是这个macro只有部分硬件的环境会定义
// 解决办法是重命名IRremoteTools.cpp和IRremoteTools.h，让编译器跳过这些文件
// 
// 接线说明
// 舵机 红线正极 黑线负极 黄线数据
// 正极 => +
// 负极 => -
// 数据 => 3
// 红外接收器
// 正面是是半圆反面刻字，正面从左到右是数据，负极，正极
// 正极 f19, j19 =>  +
// 负极 f20, j20 => -
// 数据 f21, j21 => 4
// 电源
// 5V => +
// GND => -

#include <Servo.h>
#include <IRremote.h>

int servoPin = 3;
int irPin = 4;
Servo servo;
IRrecv irrecv(4);
unsigned long last_result = 0;
unsigned int repeat_count = 0;
unsigned int servo_max_position = 2400;
unsigned int servo_min_position = 544;
unsigned int servo_position = servo_min_position + servo_max_position / 2;

void setup() {
  servo.attach(servoPin, servo_min_position, servo_max_position);
  servo.write(servo_position);
  irrecv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  decode_results result;
  if (irrecv.decode(&result)) {
    // 0xFFFFFFFF mean the last key is pressed
    // the first repeat should ignore
    unsigned long key = 0;
    if (result.value == 0xFFFFFFFF) {
      key = (++repeat_count > 1) ? last_result : 0;
    } else {
      last_result = key = result.value;
    }
    
    // set servo position by pressed key
    // + is FF02FD, - is FF9867
    if (key == 0xFF02FD) {
      servo_position = min(servo_max_position, servo_position + 100);
    } else if (key = 0xFF9867) {
      servo_position = max(servo_min_position, servo_position - 100);
    }
    servo.write(servo_position);
    
    // print information and reset receiver
    Serial.print(key, HEX);
    Serial.print(" ");
    Serial.println(servo_position);
    irrecv.resume();
  }
  delay(1);
}

