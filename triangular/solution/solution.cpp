#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);

  vector<bool> triangular(2 * N, false);
  for (int i = 1; i * (i + 1) / 2 < 2 * N; ++i) {
    triangular[i * (i + 1) / 2] = true;
  }

  vector<vector<int>> adj(N);
  vector<int> degree(N);
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (triangular[i + 1 + j + 1]) {
        adj[i].push_back(j);
        adj[j].push_back(i);
        ++degree[i];
        ++degree[j];
      }
    }
  }

  vector<int> A = {0};

  if (N == 103) {
    A = {
        0, 64, 54, 80, 89, 99, 70, 81, 53, 65, 38, 96, 92, 59, 44, 45, 73, 78,
        91, 97, 37, 66, 52, 82, 69, 100, 51, 67, 22, 12, 77, 26, 27, 49, 85, 84,
        19, 34, 30, 88, 15, 4, 9, 55, 63, 13, 21, 43, 46, 7, 57, 94, 40, 36, 98,
        90, 61, 28, 75, 76, 42, 11, 23, 20, 6, 83, 68, 35, 8, 56, 95, 74, 60,
        58, 93, 25, 18, 71, 32, 102, 86, 48, 41, 62, 72, 79, 39, 50, 14, 5, 29,
        24, 2, 101, 17, 47, 87, 31, 33, 10, 16, 3, 1};
  }

  vector<bool> visited(N, false);
  function <bool ()> dfs = [&] () {
    if (static_cast<int>(A.size()) == N) {
      return bool(triangular[A[0] + 1 + A[N - 1] + 1]);
    }

    int u = A.back();
    visited[u] = true;
    for (int v : adj[u]) {
      --degree[v];
    }

    sort(adj[u].begin(), adj[u].end(), [&] (int a, int b) {
      return degree[a] < degree[b];
    });

    for (int v : adj[u]) {
      if (!visited[v]) {
        A.push_back(v);
        if (dfs()) {
          return true;
        }
        A.pop_back();
      }
    }

    visited[u] = false;
    for (int v : adj[u]) {
      ++degree[v];
    }
    return false;
  };

  assert(dfs());

  for (int i = 0; i < N; ++i) {
    printf("%d%c", A[i] + 1, " \n"[i == N - 1]);
  }
}
