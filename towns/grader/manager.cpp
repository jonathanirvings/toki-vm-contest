#include "testlib.h"

#include <cassert>
#include <csignal>
#include <cstdio>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

class Strategy {
 public:
  virtual ~Strategy() = default;
  virtual bool check_road(int A, int B) = 0;
  virtual bool is_correct(int town) = 0;
};

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
      return std::all_of(R.begin(), R.end(), [] (std::string s) {
        return std::count(s.begin(), s.end(), '1') > 1;
      });
    } else {
      return std::count(R[town].begin(), R[town].end(), '1') <= 1;
    }
  }

 private:
  std::vector<std::string> R;
};

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
      ++outdeg[R[A][B] == '1' ? A : B];
    }
    return R[A][B] == '1';
  }

  bool is_correct(int town) override {
    if (town == -1) {
      for (int i = 0; i < N; ++i) {
        if (outdeg[i] <= 1) {
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

class GreedyOutdegStrategy : public Strategy {
 public:
  GreedyOutdegStrategy(int N, bool greedyMax): N(N), greedyMax(greedyMax) {
    R.resize(N, std::vector<int>(N, -1));
    unknown.resize(N, N - 1);
    outdeg.resize(N);
  }

  bool check_road(int A, int B) override {
    if (R[A][B] != -1) {
      return R[A][B] == 1 ? true : false;
    }

    if (greedyMax != (outdeg[A] < outdeg[B])) {
      addEdge(A, B);
      return true;
    }
    addEdge(B, A);
    return false;
  }

  bool is_correct(int town) override {
    if (town == -1) {
      for (int i = 0; i < N; ++i) {
        if (outdeg[i] <= 1) {
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
  bool greedyMax;
  std::vector<std::vector<int>> R;
  std::vector<int> outdeg;
  std::vector<int> unknown;

  void addEdge(int u, int v) {
    R[u][v] = 1;
    R[v][u] = 0;
    --unknown[u]; --unknown[v];
    ++outdeg[u];
  }
};

class NearFoundStrategy : public Strategy {
 public:
  NearFoundStrategy(int N): N(N) {
    R.resize(N, std::vector<int>(N, -1));
    unknown.resize(N, N - 1);
    outdeg.resize(N);
  }

  bool check_road(int A, int B) override {
    if (R[A][B] != -1) {
      return R[A][B] == 1 ? true : false;
    }

    if (outdeg[A] <= 1 && outdeg[B] <= 1) {
      addEdge(A, B);
      return true;
    }

    if (outdeg[A] <= 1 && outdeg[B] > 1) {
      if (outdeg[A] + unknown[A] - 1 <= 1) {
        addEdge(A, B);
        return true;
      }
      addEdge(B, A);
      return false;
    }

    if (outdeg[A] > 1 && outdeg[B] <= 1) {
      if (outdeg[B] + unknown[B] - 1 <= 1) {
        addEdge(B, A);
        return false;
      }
      addEdge(A, B);
      return true;
    }

    addEdge(A, B);
    return true;
  }

  bool is_correct(int town) override {
    // Answer should always be -1
    if (town == -1) {
      for (int i = 0; i < N; ++i) {
        if (outdeg[i] <= 1) {
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
  std::vector<std::vector<int>> R;
  std::vector<int> outdeg;
  std::vector<int> unknown;

  void addEdge(int u, int v) {
    R[u][v] = 1;
    R[v][u] = 0;
    --unknown[u]; --unknown[v];
    ++outdeg[u];
  }
};

class MaintainCycleStrategy : public Strategy {
 public:
  MaintainCycleStrategy(int N, bool deterministic=false) :
      N(N), deterministic(deterministic) {
    R.resize(N, std::vector<int>(N, -1));
    unknown.resize(N, N - 1);
    outdeg.resize(N);
    adj.resize(N);
  }

  bool check_road(int A, int B) override {
    if (R[A][B] != -1) {
      return R[A][B] == 1 ? true : false;
    }

    if (unknown[B] - 1 + outdeg[B] <= 1) {
      addEdge(B, A);
      // Cycle may be removed
      rebuildCycle();
      return false;
    }

    if (unknown[A] - 1 + outdeg[A] <= 1) {
      assert(unknown[A] + outdeg[A] == 2);
      addEdge(A, B);
      // Cycle may be removed
      rebuildCycle();
      return true;
    }

    if (outdeg[A] == 0 && outdeg[B] == 0) {
      return randomAddEdge(A, B);
    }

    if (outdeg[A] == 0 && outdeg[B] == 1) {
      addEdge(A, B);
      // A new cycle may be formed
      rebuildCycle();
      return true;
    }

    if (outdeg[A] == 1 && outdeg[B] == 0) {
      addEdge(B, A);
      // A new cycle may be formed
      rebuildCycle();
      return false;
    }

    if (outdeg[A] == 1 && outdeg[B] == 1) {
      if (cyclePart[A] && cyclePart[B]) {
        bool ret = randomAddEdge(A, B);
        // Cycle becomes smaller
        rebuildCycle();
        return ret;
      }

      if (cyclePart[A] && !cyclePart[B]) {
        addEdge(B, A);
        return false;
      }

      if (!cyclePart[A] && cyclePart[B]) {
        addEdge(A, B);
        return true;
      }

      if (!cyclePart[A] && !cyclePart[B]) {
        return randomAddEdge(A, B);
      }

      assert(false);
    }

    if (outdeg[A] > 1 && outdeg[B] <= 1) {
      addEdge(A, B);
      return true;
    }

    if (outdeg[A] <= 1 && outdeg[B] > 1) {
      addEdge(B, A);
      return false;
    }

    assert(outdeg[A] > 1 && outdeg[B] > 1);
    return randomAddEdge(A, B);
  }

  bool is_correct(int town) override {
    // if your solution was <= 4N, then `town` should be -1
    // otherwise, your solution must be at least 5N

    if (town == -1) {
      for (int i = 0; i < N; ++i) {
        if (outdeg[i] <= 1) {
          return false;
        }
      }
      return true;
    }

    if (outdeg[town] + unknown[town] <= 1) {
      return true;
    }
    return false;
  }

 private:
  int N;
  bool deterministic;
  std::vector<std::vector<int>> R;
  std::vector<int> outdeg;
  std::vector<int> unknown;
  std::vector<std::vector<int>> adj;
  std::vector<bool> cyclePart;

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    R[u][v] = 1;
    R[v][u] = 0;
    --unknown[u]; --unknown[v];
    ++outdeg[u];
  }

  bool randomAddEdge(int u, int v) {
    if (deterministic || rnd.next(2)) {
      addEdge(u, v);
      return true;
    }
    addEdge(v, u);
    return false;
  }

  // O(N)
  void rebuildCycle() {
    cyclePart.assign(N, false);
    std::vector<bool> vis(N, false);
    std::vector<bool> visTour(N, false);
    for (int i = 0; i < N; ++i) {
      if (vis[i] || outdeg[i] != 1) continue;

      int u = i;
      std::vector<int> tour;
      while (outdeg[u] == 1) {
        visTour[u] = true;
        tour.push_back(u);
        u = adj[u][0];

        if (vis[u]) {
          break;
        }

        if (visTour[u]) {
          // Found cycle
          while (tour.back() != u) {
            cyclePart[tour.back()] = true;
            vis[tour.back()] = true;
            visTour[tour.back()] = false;
            tour.pop_back();
          }
          cyclePart[u] = true;
          break;
        }
      }

      for (int u : tour) {
        vis[u] = true;
        visTour[u] = false;
      }
    }
  }
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
  } else if (std::string(buffer) == "must-sure") {
    strategy.reset(new MustSureStrategy(N));
  } else if (std::string(buffer) == "greedy-outdeg-min") {
    strategy.reset(new GreedyOutdegStrategy(N, false));
  } else if (std::string(buffer) == "greedy-outdeg-max") {
    strategy.reset(new GreedyOutdegStrategy(N, true));
  } else if (std::string(buffer) == "near-found") {
    strategy.reset(new NearFoundStrategy(N));
  } else if (std::string(buffer) == "maintain-cycle") {
    strategy.reset(new MaintainCycleStrategy(N));
  } else if (std::string(buffer) == "maintain-cycle-deterministic") {
    strategy.reset(new MaintainCycleStrategy(N, true));
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
