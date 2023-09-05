#include "LedControl.h"
#include "Matrix.c"
#include "types.h"

#define RANDOMIZE FALSE

const int joystick_x = A1;
const int joystick_y = A0;
const int joystick_btn = 0;

LedControl lc(12, 11, 10, 1);
Dot dot;
bool was_pressed = FALSE;

void draw_dot();

void setup() {
  Serial.begin(9600);
  // Joystick einstellen
  pinMode(joystick_btn, INPUT);
  digitalWrite(joystick_btn, HIGH);
  // LED-Matrix einstellen
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  // Punkt einstellen
  dot.position = {.x = MAT_VWIDTH / 2, .y = MAT_VWIDTH / 2};
  dot.velocity = {.x = 0, .y = 0};
}

void loop() {
  int xAxis = analogRead(joystick_x) - 512;
  int yAxis = analogRead(joystick_y) - 512;
  bool is_pressed = !digitalRead(joystick_btn);
  bool was_released = FALSE;
  if (was_pressed && !is_pressed) {
    was_released = TRUE;
  } else {
    was_released = FALSE;
  }
  was_pressed = is_pressed;
  if (was_released) {
    randomize_dir();
  } else if (xAxis < -100 || xAxis > 100 || yAxis < -100 || yAxis > 100) {
    Vec2 velocity = {.x = xAxis, .y = yAxis};
    dot.velocity = vec_resize(&velocity);
  }
  dot_move(&dot);
  // Serial.print("x: ");
  // Serial.print(dot.velocity.x);
  // Serial.print("y: ");
  // Serial.println(dot.velocity.y);
  lc.clearDisplay(0);
  draw_dot();
  delay(50);
}

void draw_dot() {
  Vec2 screenPos = vec_convert(&dot.position);
  lc.setLed(0, screenPos.x, screenPos.y, true);
}

void randomize_dir() {
  if (RANDOMIZE) {
    Vec2 velocity = {.x = random(-512, 511), .y = random(-512, 511)};
    dot.velocity = vec_resize(&velocity);
  } else {
    Vec2 velocity = {.x = 0, .y = 0};
    dot.velocity = vec_resize(&velocity);
    Vec2 pos = {.x = MAT_VWIDTH / 2, .y = MAT_VWIDTH / 2};
    dot.position = pos;
  }
}

// Vec2 vec_resize(Vec2 *src) {
//   Vec2 result;
//   long x = src->x;
//   long y = src->y;
//   Serial.print("Resize ");
//   Serial.print(x);
//   Serial.print(", ");
//   Serial.print(y);
//   Serial.print(", ");
//   double len = sqrt(x * x + y * y);
//   Serial.print(len);
//   Serial.print(", ");
//   result.x = (x * DOT_SPEED) / len;
//   result.y = (y * DOT_SPEED) / len;
//   Serial.print(result.x);
//   Serial.print(", ");
//   Serial.println(result.y);
//   return result;
// }
