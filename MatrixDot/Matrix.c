#include "Matrix.h"

#include "types.h"

Vec2 vec_convert(Vec2 *src) {
  return (Vec2){.x = src->x >> MAT_PREC_BITS, .y = src->y >> MAT_PREC_BITS};
}

Vec2 vec_add(Vec2 *left, Vec2 *right) {
  return (Vec2){.x = left->x + right->x, .y = left->y + right->y};
}

Vec2 vec_mul(Vec2 *src, int amount) {
  return (Vec2){.x = src->x * amount, .y = src->y * amount};
}

Vec2 vec_resize(Vec2 *src) {
  Vec2 result;
  long x = src->x;
  long y = src->y;
  double len = sqrt(x * x + y * y);
  result.x = (x * DOT_SPEED) / len;
  result.y = (y * DOT_SPEED) / len;
  return result;
}

void dot_move(Dot *dot) {
  Vec2 dest = vec_add(&dot->position, &dot->velocity);
  for (int i = 0; i < 10 && dot_bounce(dot, &dest); i++) {
  }
  dot->position = dest;
}

bool dot_bounce(Dot *dot, Vec2 *dest) {
  bool bounced = FALSE;
  if (dest->x < 0) {
    bounced = TRUE;
    dest->x = -dest->x;
    dot->velocity.x = -dot->velocity.x;
  }
  if (dest->x >= MAT_VWIDTH) {
    bounced = TRUE;
    dest->x = MAT_VWIDTH - (dest->x - MAT_VWIDTH);
    dot->velocity.x = -dot->velocity.x;
  }
  if (dest->y < 0) {
    bounced = TRUE;
    dest->y = -dest->y;
    dot->velocity.y = -dot->velocity.y;
  }
  if (dest->y >= MAT_VWIDTH) {
    bounced = TRUE;
    dest->y = MAT_VWIDTH - (dest->y - MAT_VWIDTH);
    dot->velocity.y = -dot->velocity.y;
  }
  return bounced;
}
