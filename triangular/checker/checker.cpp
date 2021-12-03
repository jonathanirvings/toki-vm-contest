#include "testlib.h"

#include <cmath>

#include <algorithm>
#include <set>
#include <vector>

int main(int argc, char * argv[]) {
  registerChecker("triangular", argc, argv);

  int N = inf.readInt();

  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    A[i] = ouf.readInt(1, N, "A[i]");
  }

  if (static_cast<int>(std::set<int>(A.begin(), A.end()).size()) != N) {
    ouf.quitf(_wa, "Found duplicates in A.");
  }

  if (!ouf.seekEof()) {
    ouf.quitf(_wa, "Extra output found");
  }

  std::vector<bool> triangular(2 * N, false);
  for (int i = 1; i * (i + 1) / 2 < 2 * N; ++i) {
    triangular[i * (i + 1) / 2] = true;
  }

  int value = 0;
  for (int i = 0; i < N; ++i) {
    value += triangular[A[i] + A[(i + 1) % N]] ? 1 : 0;
  }

  double score = std::max(0.0, (10.0 - sqrt(N - value)) / 10.0);
  score = round(score * 1000) / 1000;
  if (score == 1.0) {
    quit(_ok);
  } else {
    quitp(score);
  }
}
