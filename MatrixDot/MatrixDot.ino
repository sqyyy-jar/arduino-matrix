#include "LedControl.h"
#include "Matrix.c"

LedControl lc(12, 11, 10, 1);
Dot dot;

void move_dot();

void draw_dot();

void setup() {
  // LED-Matrix einstellen
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  // Punkt einstellen
  dot.position = { .x = 0, .y = 0 };
  dot.velocity = { .x = 1, .y = 2 };
}

void loop() {
  move_dot();
  lc.clearDisplay(0);
  draw_dot();
  delay(50);
}

void move_dot() {
  Vec2 dest;
  vec_add(&dot.position, &dot.velocity, &dest);
  if (dest.x < 0 || dest.x >= MAT_VWIDTH) {
    dot.velocity.x = -dot.velocity.x;
  }
  if (dest.y < 0 || dest.y >= MAT_VWIDTH) {
    dot.velocity.y = -dot.velocity.y;
  }
  dot.position = dest;
}

void draw_dot() {
  Vec2 screenPos;
  vec_convert(&dot.position, &screenPos);
  lc.setLed(0, screenPos.x, screenPos.y, true);
}

// TODO
// - zufällige Richtung mit Taster
