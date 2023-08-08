#include "base/command_line.h"

#include "testing/googletest/include/gtest/gtest.h"

TEST(CommandLine, case0) {
  int argc;
  char **argv;

  argc = 3;
  argv = new char *[argc];

  base::CommandLine::Initialize(argc, argv);
}