def manual(testcase):
  print(f"manual {testcase}.in")


def include(include):
  print(f"@include {include.name}")


def indexify_testcases(gen_func):
  testcase_index = 0
  def _gen_func(*args):
    nonlocal testcase_index
    gen_func(*args, testcase_index=testcase_index)
    testcase_index += 1
  return _gen_func


@indexify_testcases
def gen_manual(minN, maxN, subtask_index, testcase_index=0):
  print(f"gen {minN} {maxN} {subtask_index} manual {testcase_index}")


@indexify_testcases
def gen_must_sure(minN, maxN, subtask_index, graph_type, *args, testcase_index=0):
  print(f"gen {minN} {maxN} {subtask_index} must-sure {graph_type} {' '.join(map(str, list(args) + ['']))}{testcase_index}")


@indexify_testcases
def gen_greedy_outdeg_min(minN, maxN, subtask_index, testcase_index=0):
  print(f"gen {minN} {maxN} {subtask_index} greedy-outdeg-min {testcase_index}")


@indexify_testcases
def gen_greedy_outdeg_max(minN, maxN, subtask_index, testcase_index=0):
  print(f"gen {minN} {maxN} {subtask_index} greedy-outdeg-max {testcase_index}")


@indexify_testcases
def gen_near_found(minN, maxN, subtask_index, testcase_index=0):
  print(f"gen {minN} {maxN} {subtask_index} near-found {testcase_index}")


@indexify_testcases
def gen_maintain_cycle(minN, maxN, subtask_index, testcase_index=0):
  print(f"gen {minN} {maxN} {subtask_index} maintain-cycle {testcase_index}")


@indexify_testcases
def gen_maintain_cycle_deterministic(minN, maxN, subtask_index, testcase_index=0):
  print(f"gen {minN} {maxN} {subtask_index} maintain-cycle-deterministic {testcase_index}")


class Subtask():
  name = None

  def __init__(self):
    print("")
    print(f"@subtask {self.name}")


class SubtaskSamples(Subtask):
  name = "samples"

  def __init__(self):
    super().__init__()
    manual("sample-1")
    manual("sample-2")


class SubtaskSmallN(Subtask):
  name = "smallN"
  subtask_index = 1
  minN = 3
  maxN = 250

  def __init__(self):
    super().__init__()
    include(SubtaskSamples)
    gen_manual(self.minN, self.maxN, self.subtask_index)
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'random')
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'has-k-outgoing', 0)
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'has-k-outgoing', 1)
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'has-k-outgoing', 2)
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'dag')
    gen_greedy_outdeg_max(self.maxN, self.maxN, self.subtask_index)
    gen_greedy_outdeg_min(self.maxN, self.maxN, self.subtask_index)
    gen_near_found(self.maxN, self.maxN, self.subtask_index)
    gen_maintain_cycle(self.maxN, self.maxN, self.subtask_index)
    gen_maintain_cycle_deterministic(self.maxN, self.maxN, self.subtask_index)


class SubtaskFull(Subtask):
  name = "full"
  subtask_index = 2
  minN = 251
  maxN = 2000

  def __init__(self):
    super().__init__()
    gen_manual(self.minN, self.maxN, self.subtask_index)
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'random')
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'has-k-outgoing', 0)
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'has-k-outgoing', 1)
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'has-k-outgoing', 2)
    gen_must_sure(self.maxN - 5, self.maxN, self.subtask_index, 'dag')
    gen_greedy_outdeg_max(self.maxN, self.maxN, self.subtask_index)
    gen_greedy_outdeg_min(self.maxN, self.maxN, self.subtask_index)
    gen_near_found(self.maxN, self.maxN, self.subtask_index)
    gen_maintain_cycle(self.maxN, self.maxN, self.subtask_index)
    gen_maintain_cycle_deterministic(self.maxN, self.maxN, self.subtask_index)


def main():
  for subtask in Subtask.__subclasses__():
    subtask()

main()
