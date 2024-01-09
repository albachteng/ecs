#pragma once
class CLifespan {
public:
  int total;
  int remaining;
  CLifespan(int total) : remaining(total), total(total){};
};
