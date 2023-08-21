#include "LedControl.h"
#include "Matrix.c"

LedControl lc(12, 11, 10, 1);
Dot dot;

void draw_dot();

void setup() {
  // LED-Matrix einstellen
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  // Punkt einstellen
  dot.position = {.x = 0, .y = 0};
  dot.velocity = {.x = 1, .y = 2};
}

void loop() {
  dot_move(&dot);
  lc.clearDisplay(0);
  draw_dot();
  delay(50);
}

void draw_dot() {
  Vec2 screenPos = vec_convert(&dot.position);
  lc.setLed(0, screenPos.x, screenPos.y, true);
}

// TODO
// - zufällige Richtung mit Taster
