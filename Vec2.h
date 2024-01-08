class Vec2 {
private:
  float x, y;

public:
  Vec2();
  Vec2(float x, float y);
  const float X(), Y();
  const Vec2 operator+(const Vec2 &rhs);
  Vec2 &operator+=(const Vec2 &rhs);
  void print_vec2();
};
