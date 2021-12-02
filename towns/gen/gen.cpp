#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

void randomR(int N) {
  vector<string> R(N, string(N, '0'));
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      R[i][j] = rnd.next('0', '1');
      R[j][i] = '1' - R[i][j] + '0'; 
    }
    printf("%s\n", R[i].c_str());
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 0);

  int N = rnd.next(atoi(argv[1]), atoi(argv[2]));
  int subtask = atoi(argv[3]);
  printf("%d %d\n", N, subtask);

  const char* strategy = argv[4];
  printf("%s\n", strategy);

  if (strcmp(strategy, "manual") == 0 || strcmp(strategy, "must-sure") == 0) {
    randomR(N);
  }
}
