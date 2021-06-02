#include <cinttypes>
#include <iostream>
int main()
{
  uint64_t generator;
  const uint64_t upperlimit = 1L << 55;
  const uint64_t ettPrimtal = 16127L;
  uint64_t printout = 0L;
  for (uint64_t iteration = 0L; iteration < upperlimit; iteration += ettPrimtal) {
    // Group A
    switch(iteration & 0x000000000000003F) {
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
    case 0x06:
    case 0x07:
    case 0x09:
    case 0x0B:
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
      std::cerr << __FILE__<<__LINE__<<'\n';
      abort();
    }
    // Group B
    switch(iteration & 0x0000000000000FC0) {
    case 0x00<<6:
    case 0x01<<6:
    case 0x02<<6:
    case 0x03<<6:
    case 0x04<<6:
    case 0x05<<6:
    case 0x08<<6:
    case 0x0A<<6:
    case 0x0C<<6:
    case 0x0F<<6:
    case 0x10<<6:
    case 0x11<<6:
    case 0x14<<6:
    case 0x15<<6:
    case 0x16<<6:
    case 0x17<<6:
    case 0x19<<6:
    case 0x1A<<6:
    case 0x1D<<6:
    case 0x1F<<6:
    case 0x20<<6:
    case 0x22<<6:
    case 0x25<<6:
    case 0x26<<6:
    case 0x28<<6:
    case 0x29<<6:
    case 0x2A<<6:
    case 0x2B<<6:
    case 0x2E<<6:
    case 0x2F<<6:
    case 0x30<<6:
    case 0x33<<6:
    case 0x35<<6:
    case 0x37<<6:
    case 0x3A<<6:
    case 0x3B<<6:
    case 0x3C<<6:
    case 0x3D<<6:
    case 0x3E<<6:
    case 0x3F<<6:
      continue;
      break;
    case 0x06<<6:
    case 0x07<<6:
    case 0x09<<6:
    case 0x0B<<6:
    case 0x0D<<6:
    case 0x0E<<6:
    case 0x12<<6:
    case 0x13<<6:
    case 0x18<<6:
    case 0x1B<<6:
    case 0x1C<<6:
    case 0x1E<<6:
    case 0x21<<6:
    case 0x23<<6:
    case 0x24<<6:
    case 0x27<<6:
    case 0x2C<<6:
    case 0x2D<<6:
    case 0x31<<6:
    case 0x32<<6:
    case 0x34<<6:
    case 0x36<<6:
    case 0x38<<6:
    case 0x39<<6:
      break;
    default:
      std::cerr << __FILE__<<__LINE__<<'\n';
      abort();
    }
    if ((iteration & 0x00000000000000C0) == (iteration & 0x0000000000000300)) {
      continue;
    }
    if ((iteration & 0x0000000000000C00) == (iteration & 0x000000000000C000)) {
      continue;
    }
    if ((iteration & 0x0000000000000C00) == (iteration & 0x0000000000003000)) {
      continue;
    }
    // Group C
    if ((iteration & 0x0000000000000300) == (iteration & 0x0000000000000C00)) {
      continue;
    }
    if ((iteration & 0x0000000000003000) == (iteration & 0x0000000000000300)) {
      continue;
    }
    if ((iteration & 0x0000000000003000) == (iteration & 0x0000000000000C00)) {
      continue;
    }
    // Group D
    if ((iteration & 0x000000000000C000) == (iteration & 0x0000000000030000)) {
      continue;
    }
    if ((iteration & 0x00000000000C0000) == (iteration & 0x0000000000C00000)) {
      continue;
    }
    if ((iteration & 0x00000000000C0000) == (iteration & 0x0000000000300000)) {
      continue;
    }
    if (++printout % 100000000L == 0) {
      std::cout << iteration / 10000000L << ' ' << upperlimit / 10000000L << '\n';
    }
  }
}
