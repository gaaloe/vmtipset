#include <cassert>
#include <cinttypes>
#include <cstring>
#include <iomanip>
#include <iostream>
using std::cerr;
// Format using clang-format -i main.cpp
void showGrundSpel(char grp, uint64_t table) {
  std::cout << grp << ':';
  switch (table) {
  case 0b000110:
    std::cout << "0,1,2";
    break;
  case 0b000111:
    std::cout << "0,1,3";
    break;
  case 0b001001:
    std::cout << "0,2,1";
    break;
  case 0b001011:
    std::cout << "0,2,3";
    break;
  case 0x0D:
    std::cout << "0,3,1";
    break;
  case 0x0E:
    std::cout << "0,3,2";
    break;
  case 0x12:
    std::cout << "1,0,2";
    break;
  case 0x13:
    std::cout << "1,0,3";
    break;
  case 0x18:
    std::cout << "1,2,0";
    break;
  case 0x1B:
    std::cout << "1,2,3";
    break;
  case 0x1C:
    std::cout << "1,3,0";
    break;
  case 0x1E:
    std::cout << "1,3,2";
    break;
  case 0x21:
    std::cout << "2,0,1";
    break;
  case 0x23:
    std::cout << "2,0,3";
    break;
  case 0x24:
    std::cout << "2,1,0";
    break;
  case 0x27:
    std::cout << "2,1,3";
    break;
  case 0x2C:
    std::cout << "2,3,0";
    break;
  case 0x2D:
    std::cout << "2,3,1";
    break;
  case 0x31:
    std::cout << "3,0,1";
    break;
  case 0x32:
    std::cout << "3,0,2";
    break;
  case 0x34:
    std::cout << "3,1,0";
    break;
  case 0x36:
    std::cout << "3,1,2";
    break;
  case 0x38:
    std::cout << "3,2,0";
    break;
  case 0x39:
    std::cout << "3,2,1";
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  std::cout << ' ';
}
void showTredjeTab(uint64_t tabell) {
  switch (tabell) {
  case 0:
    std::cout << "ABCD--";
    break;
  case 1:
    std::cout << "ABC-E-";
    break;
  case 2:
    std::cout << "ABC--F";
    break;
  case 3:
    std::cout << "AB-DE-";
    break;
  case 4:
    std::cout << "AB-D-F";
    break;
  case 5:
    std::cout << "AB--EF";
    break;
  case 6:
    std::cout << "A-CDE-";
    break;
  case 7:
    std::cout << "A-CD-F";
    break;
  case 8:
    std::cout << "A-C-EF";
    break;
  case 9:
    std::cout << "A--DEF";
    break;
  case 10:
    std::cout << "-BCDE-";
    break;
  case 11:
    std::cout << "-BCD-F";
    break;
  case 12:
    std::cout << "-BC-EF";
    break;
  case 13:
    std::cout << "-B-DEF";
    break;
  case 14:
    std::cout << "--CDEF";
    break;
  case 15: // There are 15 alternatives 0..14
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    std::ios init(nullptr);
    init.copyfmt(std::cout);
    std::cout << std::hex;
    std::cout.width(14);
    std::cout << tabell << '\n';
    std::cout.copyfmt(init); // restore default formatting
    abort();
  }
}
int main(int argc, char *argv[]) {
  // seq -w 0 3 | parallel -u ./a.out {}
  // Ger 0
  //     1
  //     2
  //     3
  uint64_t offsetStride = 0;
  if (argc > 1) {
    int base = 10;
    char *endptr;
    errno = 0; /* To distinguish success/failure after call */
    const auto lstrtol = strtol(argv[1], &endptr, base);
    if (errno != 0) {
      cerr << __func__ << ' ' << __LINE__ << ' ' << strerror(errno) << '\n';
      std::terminate();
    } else if (endptr == argv[1]) {
      cerr << __func__ << ' ' << __LINE__ << ' ' << strerror(EINVAL) << '\n';
      std::terminate();
    }
    offsetStride = static_cast<uint64_t>(lstrtol);
  }
  uint64_t generator;
  const uint64_t upperlimit = 1UL << 55;
  const uint64_t ettPrimtal = 16127UL;
  uint64_t printout = 0UL;
  for (uint64_t iteration = offsetStride; iteration < upperlimit;
       iteration += ettPrimtal) {
    // Group A
    switch (iteration & 0x000000000000003F) {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x08:
    case 0x0A:
    case 0x0C:
    case 0x0F:
    case 0x10:
    case 0x11:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x19:
    case 0x1A:
    case 0x1D:
    case 0x1F:
    case 0x20:
    case 0x22:
    case 0x25:
    case 0x26:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2E:
    case 0x2F:
    case 0x30:
    case 0x33:
    case 0x35:
    case 0x37:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x3D:
    case 0x3E:
    case 0x3F:
      continue;
      break;
    // From msb to lsb:
    case 0x06: // 0b000110: 0,1,2
    case 0x07: // 0b000111: 0,1,3
    case 0x09: // 0b001001: 0,2,1
    case 0x0B: // 0b001011: 0,2,3
    case 0x0D:
    case 0x0E:
    case 0x12:
    case 0x13:
    case 0x18:
    case 0x1B:
    case 0x1C:
    case 0x1E:
    case 0x21:
    case 0x23:
    case 0x24:
    case 0x27:
    case 0x2C:
    case 0x2D:
    case 0x31:
    case 0x32:
    case 0x34:
    case 0x36:
    case 0x38:
    case 0x39:
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    // Group B
    switch (iteration & 0x0000000000000FC0) {
    case 0x00UL << 6:
    case 0x01UL << 6:
    case 0x02UL << 6:
    case 0x03UL << 6:
    case 0x04UL << 6:
    case 0x05UL << 6:
    case 0x08UL << 6:
    case 0x0AUL << 6:
    case 0x0CUL << 6:
    case 0x0FUL << 6:
    case 0x10UL << 6:
    case 0x11UL << 6:
    case 0x14UL << 6:
    case 0x15UL << 6:
    case 0x16UL << 6:
    case 0x17UL << 6:
    case 0x19UL << 6:
    case 0x1AUL << 6:
    case 0x1DUL << 6:
    case 0x1FUL << 6:
    case 0x20UL << 6:
    case 0x22UL << 6:
    case 0x25UL << 6:
    case 0x26UL << 6:
    case 0x28UL << 6:
    case 0x29UL << 6:
    case 0x2AUL << 6:
    case 0x2BUL << 6:
    case 0x2EUL << 6:
    case 0x2FUL << 6:
    case 0x30UL << 6:
    case 0x33UL << 6:
    case 0x35UL << 6:
    case 0x37UL << 6:
    case 0x3AUL << 6:
    case 0x3BUL << 6:
    case 0x3CUL << 6:
    case 0x3DUL << 6:
    case 0x3EUL << 6:
    case 0x3FUL << 6:
      continue;
      break;
    case 0x06UL << 6:
    case 0x07UL << 6:
    case 0x09UL << 6:
    case 0x0BUL << 6:
    case 0x0DUL << 6:
    case 0x0EUL << 6:
    case 0x12UL << 6:
    case 0x13UL << 6:
    case 0x18UL << 6:
    case 0x1BUL << 6:
    case 0x1CUL << 6:
    case 0x1EUL << 6:
    case 0x21UL << 6:
    case 0x23UL << 6:
    case 0x24UL << 6:
    case 0x27UL << 6:
    case 0x2CUL << 6:
    case 0x2DUL << 6:
    case 0x31UL << 6:
    case 0x32UL << 6:
    case 0x34UL << 6:
    case 0x36UL << 6:
    case 0x38UL << 6:
    case 0x39UL << 6:
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    // Group C
    switch (iteration & 0x000000000003F000) {
    case 0x00UL << 12:
    case 0x01UL << 12:
    case 0x02UL << 12:
    case 0x03UL << 12:
    case 0x04UL << 12:
    case 0x05UL << 12:
    case 0x08UL << 12:
    case 0x0AUL << 12:
    case 0x0CUL << 12:
    case 0x0FUL << 12:
    case 0x10UL << 12:
    case 0x11UL << 12:
    case 0x14UL << 12:
    case 0x15UL << 12:
    case 0x16UL << 12:
    case 0x17UL << 12:
    case 0x19UL << 12:
    case 0x1AUL << 12:
    case 0x1DUL << 12:
    case 0x1FUL << 12:
    case 0x20UL << 12:
    case 0x22UL << 12:
    case 0x25UL << 12:
    case 0x26UL << 12:
    case 0x28UL << 12:
    case 0x29UL << 12:
    case 0x2AUL << 12:
    case 0x2BUL << 12:
    case 0x2EUL << 12:
    case 0x2FUL << 12:
    case 0x30UL << 12:
    case 0x33UL << 12:
    case 0x35UL << 12:
    case 0x37UL << 12:
    case 0x3AUL << 12:
    case 0x3BUL << 12:
    case 0x3CUL << 12:
    case 0x3DUL << 12:
    case 0x3EUL << 12:
    case 0x3FUL << 12:
      continue;
      break;
    case 0x06UL << 12:
    case 0x07UL << 12:
    case 0x09UL << 12:
    case 0x0BUL << 12:
    case 0x0DUL << 12:
    case 0x0EUL << 12:
    case 0x12UL << 12:
    case 0x13UL << 12:
    case 0x18UL << 12:
    case 0x1BUL << 12:
    case 0x1CUL << 12:
    case 0x1EUL << 12:
    case 0x21UL << 12:
    case 0x23UL << 12:
    case 0x24UL << 12:
    case 0x27UL << 12:
    case 0x2CUL << 12:
    case 0x2DUL << 12:
    case 0x31UL << 12:
    case 0x32UL << 12:
    case 0x34UL << 12:
    case 0x36UL << 12:
    case 0x38UL << 12:
    case 0x39UL << 12:
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    // Group D
    switch (iteration & 0x0000000000FC0000) {
    case 0x00UL << 18:
    case 0x01UL << 18:
    case 0x02UL << 18:
    case 0x03UL << 18:
    case 0x04UL << 18:
    case 0x05UL << 18:
    case 0x08UL << 18:
    case 0x0AUL << 18:
    case 0x0CUL << 18:
    case 0x0FUL << 18:
    case 0x10UL << 18:
    case 0x11UL << 18:
    case 0x14UL << 18:
    case 0x15UL << 18:
    case 0x16UL << 18:
    case 0x17UL << 18:
    case 0x19UL << 18:
    case 0x1AUL << 18:
    case 0x1DUL << 18:
    case 0x1FUL << 18:
    case 0x20UL << 18:
    case 0x22UL << 18:
    case 0x25UL << 18:
    case 0x26UL << 18:
    case 0x28UL << 18:
    case 0x29UL << 18:
    case 0x2AUL << 18:
    case 0x2BUL << 18:
    case 0x2EUL << 18:
    case 0x2FUL << 18:
    case 0x30UL << 18:
    case 0x33UL << 18:
    case 0x35UL << 18:
    case 0x37UL << 18:
    case 0x3AUL << 18:
    case 0x3BUL << 18:
    case 0x3CUL << 18:
    case 0x3DUL << 18:
    case 0x3EUL << 18:
    case 0x3FUL << 18:
      continue;
      break;
    case 0x06UL << 18:
    case 0x07UL << 18:
    case 0x09UL << 18:
    case 0x0BUL << 18:
    case 0x0DUL << 18:
    case 0x0EUL << 18:
    case 0x12UL << 18:
    case 0x13UL << 18:
    case 0x18UL << 18:
    case 0x1BUL << 18:
    case 0x1CUL << 18:
    case 0x1EUL << 18:
    case 0x21UL << 18:
    case 0x23UL << 18:
    case 0x24UL << 18:
    case 0x27UL << 18:
    case 0x2CUL << 18:
    case 0x2DUL << 18:
    case 0x31UL << 18:
    case 0x32UL << 18:
    case 0x34UL << 18:
    case 0x36UL << 18:
    case 0x38UL << 18:
    case 0x39UL << 18:
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    // Group E
    switch (iteration & 0x000000003F000000) {
    case 0x00 << 24:
    case 0x01 << 24:
    case 0x02 << 24:
    case 0x03 << 24:
    case 0x04 << 24:
    case 0x05 << 24:
    case 0x08 << 24:
    case 0x0A << 24:
    case 0x0C << 24:
    case 0x0F << 24:
    case 0x10 << 24:
    case 0x11 << 24:
    case 0x14 << 24:
    case 0x15 << 24:
    case 0x16 << 24:
    case 0x17 << 24:
    case 0x19 << 24:
    case 0x1A << 24:
    case 0x1D << 24:
    case 0x1F << 24:
    case 0x20 << 24:
    case 0x22 << 24:
    case 0x25 << 24:
    case 0x26 << 24:
    case 0x28 << 24:
    case 0x29 << 24:
    case 0x2A << 24:
    case 0x2B << 24:
    case 0x2E << 24:
    case 0x2F << 24:
    case 0x30 << 24:
    case 0x33 << 24:
    case 0x35 << 24:
    case 0x37 << 24:
    case 0x3A << 24:
    case 0x3B << 24:
    case 0x3C << 24:
    case 0x3D << 24:
    case 0x3E << 24:
    case 0x3F << 24:
      continue;
      break;
    case 0x06 << 24:
    case 0x07 << 24:
    case 0x09 << 24:
    case 0x0B << 24:
    case 0x0D << 24:
    case 0x0E << 24:
    case 0x12 << 24:
    case 0x13 << 24:
    case 0x18 << 24:
    case 0x1B << 24:
    case 0x1C << 24:
    case 0x1E << 24:
    case 0x21 << 24:
    case 0x23 << 24:
    case 0x24 << 24:
    case 0x27 << 24:
    case 0x2C << 24:
    case 0x2D << 24:
    case 0x31 << 24:
    case 0x32 << 24:
    case 0x34 << 24:
    case 0x36 << 24:
    case 0x38 << 24:
    case 0x39 << 24:
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    // Group F
    switch (iteration & 0x0000000FC0000000) {
    case 0x00UL << 30:
    case 0x01UL << 30:
    case 0x02UL << 30:
    case 0x03UL << 30:
    case 0x04UL << 30:
    case 0x05UL << 30:
    case 0x08UL << 30:
    case 0x0AUL << 30:
    case 0x0CUL << 30:
    case 0x0FUL << 30:
    case 0x10UL << 30:
    case 0x11UL << 30:
    case 0x14UL << 30:
    case 0x15UL << 30:
    case 0x16UL << 30:
    case 0x17UL << 30:
    case 0x19UL << 30:
    case 0x1AUL << 30:
    case 0x1DUL << 30:
    case 0x1FUL << 30:
    case 0x20UL << 30:
    case 0x22UL << 30:
    case 0x25UL << 30:
    case 0x26UL << 30:
    case 0x28UL << 30:
    case 0x29UL << 30:
    case 0x2AUL << 30:
    case 0x2BUL << 30:
    case 0x2EUL << 30:
    case 0x2FUL << 30:
    case 0x30UL << 30:
    case 0x33UL << 30:
    case 0x35UL << 30:
    case 0x37UL << 30:
    case 0x3AUL << 30:
    case 0x3BUL << 30:
    case 0x3CUL << 30:
    case 0x3DUL << 30:
    case 0x3EUL << 30:
    case 0x3FUL << 30:
      continue;
      break;
    case 0x06UL << 30:
    case 0x07UL << 30:
    case 0x09UL << 30:
    case 0x0BUL << 30:
    case 0x0DUL << 30:
    case 0x0EUL << 30:
    case 0x12UL << 30:
    case 0x13UL << 30:
    case 0x18UL << 30:
    case 0x1BUL << 30:
    case 0x1CUL << 30:
    case 0x1EUL << 30:
    case 0x21UL << 30:
    case 0x23UL << 30:
    case 0x24UL << 30:
    case 0x27UL << 30:
    case 0x2CUL << 30:
    case 0x2DUL << 30:
    case 0x31UL << 30:
    case 0x32UL << 30:
    case 0x34UL << 30:
    case 0x36UL << 30:
    case 0x38UL << 30:
    case 0x39UL << 30:
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    // One of 15 ways to pick the best 3rd place set:
    // See table on https://en.wikipedia.org/wiki/UEFA_Euro_2020#Knockout_phase
    switch (iteration & 0x000000F000000000L) {
    case 0x0UL << 36: // ABCD
    case 0x1UL << 36: // ABC E
    case 0x2UL << 36: // ABC  F
    case 0x3UL << 36: // AB DE
    case 0x4UL << 36: // AB D F
    case 0x5UL << 36: // AB  EF
    case 0x6UL << 36: // A CDE
    case 0x7UL << 36: // A CD F
    case 0x8UL << 36: // A C EF
    case 0x9UL << 36: // A  DEF
    case 0xAUL << 36: //  BCDE
    case 0xBUL << 36: //  BCD F
    case 0xCUL << 36: //  BC EF
    case 0xDUL << 36: //  B DEF
    case 0xEUL << 36: //   CDEF
      break;
    case 0xFUL << 36: // There are 15 alternatives, not 16
      continue;
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      std::ios init(nullptr);
      init.copyfmt(std::cout);
      std::cout << std::hex;
      std::cout.width(14);
      std::cout << (iteration & 0x000000F000000000L) << ' ';
      std::cout << iteration << '\n';
      std::cout.copyfmt(init); // restore default formatting
      abort();
    }
    if (++printout % 10000UL == 0) {
      std::ios init(nullptr);
      init.copyfmt(std::cout);
      std::cout << std::hex;
      std::cout.width(14);
      std::cout << iteration << ' ';
      std::cout << upperlimit << '\n';
      std::cout.copyfmt(init); // restore default formatting
      const uint64_t tableA = iteration & 0x3FUL;
      const uint64_t tableB = (iteration >> 6) & 0x3FUL;
      const uint64_t tableC = (iteration >> 12) & 0x3FUL;
      const uint64_t tableD = (iteration >> 18) & 0x3FUL;
      const uint64_t tableE = (iteration >> 24) & 0x3FUL;
      const uint64_t tableF = (iteration >> 30) & 0x3FUL;
      const uint64_t thirdTable = (iteration >> 36) & 0xFUL;
      showGrundSpel('A', tableA);
      showGrundSpel('B', tableB);
      showGrundSpel('C', tableC);
      showGrundSpel('D', tableD);
      showGrundSpel('E', tableE);
      showGrundSpel('F', tableF);
      showTredjeTab(thirdTable);
      std::cout << '\n';
    }
  }
}
