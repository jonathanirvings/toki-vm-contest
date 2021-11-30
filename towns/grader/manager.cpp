#include "testlib.h"

#include <cassert>
#include <csignal>
#include <cstdio>

#include <memory>
#include <string>
#include <vector>

class Strategy {
 public:
  virtual bool check_road(int A, int B) = 0;
  virtual bool is_correct(int town) = 0;
};

class ManualStrategy : public Strategy {
 public:
  ManualStrategy(int N) : N(N) {
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
  int N;
  std::vector<std::string> R;
};

inline FILE* openFile(const char* name, const char* mode) {
  FILE* file = fopen(name, mode);
  if (!file) {
    quitf(_fail, "Could not open file '%s' with mode '%s'", name, mode);
  }
  return file;
}

int main(int argc, char *argv[]) {
  testlibMode = _checker;
  ouf.mode = _output;

  if (argc < 3) {
    quit(_fail, "Insufficient number of args for manager of 'towns'");
  }

  {
    // Keep alive on broken pipes
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &sa, NULL);
  }

  // Must be in this order
  FILE *fout = openFile(argv[2], "a");
  FILE *fin = openFile(argv[1], "r");

  int N;
  int subtask;
  assert(2 == scanf("%d %d", &N, &subtask));

  std::unique_ptr<Strategy> strategy;
  char buffer[100];
  assert(1 == scanf("%s", buffer));
  if (std::string(buffer) == "manual") {
    strategy.reset(new ManualStrategy(N));
  } else {
    assert(false);
  }

  fprintf(fout, "%d\n", N);
  fflush(fout);

  int Q = 0;
  while (true) {
    {
      std::string in_secret = "Z";
      char secret[100];
      if (fscanf(fin, "%s", secret) != 1 || std::string(secret) != in_secret) {
        quit(_sv, "Secret not found!");
      }
    }

    int op;
    if (fscanf(fin, "%d", &op) != 1) {
      quit(_sv, "op not found.");
    }

    if (op == 0) {
      if (Q == 40000) {
        quit(_wa, "Too many queries.");
      }
      ++Q;

      int A, B;
      if (fscanf(fin, "%d %d", &A, &B) != 2) {
        quit(_sv, "Invalid query format.");
      }
      if (A == B || A < 0 || A >= N || B < 0 || B >= N) {
        quit(_wa, "Invalid query parameters.");
      }

      int road = strategy->check_road(A, B) ? 1 : 0;
      fprintf(fout, "%d\n", road);
      fflush(fout);
    } else if (op == 1) {
      int answer;
      if (fscanf(fin, "%d", &answer) != 1) {
        quit(_sv, "Invalid answer format.");
      }

      if (answer < -1 || answer >= N) {
        quit(_wa, "Wrong answer.");
      }

      if (strategy->is_correct(answer)) {
        if (subtask == 1) {
          quit(_ok);
        } else if (subtask == 2) {
          if (Q <= 8000) {
            quit(_ok);
          } else if (Q <= 20000) {
            quitp(1.0 - 70.0 / 90.0 * sqrt((Q - 8000) * 1.0 / 12000));
          } else {
            quitp(20.0 / 90.0);
          }
        } else {
          assert(false);
        }
      } else {
        quit(_wa, "Wrong answer.");
      }
    } else {
      quit(_sv, "Invalid value of op.");
    }
  }
}
