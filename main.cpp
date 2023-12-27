#include "Vec2.h"
#include "iostream"

int main() {
  Vec2 v1 = Vec2(1.0, 1.0);
  v1.print_vec2();
  Vec2 v2 = Vec2(2.0, 2.0);
  v2.print_vec2();
  Vec2 v3;
  v3 = v1 + v2;
  v3.print_vec2();
  v1 += v2;
  v1.print_vec2();
}
