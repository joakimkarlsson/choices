#include <igloo/igloo_alt.h>
using namespace igloo;

int main(int argc, const char *argv[])
{
  for(int i=0; i<argc; i++)
  {
    std::cout << argv[i] << std::endl;
  }

  return TestRunner::RunAllTests();
}
