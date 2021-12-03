#include "testlib.h"

#include <functional>
#include <numeric>
#include <vector>

int main(int, char *argv[]) {
  registerValidation();

  int subtask_number = atoi(argv[1] + strlen("subtask"));
  int N = std::vector<int>(
      {15, 16, 100, 103, 150, 178, 197, 198, 199, 200})[subtask_number - 1];
  inf.readInt(N, N, "N");
  inf.readEoln();
  inf.readEof();
  
  return 0;
}
