// LED-Matrix Breite
#define MAT_WIDTH 8
// Anzahl an Bits pro LED
#define MAT_PREC_BITS 4
// Virtuelle Matrix Breite
#define MAT_VWIDTH MAT_WIDTH << MAT_PREC_BITS

typedef struct vec2_t {
  int x;
  int y;
} Vec2;

typedef struct dot_t {
  Vec2 position;
  Vec2 velocity;
} Dot;

// Vektor in Matrix-Koordinaten umwandeln
void vec_convert(Vec2 *src, Vec2 *dst);

// Vektor addieren
void vec_add(Vec2 *left, Vec2 *right, Vec2 *dst);

// Vektor mit Integer multiplizieren
void vec_mul(Vec2 *src, int amount, Vec2 *dst);

// Quadrierte Länge eines Vektors
int vec_mag_sq(Vec2 *src);

// Länge eines Vektors
int vec_mag(Vec2 *src);

