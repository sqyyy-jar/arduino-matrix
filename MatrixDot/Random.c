typedef struct random_t {
  long seed;
} Random;

long rand_xorshift32(Random *random) {
  // xorshift32
  long x = random->seed;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return random->seed = x;
}

long rand_next(Random *random, long bound) {
  return (rand_xorshift32(random) & 0x7FFFFFFF) % bound;
}
