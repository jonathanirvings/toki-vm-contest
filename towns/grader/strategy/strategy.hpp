#pragma once

class Strategy {
 public:
  virtual ~Strategy() = default;
  virtual bool check_road(int A, int B) = 0;
  virtual bool is_correct(int town) = 0;
};
