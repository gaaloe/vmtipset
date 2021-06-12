#ifndef _HOME_HENRIK_VMTIPSET_EM2020_ALLEGE_H
#define _HOME_HENRIK_VMTIPSET_EM2020_ALLEGE_H
#include <cassert>
#ifndef NDEBUG
#define DEBUG_allege(ex) assert(ex)
#else
#define DEBUG_allege(ex)                                                       \
  {                                                                            \
    if (!(ex)) {                                                               \
      std::cerr << "Assertion failed: " << __FILE__ << ' ' << __LINE__ << ' '  \
                << #ex << '\n';                                                \
      abort();                                                                 \
    }                                                                          \
  }
#endif
#endif
