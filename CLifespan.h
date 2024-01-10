#pragma once
class CLifespan {
public:
  int start;
  int ttl;
  CLifespan(int current, int ttl) : start(current), ttl(ttl){};
};
