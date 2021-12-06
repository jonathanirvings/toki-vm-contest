#include <bits/stdc++.h>
using namespace std;

constexpr int kMaxIterations = 100000;
constexpr double kMaxRuntimeSecs = 0.9;
constexpr int kRandomSeed = 477444;

int main() {
  srand(kRandomSeed);
  
  int N;
  scanf("%d", &N);

  vector<bool> triangular(2 * N, false);
  for (int i = 1; i * (i + 1) / 2 < 2 * N; ++i) {
    triangular[i * (i + 1) / 2] = true;
  }

  vector<int> order(N);
  iota(order.begin(), order.end(), 1);
  pair<int, vector<int>> answer = make_pair(0, vector<int>({}));
  mt19937 rng(kRandomSeed);
  clock_t tStart = clock();
  for (int tries = 0;
       tries < kMaxIterations &&
           clock() - tStart < kMaxRuntimeSecs * CLOCKS_PER_SEC;
       ++tries) {
    shuffle(order.begin(), order.end(), rng);
    vector<int> A = {order[0]};
    int value = 0;
    
    vector<int> unused = order;
    swap(unused[0], unused[unused.size() - 1]);
    unused.pop_back();
    for (int j = 0; j < N - 1; ++j) {
      bool found = false;
      for (int k = 0; k < static_cast<int>(unused.size()) && !found; ++k) {
        if (triangular[A[j] + unused[k]]) {
          A.push_back(unused[k]);
          swap(unused[k], unused[unused.size() - 1]);
          unused.pop_back();
          ++value;
          found = true;
        }
      }
      if (!found) {
        A.push_back(unused[unused.size() - 1]);
        unused.pop_back();
      }
    }
    if (triangular[A[0] + A[N - 1]]) {
      ++value;
    }
    answer = max(answer, make_pair(value, A));
  }

  for (int i = 0; i < N; ++i) {
    printf("%d%c", answer.second[i], " \n"[i == N - 1]);
  }
}
