#include "LedControl.h"
#include "Matrix.c"
#include "types.h"

const int joystick_x = A3;
const int joystick_y = A2;
const int joystick_btn = 0;

LedControl lc(12, 11, 10, 1);
Dot dot;
bool was_pressed = FALSE;

void draw_dot();

void setup() {
  Serial.begin(9600);
  // Joystick einstellen
  pinMode(joystick_btn, INPUT);
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
  bool is_pressed = digitalRead(joystick_btn);
  bool was_released = FALSE;
  if (was_pressed && !is_pressed) {
    was_released = TRUE;
  } else {
    was_released = FALSE;
  }
  was_pressed = is_pressed;
  if (was_released) {
    randomize_dir();
  } else if (xAxis < 400 || xAxis > 600 || yAxis < 400 || yAxis > 600) {
    Vec2 velocity = {.x = xAxis - 512, .y = yAxis - 512};
    dot.velocity = vec_normalize(&velocity);
  }
  dot_move(&dot);
  lc.clearDisplay(0);
  draw_dot();
  delay(50);
}

void draw_dot() {
  Vec2 screenPos = vec_convert(&dot.position);
  // Serial.print(screenPos.x);
  // Serial.print(":");
  // Serial.println(screenPos.y);
  lc.setLed(0, screenPos.x, screenPos.y, true);
}

void randomize_dir() {
  Vec2 velocity = {.x = random(-10, 11), .y = random(-10, 11)};
  dot.velocity = vec_normalize(&velocity);
}
