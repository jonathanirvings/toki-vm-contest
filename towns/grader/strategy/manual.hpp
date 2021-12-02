#include <cassert>

#include <vector>

#include "strategy.hpp"

class ManualStrategy : public Strategy {
 public:
  ManualStrategy(int N) {
    R.resize(N);
    for (int i = 0; i < N; ++i) {
      char buffer[N + 1];
      assert(1 == scanf("%s", buffer));
      R[i] = buffer;
    }
  }

  bool check_road(int A, int B) override {
    return R[A][B] == '1';
  }

  bool is_correct(int town) override {
    if (town == -1) {
      return all_of(R.begin(), R.end(), [] (std::string s) {
        return count(s.begin(), s.end(), '1') > 1;
      });
    } else {
      return count(R[town].begin(), R[town].end(), '1') <= 1;
    }
  }

 private:
  std::vector<std::string> R;
};
