#include "team.h"

#include <cassert>
#include <cstdio>

// BEGIN SECRET
#include <string>
// END SECRET
#include <vector>

int main() {
  // BEGIN SECRET
  {
    std::string in_secret = "ini-adalah-masukan-rahasia";
    std::string out_secret = "ini-adalah-keluaran-rahasia";
    char secret[1000];
    assert(1 == scanf("%s", secret));
    if (std::string(secret) != in_secret) {
      printf("%s\n", out_secret.c_str());
      printf("SV\n");
      fclose(stdout);
      return 0;
    }
  }
  // END SECRET
  int N, K;
  assert(2 == scanf("%d %d", &N, &K));

  std::vector<int> L(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &L[i]));
  }

  int result = maximum_teams(N, K, L);
  // BEGIN SECRET
  {
    std::string out_secret = "ini-adalah-keluaran-rahasia";
    printf("%s\n", out_secret.c_str());
    printf("OK\n");
  }
  // END SECRET
  printf("%d\n", result);
  return 0;
}
