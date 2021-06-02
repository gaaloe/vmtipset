#include <cinttypes>
#include <iostream>
int main()
{
  uint64_t generator;
  const uint64_t upperlimit = 1L << 55;
  for (uint64_t iteration = 0L; iteration < upperlimit; ++iteration) {
    if ((iteration % 1000000000L) == 0) {
      std::cout << iteration / 1000000000L << ' ' << upperlimit / 1000000000L << '\n';
    }
  }
}
