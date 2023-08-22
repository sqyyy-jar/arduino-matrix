#include "LedControl.h"
#include "Matrix.c"

const int joystick_x = A3;
const int joystick_y = A2;
const int joystick_btn = 0;

LedControl lc(12, 11, 10, 1);
Dot dot;

void draw_dot();

void setup() {
  Serial.begin(9600);
  // Joystick einstellen
  pinMode(joystick_btn, INPUT);
  pinMode(joystick_x, INPUT);
  pinMode(joystick_y, INPUT);
  // digitalWrite(joystick_btn, HIGH);
  // LED-Matrix einstellen
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  // Punkt einstellen
  dot.position = {.x = MAT_VWIDTH / 2, .y = MAT_VWIDTH / 2};
  dot.velocity = {.x = 0, .y = 0};
}

void loop() {
  int xAxis = analogRead(joystick_x);
  int yAxis = analogRead(joystick_y);
  int btn = digitalRead(joystick_btn);
  // if (xAxis > 500) {
  //   lc.setLed(0, 0, 0, true);
  // } else if (xAxis < 500) {
  //   lc.setLed(0, 2, 0, true);
  // }
  // if (yAxis > 500) {
  //   lc.setLed(0, 0, 6, true);
  // } else if (yAxis < 500) {
  //   lc.setLed(0, 2, 6, true);
  // }
  if (btn) {
    // randomize_dir();
  }
  dot_move(&dot);
  lc.clearDisplay(0);
  draw_dot();
  delay(50);
}

void draw_dot() {
  Vec2 screenPos = vec_convert(&dot.position);
  Serial.print(screenPos.x);
  Serial.print(":");
  Serial.println(screenPos.y);
  lc.setLed(0, screenPos.x, screenPos.y, true);
}

void randomize_dir() {
  Vec2 vel = {.x = random(-10, 11), .y = random(-10, 11)};
  vel.x *= 100;
  vel.y *= 100;
  int len = sqrt(vel.x * vel.x + vel.y * vel.y);
  int w_len = 3;
  vel.x = vel.x * w_len / len;
  vel.y = vel.y * w_len / len;
  dot.velocity = vel;
}
