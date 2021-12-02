#include <cassert>

#include <vector>

#include "strategy.hpp"

class MustSureStrategy : public Strategy {
 public:
  MustSureStrategy(int N) : N(N) {
    R.resize(N);
    unknown.resize(N, N - 1);
    outdeg.resize(N);
    queried.resize(N, std::vector<bool>(N, false));
    for (int i = 0; i < N; ++i) {
      char buffer[N + 1];
      assert(1 == scanf("%s", buffer));
      R[i] = buffer;
    }
  }

  bool check_road(int A, int B) override {
    if (!queried[A][B]) {
      queried[A][B] = queried[B][A] = true;
      --unknown[A];
      --unknown[B];
      --outdeg[R[A][B] == '1' ? A : B];
    }
    return R[A][B] == '1';
  }

  bool is_correct(int town) override {
    if (town == -1) {
      for (int i = 0; i < N; ++i) {
        if (outdeg[town] <= 1) {
          return false;
        }
      }
      return true;
    } else {
      return outdeg[town] + unknown[town] <= 1;
    }
  }

 private:
  int N;
  std::vector<std::string> R;
  std::vector<std::vector<bool>> queried;
  std::vector<int> unknown;
  std::vector<int> outdeg;
};
