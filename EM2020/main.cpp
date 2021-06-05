#include <algorithm> //std::find_if
#include <cassert>
#include <cinttypes>
#include <cstring>
#include <gsl/gsl-lite.hpp>
#include <iomanip>
#include <iostream>
using std::cerr;
// g++ -I ~/gsl-lite/include main.cpp
// clang-format -i main.cpp
// ./a.out
// seq -w 0 3 | parallel -u ./a.out {} 524287
// seq -w 0 15 | parallel -u ./a.out {} 16127
// seq -w 0 15 | parallel -u ./a.out {} 16127 tur ita wal
void parseArgs(int argc, gsl::span<char *> span_argv, uint64_t &offsetStride,
               uint64_t &ettPrimtal);
const uint64_t upperlimit = 1UL << 55;
uint64_t ettPrimtal = 16127UL;
// const uint64_t ettPrimtal = 131071UL;
// const uint64_t ettPrimtal = 524287UL;
uint64_t completeFactor = 1UL;
static int maxSoFar = 0;
static uint64_t maxIteration = 0;
enum e_team {
  tur,
  ita,
  wal,
  sui,
  den,
  fin,
  bel,
  rus,
  ned,
  ukr,
  aut,
  mkd,
  eng,
  cro,
  sco,
  cze,
  esp,
  swe,
  pol,
  svk,
  hun,
  por,
  fra,
  ger
};
// Games are officially numbered from 1 to 51.
e_team game[53][2] = {
    {},
    {tur, ita} /*1*/,
    {wal, sui},
    {den, fin},
    {bel, rus},
    {ned, ukr},
    {aut, mkd},
    {eng, cro},
    {sco, cze},
    {esp, swe},
    {pol, svk},
    {hun, por},
    {fra, ger},
    {tur, wal},
    {ita, sui},
    {fin, rus},
    {den, bel},
    {ned, aut},
    {ukr, mkd},
    {cro, cze},
    {eng, sco},
    {swe, svk},
    {esp, pol},
    {hun, fra},
    {por, ger},
    {sui, tur},
    {ita, wal},
    {rus, den},
    {fin, bel},
    {mkd, ned},
    {ukr, aut},
    {cro, sco},
    {cze, eng},
    {svk, esp},
    {swe, pol},
    {por, fra},
    {ger, hun} /*36*/,
    {} /*1A-2C*/,
    {} /*2A-2B*/,
    {} /*1B-3ADEF 39*/,
    {} /*1C-3DEF 40*/,
    {} /*1F-3ABC 41*/,
    {} /*2D-2E*/,
    {} /*1E-3ABCD 43*/,
    {} /*1D-2F, 44*/,
    {} /*41-42, 45*/,
    {} /*37-39, 46*/,
    {} /*40-38, 47*/,
    {} /*43-44, 48*/,
    {} /*46-45, 49*/,
    {} /*48-47, 50*/,
    {} /*49-50, 51*/,
    {} /*Winner*/,
};
struct s_saabare {
  char namnkod[7];
  e_team grupp_placering[6][2];
  e_team kvartsfinallag[8];
  e_team semifinallag[4];
  e_team finallag[2];
  e_team vinnare[1];
  int poang;
} saab[1] = {
    {"Test",
     {{tur, ita}, {den, fin}, {aut, mkd}, {eng, cro}, {pol, svk}, {hun, por}},
     {tur, den, aut, eng, pol, hun, ita, cro},
     {tur, aut, pol, ita},
     {tur, pol},
     {tur},
     0}};
extern enum e_team operator++(enum e_team &that);
extern const enum e_team operator++(enum e_team &that, int);
std::ostream &operator<<(std::ostream &o, const e_team &team) {
  switch (team) {
  case tur:
    o << "tur";
    break;
  case ita:
    o << "ita";
    break;
  case wal:
    o << "wal";
    break;
  case sui:
    o << "sui";
    break;
  case den:
    o << "den";
    break;
  case fin:
    o << "fin";
    break;
  case bel:
    o << "bel";
    break;
  case rus:
    o << "rus";
    break;
  case ned:
    o << "ned";
    break;
  case ukr:
    o << "ukr";
    break;
  case aut:
    o << "aut";
    break;
  case mkd:
    o << "mkd";
    break;
  case eng:
    o << "eng";
    break;
  case cro:
    o << "cro";
    break;
  case sco:
    o << "sco";
    break;
  case cze:
    o << "cze";
    break;
  case esp:
    o << "esp";
    break;
  case swe:
    o << "swe";
    break;
  case pol:
    o << "pol";
    break;
  case svk:
    o << "svk";
    break;
  case hun:
    o << "hun";
    break;
  case por:
    o << "por";
    break;
  case fra:
    o << "fra";
    break;
  case ger:
    o << "ger";
    break;
  }
  return o;
}
void showGrundSpel(char grp, uint64_t table) {
  std::cout << grp << ':';
  const int offset =
      grp == 'A'
          ? 0
          : grp == 'B'
                ? 4
                : grp == 'C' ? 8 : grp == 'D' ? 12 : grp == 'E' ? 16 : 20;
  const unsigned win = table >> 4;
  const unsigned secnd = (table & 0xC) >> 2;
  const unsigned third = table & 0x3;
  std::cout << (e_team)(win + offset) << ',' << (e_team)(secnd + offset) << ','
            << (e_team)(third + offset) << ' ';
  switch (grp) {
  case 'A':
    game[37][0] = (e_team)(win + offset);
    game[38][0] = (e_team)(secnd + offset);
    break;
  case 'B':
    game[39][0] = (e_team)(win + offset);
    game[38][1] = (e_team)(secnd + offset);
    break;
  case 'C':
    game[40][0] = (e_team)(win + offset);
    game[37][1] = (e_team)(secnd + offset);
    break;
  case 'D':
    game[44][0] = (e_team)(win + offset);
    game[42][0] = (e_team)(secnd + offset);
    break;
  case 'E':
    game[43][0] = (e_team)(win + offset);
    game[42][1] = (e_team)(secnd + offset);
    break;
  case 'F':
    game[41][0] = (e_team)(win + offset);
    game[44][1] = (e_team)(secnd + offset);
    break;
  default:
    cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
}
void calcGrundSpel(char grp, uint64_t table) {
  const int offset =
      grp == 'A'
          ? 0
          : grp == 'B'
                ? 4
                : grp == 'C' ? 8 : grp == 'D' ? 12 : grp == 'E' ? 16 : 20;
  const unsigned win = table >> 4;
  const unsigned secnd = (table & 0xC) >> 2;
  unsigned saabOffset = 0;
  switch (grp) {
  case 'A':
    game[37][0] = (e_team)(win + offset);
    game[38][0] = (e_team)(secnd + offset);
    saabOffset = 0;
    break;
  case 'B':
    game[39][0] = (e_team)(win + offset);
    game[38][1] = (e_team)(secnd + offset);
    saabOffset = 1;
    break;
  case 'C':
    game[40][0] = (e_team)(win + offset);
    game[37][1] = (e_team)(secnd + offset);
    saabOffset = 2;
    break;
  case 'D':
    game[44][0] = (e_team)(win + offset);
    game[42][0] = (e_team)(secnd + offset);
    saabOffset = 3;
    break;
  case 'E':
    game[43][0] = (e_team)(win + offset);
    game[42][1] = (e_team)(secnd + offset);
    saabOffset = 4;
    break;
  case 'F':
    game[41][0] = (e_team)(win + offset);
    game[44][1] = (e_team)(secnd + offset);
    saabOffset = 5;
    break;
  default:
    cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  for (auto &saabare : saab) {
    if ((e_team)(win + offset) == saabare.grupp_placering[saabOffset][0]) {
      saabare.poang += 10;
    } else if ((e_team)(win + offset) ==
               saabare.grupp_placering[saabOffset][1]) {
      saabare.poang += 7;
    }
    if ((e_team)(secnd + offset) == saabare.grupp_placering[saabOffset][1]) {
      saabare.poang += 10;
    } else if ((e_team)(secnd + offset) ==
               saabare.grupp_placering[saabOffset][0]) {
      saabare.poang += 7;
    }
  }
}
void showTredjeTab(uint64_t tabell, uint64_t tableA, uint64_t tableB,
                   uint64_t tableC, uint64_t tableD, uint64_t tableE,
                   uint64_t tableF) {
  /*1B-ADEF3, match 39*/
  /*1C-DEF3, match 40*/
  /*1E-ABCD3, match 43*/
  /*1F-ABC3, match 41*/
  // 39 40 43 41
  // 1B 1C 1E 1F
  switch (tabell) {
  case 0:
    std::cout << "ABCD--";
    // 3A 3D 3B 3C
    game[39][1] = (e_team)((tableA & 0x3) + 0);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
    break;
  case 1:
    std::cout << "ABC-E-";
    // 3A 3E 3B 3C
    game[39][1] = (e_team)(tableA & 0x3);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
    break;
  case 2:
    std::cout << "ABC--F";
    // 3A 3F 3B 3C
    game[39][1] = (e_team)((tableA & 0x3) + 0);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
    break;
  case 3:
    std::cout << "AB-DE-";
    // 3D 3E 3A 3B
    game[39][1] = (e_team)((tableD & 0x3) + 12);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableA & 0x3) + 0);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 4:
    std::cout << "AB-D-F";
    // 3D 3F 3A 3B
    game[39][1] = (e_team)((tableD & 0x3) + 12);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableA & 0x3) + 0);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 5:
    std::cout << "AB--EF";
    // 3E 3F 3B 3A
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 6:
    std::cout << "A-CDE-";
    // 3E 3D 3C 3A
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 7:
    std::cout << "A-CD-F";
    // 3F 3D 3C 3A
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 8:
    std::cout << "A-C-EF";
    // 3E 3F 3C 3A
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 9:
    std::cout << "A--DEF";
    // 3E 3F 3D 3A
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableD & 0x3) + 12);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 10:
    std::cout << "-BCDE-";
    // 3E 3D 3B 3C
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
    break;
  case 11:
    std::cout << "-BCD-F";
    // 3F 3D 3C 3B
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 12:
    std::cout << "-BC-EF";
    // 3F 3E 3C 3B
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 13:
    std::cout << "-B-DEF";
    // 3F 3E 3D 3B
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableD & 0x3) + 12);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 14:
    std::cout << "--CDEF";
    // 3F 3E 3D 3C
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableD & 0x3) + 12);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
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
void calcTredjeTab(uint64_t tabell, uint64_t tableA, uint64_t tableB,
                   uint64_t tableC, uint64_t tableD, uint64_t tableE,
                   uint64_t tableF) {
  /*1B-ADEF3, match 39*/
  /*1C-DEF3, match 40*/
  /*1E-ABCD3, match 43*/
  /*1F-ABC3, match 41*/
  // 39 40 43 41
  // 1B 1C 1E 1F
  switch (tabell) {
  case 0:
    // 3A 3D 3B 3C
    game[39][1] = (e_team)((tableA & 0x3) + 0);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
    break;
  case 1:
    // 3A 3E 3B 3C
    game[39][1] = (e_team)(tableA & 0x3);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
    break;
  case 2:
    // 3A 3F 3B 3C
    game[39][1] = (e_team)((tableA & 0x3) + 0);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
    break;
  case 3:
    // 3D 3E 3A 3B
    game[39][1] = (e_team)((tableD & 0x3) + 12);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableA & 0x3) + 0);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 4:
    // 3D 3F 3A 3B
    game[39][1] = (e_team)((tableD & 0x3) + 12);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableA & 0x3) + 0);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 5:
    // 3E 3F 3B 3A
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 6:
    // 3E 3D 3C 3A
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 7:
    // 3F 3D 3C 3A
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 8:
    // 3E 3F 3C 3A
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 9:
    // 3E 3F 3D 3A
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableF & 0x3) + 20);
    game[43][1] = (e_team)((tableD & 0x3) + 12);
    game[41][1] = (e_team)((tableA & 0x3) + 0);
    break;
  case 10:
    // 3E 3D 3B 3C
    game[39][1] = (e_team)((tableE & 0x3) + 16);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableB & 0x3) + 4);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
    break;
  case 11:
    // 3F 3D 3C 3B
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableD & 0x3) + 12);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 12:
    // 3F 3E 3C 3B
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableC & 0x3) + 8);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 13:
    // 3F 3E 3D 3B
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableD & 0x3) + 12);
    game[41][1] = (e_team)((tableB & 0x3) + 4);
    break;
  case 14:
    // 3F 3E 3D 3C
    game[39][1] = (e_team)((tableF & 0x3) + 20);
    game[40][1] = (e_team)((tableE & 0x3) + 16);
    game[43][1] = (e_team)((tableD & 0x3) + 12);
    game[41][1] = (e_team)((tableC & 0x3) + 8);
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
  uint64_t offsetStride = 0;
  if (argc > 1) {
    gsl::span<char *> span_argv(argv, argc);
    parseArgs(argc, span_argv, offsetStride, ettPrimtal);
  }
  uint64_t generator;
  for (uint64_t iteration = offsetStride; iteration < upperlimit;
       iteration += (ettPrimtal * completeFactor)) {
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
    const uint64_t tableA = iteration & 0x3FUL;
    const uint64_t tableB = (iteration >> 6) & 0x3FUL;
    const uint64_t tableC = (iteration >> 12) & 0x3FUL;
    const uint64_t tableD = (iteration >> 18) & 0x3FUL;
    const uint64_t tableE = (iteration >> 24) & 0x3FUL;
    const uint64_t tableF = (iteration >> 30) & 0x3FUL;
    const uint64_t thirdTable = (iteration >> 36) & 0xFUL;
    saab[0].poang = 0;
    calcGrundSpel('A', tableA);
    calcGrundSpel('B', tableB);
    calcGrundSpel('C', tableC);
    calcGrundSpel('D', tableD);
    calcGrundSpel('E', tableE);
    calcGrundSpel('F', tableF);
    calcTredjeTab(thirdTable, tableA, tableB, tableC, tableD, tableE, tableF);
#ifndef NDEBUG
    // Kontrollera att alla fält match 37-44 är olika
    for (int match = 37; match <= 44; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        for (int match2 = 37; match2 <= 44; ++match2) {
          for (int hemmaBorta2 = 0; hemmaBorta2 < 2; ++hemmaBorta2) {
            const e_team t2 = game[match2][hemmaBorta2];
            if (tt == t2) {
              assert(match == match2);
              assert(hemmaBorta == hemmaBorta2);
            }
          }
        }
      }
    }
#endif
    // Avgör match 37 till 44, fyll i match 45 till 48
    uint64_t result;
    result = ((iteration >> (37 + 3)) & 0x1);
    game[46][1] = game[37][result];
    result = ((iteration >> (38 + 3)) & 0x1);
    game[47][1] = game[38][result];
    result = ((iteration >> (39 + 3)) & 0x1);
    game[46][0] = game[39][result];
    result = ((iteration >> (40 + 3)) & 0x1);
    game[47][0] = game[40][result];
    result = ((iteration >> (41 + 3)) & 0x1);
    game[45][0] = game[41][result];
    result = ((iteration >> (42 + 3)) & 0x1);
    game[45][1] = game[42][result];
    result = ((iteration >> (43 + 3)) & 0x1);
    game[48][0] = game[43][result];
    result = ((iteration >> (44 + 3)) & 0x1);
    game[48][1] = game[44][result];
#ifndef NDEBUG
    // Kontrollera att alla fält match 37-44 är olika
    for (int match = 45; match <= 48; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        for (int match2 = 45; match2 <= 48; ++match2) {
          for (int hemmaBorta2 = 0; hemmaBorta2 < 2; ++hemmaBorta2) {
            const e_team t2 = game[match2][hemmaBorta2];
            if (tt == t2) {
              assert(match == match2);
              assert(hemmaBorta == hemmaBorta2);
            }
          }
        }
      }
    }
#endif
    {
      gsl::span<e_team> span_quarts(saab[0].kvartsfinallag, 8);
      for (int match = 45; match <= 48; ++match) {
        for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
          const e_team tt = game[match][hemmaBorta];
          const auto *f =
              std::find_if(span_quarts.cbegin(), span_quarts.cend(),
                           [tt](const e_team tm) { return tt == tm; });
          if (f != span_quarts.cend()) {
            saab[0].poang += 15;
          }
        }
      }
    }
    // Avgör match 45 till 48, fyll i match 49 och 50
    result = ((iteration >> (45 + 3)) & 0x1);
    game[49][1] = game[45][result];
    result = ((iteration >> (46 + 3)) & 0x1);
    game[49][0] = game[46][result];
    result = ((iteration >> (47 + 3)) & 0x1);
    game[50][1] = game[47][result];
    result = ((iteration >> (48 + 3)) & 0x1);
    game[50][0] = game[48][result];
#ifndef NDEBUG
    // Kontrollera att alla fält match 37-44 är olika
    for (int match = 49; match <= 50; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        for (int match2 = 49; match2 <= 50; ++match2) {
          for (int hemmaBorta2 = 0; hemmaBorta2 < 2; ++hemmaBorta2) {
            const e_team t2 = game[match2][hemmaBorta2];
            if (tt == t2) {
              assert(match == match2);
              assert(hemmaBorta == hemmaBorta2);
            }
          }
        }
      }
    }
#endif
    {
      gsl::span<e_team> span_semi(saab[0].semifinallag, 4);
      for (int match = 49; match <= 50; ++match) {
        for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
          const e_team tt = game[match][hemmaBorta];
          const auto *f =
              std::find_if(span_semi.cbegin(), span_semi.cend(),
                           [tt](const e_team tm) { return tt == tm; });
          if (f != span_semi.cend()) {
            saab[0].poang += 25;
          }
        }
      }
    }
    // Avgör match 49 och 50
    result = ((iteration >> (49 + 3)) & 0x1);
    game[51][0] = game[49][result];
    result = ((iteration >> (50 + 3)) & 0x1);
    game[51][1] = game[50][result];
    {
      gsl::span<e_team> span_final(saab[0].finallag, 2);
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[51][hemmaBorta];
        const auto *f =
            std::find_if(span_final.cbegin(), span_final.cend(),
                         [tt](const e_team tm) { return tt == tm; });
        if (f != span_final.cend()) {
          saab[0].poang += 35;
        }
      }
    }
    // Avgör finalen, match 51
    result = ((iteration >> (51 + 3)) & 0x1);
    game[52][0] = game[51][result];
    if (game[52][0] == saab[0].vinnare[0]) {
      saab[0].poang += 50;
    }
    if (maxSoFar < saab[0].poang) {
      // Utskrift när max ökas
      maxSoFar = saab[0].poang;
      maxIteration = iteration;
      // Skriv ut
      std::ios init(nullptr);
      init.copyfmt(std::cout);
      std::cout << std::hex;
      std::cout.width(14);
      std::cout << iteration << ' ';
      std::cout << upperlimit << '\n';
      std::cout.copyfmt(init); // restore default formatting
      showGrundSpel('A', tableA);
      showGrundSpel('B', tableB);
      showGrundSpel('C', tableC);
      showGrundSpel('D', tableD);
      showGrundSpel('E', tableE);
      showGrundSpel('F', tableF);
      std::cout << '\n';
      for (int match = 45; match <= 48; ++match) {
        for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
          const e_team tt = game[match][hemmaBorta];
          std::cout << tt;
          if (match != 48 || hemmaBorta != 1) {
            std::cout << ',';
          } else {
            std::cout << ' ';
          }
        }
      }
      for (int match = 49; match <= 50; ++match) {
        for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
          const e_team tt = game[match][hemmaBorta];
          std::cout << tt;
          if (match != 50 || hemmaBorta != 1) {
            std::cout << ',';
          } else {
            std::cout << ' ';
          }
        }
      }
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[51][hemmaBorta];
        std::cout << tt;
        if (hemmaBorta != 1) {
          std::cout << ',';
        } else {
          std::cout << ' ';
        }
      }
      std::cout << ' ' << game[52][0];
      std::cout << ' ' << saab[0].poang;
      std::cout << '\n';
    }
  }
  {
    const uint64_t tableA = maxIteration & 0x3FUL;
    const uint64_t tableB = (maxIteration >> 6) & 0x3FUL;
    const uint64_t tableC = (maxIteration >> 12) & 0x3FUL;
    const uint64_t tableD = (maxIteration >> 18) & 0x3FUL;
    const uint64_t tableE = (maxIteration >> 24) & 0x3FUL;
    const uint64_t tableF = (maxIteration >> 30) & 0x3FUL;
    const uint64_t thirdTable = (maxIteration >> 36) & 0xFUL;
    // Skriv ut
    std::cout << __FILE__ << __LINE__ << ' ' << offsetStride << ' ';
    std::ios init(nullptr);
    init.copyfmt(std::cout);
    std::cout << std::hex;
    std::cout.width(14);
    std::cout << maxIteration << '\n';
    std::cout.copyfmt(init); // restore default formatting
    showGrundSpel('A', tableA);
    showGrundSpel('B', tableB);
    showGrundSpel('C', tableC);
    showGrundSpel('D', tableD);
    showGrundSpel('E', tableE);
    showGrundSpel('F', tableF);
    showTredjeTab(thirdTable, tableA, tableB, tableC, tableD, tableE, tableF);
    std::cout << '\n';
    for (int match = 45; match <= 48; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        std::cout << tt;
        if (match != 48 || hemmaBorta != 1) {
          std::cout << ',';
        } else {
          std::cout << ' ';
        }
      }
    }
    for (int match = 49; match <= 50; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        std::cout << tt;
        if (match != 50 || hemmaBorta != 1) {
          std::cout << ',';
        } else {
          std::cout << ' ';
        }
      }
    }
    for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
      const e_team tt = game[51][hemmaBorta];
      std::cout << tt;
      if (hemmaBorta != 1) {
        std::cout << ',';
      } else {
        std::cout << ' ';
      }
    }
    std::cout << ' ' << game[52][0];
    std::cout << ' ' << maxSoFar;
    std::cout << '\n';
  }
}
enum e_team operator++(enum e_team &that) {
  that = static_cast<enum e_team>(static_cast<int>(that) + 1);
  return that;
}
const enum e_team operator++(enum e_team &that, int) {
  enum e_team result = that;
  ++that;
  return result;
}
void parseArgs(int argc, gsl::span<char *> span_argv, uint64_t &offsetStride,
               uint64_t &ettPrimtal) {
  int base = 10;
  char *endptr;
  errno = 0; /* To distinguish success/failure after call */
  const auto lstrtol = strtol(span_argv[1], &endptr, base);
  if (errno != 0) {
    cerr << __func__ << ' ' << __LINE__ << ' ' << strerror(errno) << '\n';
    std::terminate();
  } else if (endptr == span_argv[1]) {
    cerr << __func__ << ' ' << __LINE__ << ' ' << strerror(EINVAL) << '\n';
    std::terminate();
  }
  offsetStride = static_cast<uint64_t>(lstrtol);
  if (argc > 2) {
    errno = 0;
    const auto lstrtol = strtol(span_argv[2], &endptr, base);
    if (errno != 0) {
      cerr << __func__ << ' ' << __LINE__ << ' ' << strerror(errno) << '\n';
      std::terminate();
    } else if (endptr == span_argv[1]) {
      cerr << __func__ << ' ' << __LINE__ << ' ' << strerror(EINVAL) << '\n';
      std::terminate();
    }
    ettPrimtal = static_cast<uint64_t>(lstrtol);
  }
  if (argc > 3) {
    // 3 teams group A follows
    assert(argc >= 6);
    char *const arg3 = span_argv[3];
    char *const arg4 = span_argv[4];
    char *const arg5 = span_argv[5];
    const e_team winA =
        strcmp("tur", arg3) == 0
            ? tur
            : strcmp("ita", arg3) == 0
                  ? ita
                  : strcmp("wal", arg3) == 0
                        ? wal
                        : strcmp("sui", arg3) == 0 ? sui : (e_team)-1;
    const e_team scndA =
        strcmp("tur", arg4) == 0
            ? tur
            : strcmp("ita", arg4) == 0
                  ? ita
                  : strcmp("wal", arg4) == 0
                        ? wal
                        : strcmp("sui", arg4) == 0 ? sui : (e_team)-1;
    const e_team rd3A =
        strcmp("tur", arg5) == 0
            ? tur
            : strcmp("ita", arg5) == 0
                  ? ita
                  : strcmp("wal", arg5) == 0
                        ? wal
                        : strcmp("sui", arg5) == 0 ? sui : (e_team)-1;
    assert(winA != (e_team)-1);
    assert(scndA != (e_team)-1);
    assert(rd3A != (e_team)-1);
    assert(winA != scndA);
    assert(winA != rd3A);
    assert(scndA != rd3A);
    if (argc > 6) {
      // Group B win,2nd,3rd
    } else {
      completeFactor = 1UL << 6;
      offsetStride *= 1UL << 6;
      offsetStride +=
          ((winA - 0) << 4) + ((scndA - 0) << 2) + ((rd3A - 0) << 0);
    }
  }
}
