#include "types.h"

// LED-Matrix Breite
#define MAT_WIDTH 8
// Anzahl an Bits pro LED
#define MAT_PREC_BITS 5
// Virtuelle Breite eines Punktes
#define MAT_DOT_VWIDTH (1 << MAT_PREC_BITS)
// Virtuelle Matrix Breite
#define MAT_VWIDTH (MAT_DOT_VWIDTH * MAT_WIDTH)
// Geschwindigkeit des Punkts
#define DOT_SPEED (MAT_DOT_VWIDTH / 2)

// 2D-Vektor
typedef struct vec2_t {
  int x;
  int y;
} Vec2;

// 2D-Punkt mit Geschwindigkeit
typedef struct dot_t {
  Vec2 position;
  Vec2 velocity;
} Dot;

// Vektor in Matrix-Koordinaten umwandeln
Vec2 vec_convert(Vec2 *src);

// Vektor addieren
Vec2 vec_add(Vec2 *left, Vec2 *right);

// Vektor mit Integer multiplizieren
Vec2 vec_mul(Vec2 *src, int amount);

// Vektor an Geschwindigkeit anpassen (length=DOT_SPEED)
Vec2 vec_resize(Vec2 *src);

// Punkt wird bewegt
void dot_move(Dot *dot);

// Lässt den Punkt von Wänden abprallen
bool dot_bounce(Dot *dot, Vec2 *dest);