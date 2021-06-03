#include <cassert>
#include <cinttypes>
#include <iomanip>
#include <iostream>
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
    std::cout << "0,1,2";
    break;
  case 0x0E:
    std::cout << "0,1,2";
    break;
  case 0x12:
    std::cout << "0,1,2";
    break;
  case 0x13:
    std::cout << "0,1,2";
    break;
  case 0x18:
    std::cout << "0,1,2";
    break;
  case 0x1B:
    std::cout << "0,1,2";
    break;
  case 0x1C:
    std::cout << "0,1,2";
    break;
  case 0x1E:
    std::cout << "0,1,2";
    break;
  case 0x21:
    std::cout << "0,1,2";
    break;
  case 0x23:
    std::cout << "0,1,2";
    break;
  case 0x24:
    std::cout << "0,1,2";
    break;
  case 0x27:
    std::cout << "0,1,2";
    break;
  case 0x2C:
    std::cout << "0,1,2";
    break;
  case 0x2D:
    std::cout << "0,1,2";
    break;
  case 0x31:
    std::cout << "0,1,2";
    break;
  case 0x32:
    std::cout << "0,1,2";
    break;
  case 0x34:
    std::cout << "0,1,2";
    break;
  case 0x36:
    std::cout << "0,1,2";
    break;
  case 0x38:
    std::cout << "0,1,2";
    break;
  case 0x39:
    std::cout << "0,1,2";
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  std::cout << ' ';
}
void showTredjeTab(uint64_t tabell) {
  switch (tabell) {
  case 0x0L:
    std::cout << "ABCD  ";
    break;
  case 0x1L: // ABC E
    std::cout << "ABCD  ";
    break;
  case 0x2L: // ABC  F
    std::cout << "ABCD  ";
    break;
  case 0x3L: // AB DE
    std::cout << "ABCD  ";
    break;
  case 0x4L: // AB D F
    std::cout << "ABCD  ";
    break;
  case 0x5L: // AB  EF
    std::cout << "ABCD  ";
    break;
  case 0x6L: // A CDE
    std::cout << "ABCD  ";
    break;
  case 0x7L: // A CD F
    std::cout << "ABCD  ";
    break;
  case 0x8L: // A C EF
    std::cout << "ABCD  ";
    break;
  case 0x9L: // A  DEF
    std::cout << "ABCD  ";
    break;
  case 0xAL: //  BCDE
    std::cout << "ABCD  ";
    break;
  case 0xBL: //  BCD F
    std::cout << "ABCD  ";
    break;
  case 0xCL: //  BC EF
    std::cout << "ABCD  ";
    break;
  case 0xDL:
    std::cout << " B DEF";
    break;
  case 0xEL:
    std::cout << "  CDEF";
    break;
  case 0xFL: // There are 15 alternatives, not 16
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    std::ios init(NULL);
    init.copyfmt(std::cout);
    std::cout << std::hex;
    std::cout.width(14);
    std::cout << tabell << '\n';
    std::cout.copyfmt(init); // restore default formatting
    abort();
  }
}
int main(int argc, char *argv[])
{
  // seq -w 0 3 | parallel ./a.out {}
  // Ger 0
  //     1
  //     2
  //     3
  std::cout << argv[1] << '\n';
  exit(0);
  uint64_t generator;
  const uint64_t upperlimit = 1L << 55;
  const uint64_t ettPrimtal = 16127L;
  uint64_t printout = 0L;
  for (uint64_t iteration = 0L; iteration < upperlimit;
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
    case 0x00L << 6:
    case 0x01L << 6:
    case 0x02L << 6:
    case 0x03L << 6:
    case 0x04L << 6:
    case 0x05L << 6:
    case 0x08L << 6:
    case 0x0AL << 6:
    case 0x0CL << 6:
    case 0x0FL << 6:
    case 0x10L << 6:
    case 0x11L << 6:
    case 0x14L << 6:
    case 0x15L << 6:
    case 0x16L << 6:
    case 0x17L << 6:
    case 0x19L << 6:
    case 0x1AL << 6:
    case 0x1DL << 6:
    case 0x1FL << 6:
    case 0x20L << 6:
    case 0x22L << 6:
    case 0x25L << 6:
    case 0x26L << 6:
    case 0x28L << 6:
    case 0x29L << 6:
    case 0x2AL << 6:
    case 0x2BL << 6:
    case 0x2EL << 6:
    case 0x2FL << 6:
    case 0x30L << 6:
    case 0x33L << 6:
    case 0x35L << 6:
    case 0x37L << 6:
    case 0x3AL << 6:
    case 0x3BL << 6:
    case 0x3CL << 6:
    case 0x3DL << 6:
    case 0x3EL << 6:
    case 0x3FL << 6:
      continue;
      break;
    case 0x06L << 6:
    case 0x07L << 6:
    case 0x09L << 6:
    case 0x0BL << 6:
    case 0x0DL << 6:
    case 0x0EL << 6:
    case 0x12L << 6:
    case 0x13L << 6:
    case 0x18L << 6:
    case 0x1BL << 6:
    case 0x1CL << 6:
    case 0x1EL << 6:
    case 0x21L << 6:
    case 0x23L << 6:
    case 0x24L << 6:
    case 0x27L << 6:
    case 0x2CL << 6:
    case 0x2DL << 6:
    case 0x31L << 6:
    case 0x32L << 6:
    case 0x34L << 6:
    case 0x36L << 6:
    case 0x38L << 6:
    case 0x39L << 6:
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    // Group C
    switch (iteration & 0x000000000003F000) {
    case 0x00L << 12:
    case 0x01L << 12:
    case 0x02L << 12:
    case 0x03L << 12:
    case 0x04L << 12:
    case 0x05L << 12:
    case 0x08L << 12:
    case 0x0AL << 12:
    case 0x0CL << 12:
    case 0x0FL << 12:
    case 0x10L << 12:
    case 0x11L << 12:
    case 0x14L << 12:
    case 0x15L << 12:
    case 0x16L << 12:
    case 0x17L << 12:
    case 0x19L << 12:
    case 0x1AL << 12:
    case 0x1DL << 12:
    case 0x1FL << 12:
    case 0x20L << 12:
    case 0x22L << 12:
    case 0x25L << 12:
    case 0x26L << 12:
    case 0x28L << 12:
    case 0x29L << 12:
    case 0x2AL << 12:
    case 0x2BL << 12:
    case 0x2EL << 12:
    case 0x2FL << 12:
    case 0x30L << 12:
    case 0x33L << 12:
    case 0x35L << 12:
    case 0x37L << 12:
    case 0x3AL << 12:
    case 0x3BL << 12:
    case 0x3CL << 12:
    case 0x3DL << 12:
    case 0x3EL << 12:
    case 0x3FL << 12:
      continue;
      break;
    case 0x06L << 12:
    case 0x07L << 12:
    case 0x09L << 12:
    case 0x0BL << 12:
    case 0x0DL << 12:
    case 0x0EL << 12:
    case 0x12L << 12:
    case 0x13L << 12:
    case 0x18L << 12:
    case 0x1BL << 12:
    case 0x1CL << 12:
    case 0x1EL << 12:
    case 0x21L << 12:
    case 0x23L << 12:
    case 0x24L << 12:
    case 0x27L << 12:
    case 0x2CL << 12:
    case 0x2DL << 12:
    case 0x31L << 12:
    case 0x32L << 12:
    case 0x34L << 12:
    case 0x36L << 12:
    case 0x38L << 12:
    case 0x39L << 12:
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    // Group D
    switch (iteration & 0x0000000000FC0000) {
    case 0x00L << 18:
    case 0x01L << 18:
    case 0x02L << 18:
    case 0x03L << 18:
    case 0x04L << 18:
    case 0x05L << 18:
    case 0x08L << 18:
    case 0x0AL << 18:
    case 0x0CL << 18:
    case 0x0FL << 18:
    case 0x10L << 18:
    case 0x11L << 18:
    case 0x14L << 18:
    case 0x15L << 18:
    case 0x16L << 18:
    case 0x17L << 18:
    case 0x19L << 18:
    case 0x1AL << 18:
    case 0x1DL << 18:
    case 0x1FL << 18:
    case 0x20L << 18:
    case 0x22L << 18:
    case 0x25L << 18:
    case 0x26L << 18:
    case 0x28L << 18:
    case 0x29L << 18:
    case 0x2AL << 18:
    case 0x2BL << 18:
    case 0x2EL << 18:
    case 0x2FL << 18:
    case 0x30L << 18:
    case 0x33L << 18:
    case 0x35L << 18:
    case 0x37L << 18:
    case 0x3AL << 18:
    case 0x3BL << 18:
    case 0x3CL << 18:
    case 0x3DL << 18:
    case 0x3EL << 18:
    case 0x3FL << 18:
      continue;
      break;
    case 0x06L << 18:
    case 0x07L << 18:
    case 0x09L << 18:
    case 0x0BL << 18:
    case 0x0DL << 18:
    case 0x0EL << 18:
    case 0x12L << 18:
    case 0x13L << 18:
    case 0x18L << 18:
    case 0x1BL << 18:
    case 0x1CL << 18:
    case 0x1EL << 18:
    case 0x21L << 18:
    case 0x23L << 18:
    case 0x24L << 18:
    case 0x27L << 18:
    case 0x2CL << 18:
    case 0x2DL << 18:
    case 0x31L << 18:
    case 0x32L << 18:
    case 0x34L << 18:
    case 0x36L << 18:
    case 0x38L << 18:
    case 0x39L << 18:
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
    case 0x00L << 30:
    case 0x01L << 30:
    case 0x02L << 30:
    case 0x03L << 30:
    case 0x04L << 30:
    case 0x05L << 30:
    case 0x08L << 30:
    case 0x0AL << 30:
    case 0x0CL << 30:
    case 0x0FL << 30:
    case 0x10L << 30:
    case 0x11L << 30:
    case 0x14L << 30:
    case 0x15L << 30:
    case 0x16L << 30:
    case 0x17L << 30:
    case 0x19L << 30:
    case 0x1AL << 30:
    case 0x1DL << 30:
    case 0x1FL << 30:
    case 0x20L << 30:
    case 0x22L << 30:
    case 0x25L << 30:
    case 0x26L << 30:
    case 0x28L << 30:
    case 0x29L << 30:
    case 0x2AL << 30:
    case 0x2BL << 30:
    case 0x2EL << 30:
    case 0x2FL << 30:
    case 0x30L << 30:
    case 0x33L << 30:
    case 0x35L << 30:
    case 0x37L << 30:
    case 0x3AL << 30:
    case 0x3BL << 30:
    case 0x3CL << 30:
    case 0x3DL << 30:
    case 0x3EL << 30:
    case 0x3FL << 30:
      continue;
      break;
    case 0x06L << 30:
    case 0x07L << 30:
    case 0x09L << 30:
    case 0x0BL << 30:
    case 0x0DL << 30:
    case 0x0EL << 30:
    case 0x12L << 30:
    case 0x13L << 30:
    case 0x18L << 30:
    case 0x1BL << 30:
    case 0x1CL << 30:
    case 0x1EL << 30:
    case 0x21L << 30:
    case 0x23L << 30:
    case 0x24L << 30:
    case 0x27L << 30:
    case 0x2CL << 30:
    case 0x2DL << 30:
    case 0x31L << 30:
    case 0x32L << 30:
    case 0x34L << 30:
    case 0x36L << 30:
    case 0x38L << 30:
    case 0x39L << 30:
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    // One of 15 ways to pick the best 3rd place set:
    // See table on https://en.wikipedia.org/wiki/UEFA_Euro_2020#Knockout_phase
    switch (iteration & 0x000000F000000000L) {
    case 0x0L << 36: // ABCD
    case 0x1L << 36: // ABC E
    case 0x2L << 36: // ABC  F
    case 0x3L << 36: // AB DE
    case 0x4L << 36: // AB D F
    case 0x5L << 36: // AB  EF
    case 0x6L << 36: // A CDE
    case 0x7L << 36: // A CD F
    case 0x8L << 36: // A C EF
    case 0x9L << 36: // A  DEF
    case 0xAL << 36: //  BCDE
    case 0xBL << 36: //  BCD F
    case 0xCL << 36: //  BC EF
    case 0xDL << 36: //  B DEF
    case 0xEL << 36: //   CDEF
      break;
    case 0xFL << 36: // There are 15 alternatives, not 16
      continue;
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      std::ios init(NULL);
      init.copyfmt(std::cout);
      std::cout << std::hex;
      std::cout.width(14);
      std::cout << (iteration & 0x000000F000000000L) << ' ';
      std::cout << iteration << '\n';
      std::cout.copyfmt(init); // restore default formatting
      abort();
    }
    if (++printout % 1000000L == 0) {
      std::ios init(NULL);
      init.copyfmt(std::cout);
      std::cout << std::hex;
      std::cout.width(14);
      std::cout << iteration << ' ';
      std::cout << upperlimit << '\n';
      std::cout.copyfmt(init); // restore default formatting
      const uint64_t tableA = iteration & 0x3FL;
      const uint64_t tableB = (iteration >> 6) & 0x3FL;
      const uint64_t tableC = (iteration >> 12) & 0x3FL;
      const uint64_t tableD = (iteration >> 18) & 0x3FL;
      const uint64_t tableE = (iteration >> 24) & 0x3FL;
      const uint64_t tableF = (iteration >> 30) & 0x3FL;
      const uint64_t thirdTable = (iteration >> 36) & 0xFL;
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
