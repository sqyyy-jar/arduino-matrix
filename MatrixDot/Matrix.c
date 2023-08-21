#include "Matrix.h"

void vec_convert(Vec2 *src, Vec2 *dst) {
  dst->x = src->x >> MAT_PREC_BITS;
  dst->y = src->y >> MAT_PREC_BITS;
}

void vec_add(Vec2 *left, Vec2 *right, Vec2 *dst) {
  dst->x = left->x + right->x;
  dst->y = left->y + right->y;
}

void vec_mul(Vec2 *src, int amount, Vec2 *dst) {
  dst->x = src->x * amount;
  dst->y = src->y * amount;
}

int vec_mag_sq(Vec2 *src) {
  return src->x * src->x + src->y * src->y;
}

int vec_mag(Vec2 *src) {
  return sqrt(vec_mag_sq(src));
}

