#include <bits/stdc++.h>
using namespace std;

constexpr int kMaxIterations = 500000;
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

  vector<int> A(N);
  iota(A.begin(), A.end(), 1);
  pair<int, vector<int>> answer = make_pair(0, vector<int>({}));
  mt19937 rng(kRandomSeed);
  clock_t tStart = clock();
  for (int tries = 0;
       tries < kMaxIterations &&
           clock() - tStart < kMaxRuntimeSecs * CLOCKS_PER_SEC;
       ++tries) {
    shuffle(A.begin(), A.end(), rng);
    int value = 0;
    for (int i = 0; i < N; ++i) {
      value += triangular[A[i] + A[(i + 1) % N]] ? 1 : 0;
    }
    answer = max(answer, make_pair(value, A));
  }

  for (int i = 0; i < N; ++i) {
    printf("%d%c", answer.second[i], " \n"[i == N - 1]);
  }
}
