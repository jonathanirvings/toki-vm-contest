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
  print(f"gen {minN} {maxN} {subtask_index} manual")


@indexify_testcases
def gen_must_sure(minN, maxN, subtask_index, testcase_index=0):
  print(f"gen {minN} {maxN} {subtask_index} must-sure")


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
    gen_must_sure(self.minN, self.maxN, self.subtask_index)


class SubtaskFull(Subtask):
  name = "full"
  subtask_index = 2
  minN = 251
  maxN = 2000

  def __init__(self):
    super().__init__()
    gen_manual(self.minN, self.maxN, self.subtask_index)
    gen_must_sure(self.minN, self.maxN, self.subtask_index)


def main():
  for subtask in Subtask.__subclasses__():
    subtask()

main()
