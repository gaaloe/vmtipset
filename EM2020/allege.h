#ifndef allege_h
#define allege_h
#include <cassert>
#ifndef NDEBUG
#define allege(ex) assert(ex)
#else
#define allege(ex)                                                             \
  {                                                                            \
    if (!(ex)) {                                                               \
      std::cerr << "Assertion failed: " << __FILE__ << ' ' << __LINE__ << ' '  \
                << #ex << '\n';                                                \
      abort();                                                                 \
    }                                                                          \
  }
#endif
#endif
