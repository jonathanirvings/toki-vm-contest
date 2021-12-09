# Notice

Each task has an attachment package that you can download from the contest system.

There are some "output-only" tasks, for which:
* The attachment package contains input test cases and example test cases. Each test case is a separate subtask.
* You may submit multiple output files as a zip file. For this purpose, your output files should be named `??.out`, where `??` is the test case number (e.g., `03.out`).
* You may make up to 100 submissions for output-only tasks. In each submission, you may submit the output files for any subset of the test cases.

For other tasks:
* The attachment package contains sample graders, sample implementations, example test cases, and compile scripts.
* You may make up to 50 submissions for each task, and you have to submit exactly one file in each submission.
* The name of the file that you should submit is given in the task statement header. It should implement the procedures described in the task statement using the signatures provided in the sample implementations.
* You are free to implement other procedures.
* When testing your programs with the sample grader, your input should match the format and constraints from the task statement, otherwise, unspecified behaviors may occur.
* In sample grader inputs, every two consecutive tokens on a line are separated by a single space, unless another format is explicitly specified.
* When you test your code on your local machine, we recommend you to use scripts in the attachment package. The grading system will use `-std=gnu++17` option to compile, but you may remove or replace it if your local compiler does not support it.

# Convention

The task statements specify signatures using generic type names `void`, `int`, `int[]` (array), and `int[][]` (array of arrays).

In C++, the graders use appropriate data types or implementations, as listed below

| `void ` | `int` | `bool` | `int[]`            | length of array `a` |
| ------- | ----- | ------ | ------------------ | ------------------- |
| `void ` | `int` | `bool` | `std::vector<int>` | `a.size()`          |

# Limits

The limits for all tasks are available in the "Overview" page in the contest system.
