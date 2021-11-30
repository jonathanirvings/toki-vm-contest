#include "towns.h"

#include <cassert>
#include <cstdio>

#include <string>
#include <vector>

static int N;
static std::vector<std::string> R;
static int Q;

static inline void wrong_answer(std::string message) {
  printf("Wrong Answer: %s\n", message.c_str());
  exit(0);
}

bool check_road(int A, int B) {
  if (Q >= 40000) {
    wrong_answer("too many questions");
  }
  ++Q;
  if (A == B || A < 0 || A >= N || B < 0 || B >= N) {
    wrong_answer("invalid parameters");
  }
  return R[A][B] == '1';
}

int main() {
  assert(scanf("%d", &N) == 1);
  R.resize(N);

  for (int i = 0; i < N; ++i) {
    char buffer[N + 1];
    assert(scanf("%s", buffer) == 1);
    R[i] = buffer;
  }

  int answer = find_town(N);
  printf("%d\n%d\n", answer, Q);
  return 0;
}
