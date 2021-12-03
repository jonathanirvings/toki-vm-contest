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
