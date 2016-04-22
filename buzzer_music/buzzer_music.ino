// 效果
// 播放三种音乐，电位器可调整播放哪种音乐和音调
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

#include <pitches.h>
int buzzer = 11;
int potPin = A0;

typedef struct {
  int note;
  int duration;
  int is_end;
} melody_t;

melody_t melody_1[] = {
  { 0, 4 },
  { NOTE_A5, 8 },
};
size_t nmelody_1 = sizeof(melody_1) / sizeof(melody_t);

melody_t melody_2[] = {
  { NOTE_E4, 8 },
  { NOTE_E4, 8 },
  { NOTE_F5, 4 },
  { NOTE_C5, 4 },
  { NOTE_C3, 4 },
  { NOTE_C5, 2 }
};
size_t nmelody_2 = sizeof(melody_2) / sizeof(melody_t);

melody_t melody_3[] = {
  { NOTE_D7, 4 },
  { NOTE_D7, 4 },
  { 0, 2 },
  { NOTE_D7, 4 },
  { NOTE_D7, 4 },
};
size_t nmelody_3 = sizeof(melody_3) / sizeof(melody_t);

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  melody_t* melody = NULL;
  size_t nmelody = 0;
  int val = analogRead(potPin);
  Serial.println(val);
  if (val > 0 && val <= 300) {
    melody = melody_1;
    nmelody = nmelody_1;
  } else if (val > 300 && val <= 600) {
    melody = melody_2;
    nmelody = nmelody_2;
  } else if (val > 600) {
    melody = melody_3;
    nmelody = nmelody_3;
  }
  for (int i = 0; i < nmelody; ++i) {
    int note = melody[i].note;
    int noteDuration = 1000 / melody[i].duration;
    tone(buzzer, note == 0 ? 0 : (note + val % 300), noteDuration);
    delay(noteDuration * 1.3);
    noTone(buzzer);
  }
  delay(1000);
}

