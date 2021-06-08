#include <algorithm> //std::find_if
#include <cassert>
#include <cinttypes>
#include <cstring>
#include <gsl/gsl-lite.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
using std::cerr;
// g++ -I ~/gsl-lite/include main.cpp
// clang-format -i main.cpp
// ./a.out
// seq -w 0 3 | parallel -u ./a.out {} 524287
// seq -w 0 15 | parallel -u ./a.out {} 16127
// seq -w 0 15 | parallel -u ./a.out {} 16127 tur ita wal
void parseArgs(int argc, gsl::span<char *> span_argv, uint64_t *completeFactor,
               uint64_t *offsetStride, uint64_t *ettPrimtal);
const uint64_t upperlimit = 1UL << 55;
uint64_t ettPrimtal = 16127UL;
// const uint64_t ettPrimtal = 131071UL;
// const uint64_t ettPrimtal = 524287UL;
uint64_t completeFactor = 1UL;
static int maxSoFar = 0;
static uint64_t maxIteration = 0;
int totFifa;
int maxFifa = 0;
static uint64_t maxFifaIteration = 0;
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
int rank[24] = {
    /*tur*/ 1505 - 1374,
    /*ita*/ 1642 - 1374,
    /*wal*/ 1570 - 1374,
    /*sui*/ 1606 - 1374,
    /*den*/ 1631 - 1374,
    /*fin*/ 1410 - 1374,
    /*bel*/ 1783 - 1374,
    /*rus*/ 1462 - 1374,
    /*ned*/ 1598 - 1374,
    /*ukr*/ 1515 - 1374,
    /*aut*/ 1523 - 1374,
    /*mkd*/ 1374 - 1374,
    /*eng*/ 1686 - 1374,
    /*cro*/ 1605 - 1374,
    /*sco*/ 1441 - 1374,
    /*cze*/ 1458 - 1374,
    /*esp*/ 1648 - 1374,
    /*swe*/ 1569 - 1374,
    /*pol*/ 1549 - 1374,
    /*svk*/ 1475 - 1374,
    /*hun*/ 1468 - 1374,
    /*por*/ 1666 - 1374,
    /*fra*/ 1757 - 1374,
    /*ger*/ 1609 - 1374};
enum e_grp {
  _0123,
  _0132,
  _0213,
  _0231,
  _0312,
  _0321,
  _1023,
  _1032,
  _1203,
  _1230,
  _1302,
  _1320,
  _2013,
  _2031,
  _2103,
  _2130,
  _2301,
  _2310,
  _3012,
  _3021,
  _3102,
  _3120,
  _3201,
  _3210
};
char names[24][4];
void elaborateNames();
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
#ifdef GRUND6
  const unsigned win = table >> 4;
  const unsigned secnd = (table & 0xC) >> 2;
  const unsigned third = table & 0x3;
#else
  unsigned win;
  unsigned secnd;
  unsigned third;
  switch (table) {
  case _0123:
    win = 0;
    secnd = 1;
    third = 2;
    break;
  case _0132:
    win = 0;
    secnd = 1;
    third = 3;
    break;
  case _0213:
    win = 0;
    secnd = 2;
    third = 1;
    break;
  case _0231:
    win = 0;
    secnd = 2;
    third = 3;
    break;
  case _0312:
    win = 0;
    secnd = 3;
    third = 1;
    break;
  case _0321:
    win = 0;
    secnd = 3;
    third = 2;
    break;
  case _1023:
    win = 1;
    secnd = 0;
    third = 2;
    break;
  case _1032:
    win = 1;
    secnd = 0;
    third = 3;
    break;
  case _1203:
    win = 1;
    secnd = 2;
    third = 0;
    break;
  case _1230:
    win = 1;
    secnd = 2;
    third = 3;
    break;
  case _1302:
    win = 1;
    secnd = 3;
    third = 0;
    break;
  case _1320:
    win = 1;
    secnd = 3;
    third = 2;
    break;
  case _2013:
    win = 2;
    secnd = 0;
    third = 1;
    break;
  case _2031:
    win = 2;
    secnd = 0;
    third = 3;
    break;
  case _2103:
    win = 2;
    secnd = 1;
    third = 0;
    break;
  case _2130:
    win = 2;
    secnd = 1;
    third = 3;
    break;
  case _2301:
    win = 2;
    secnd = 3;
    third = 0;
    break;
  case _2310:
    win = 2;
    secnd = 3;
    third = 1;
    break;
  case _3012:
    win = 3;
    secnd = 0;
    third = 1;
    break;
  case _3021:
    win = 3;
    secnd = 0;
    third = 2;
    break;
  case _3102:
    win = 3;
    secnd = 1;
    third = 0;
    break;
  case _3120:
    win = 3;
    secnd = 1;
    third = 2;
    break;
  case _3201:
    win = 3;
    secnd = 2;
    third = 0;
    break;
  case _3210:
    win = 3;
    secnd = 2;
    third = 1;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    ;
    abort();
  }
  assert(0 <= win && win <= 3);
  assert(0 <= secnd && secnd <= 3);
  assert(0 <= third && third <= 3);
  assert(win != secnd);
  assert(win != third);
  assert(secnd != third);
#endif
  std::cout << static_cast<e_team>(win + offset) << ','
            << static_cast<e_team>(secnd + offset) << ','
            << static_cast<e_team>(third + offset) << ' ';
  switch (grp) {
  case 'A':
    game[37][0] = static_cast<e_team>(win + offset);
    game[38][0] = static_cast<e_team>(secnd + offset);
    break;
  case 'B':
    game[39][0] = static_cast<e_team>(win + offset);
    game[38][1] = static_cast<e_team>(secnd + offset);
    break;
  case 'C':
    game[40][0] = static_cast<e_team>(win + offset);
    game[37][1] = static_cast<e_team>(secnd + offset);
    break;
  case 'D':
    game[44][0] = static_cast<e_team>(win + offset);
    game[42][0] = static_cast<e_team>(secnd + offset);
    break;
  case 'E':
    game[43][0] = static_cast<e_team>(win + offset);
    game[42][1] = static_cast<e_team>(secnd + offset);
    break;
  case 'F':
    game[41][0] = static_cast<e_team>(win + offset);
    game[44][1] = static_cast<e_team>(secnd + offset);
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
#ifdef GRUND6
  const unsigned win = table >> 4;
  const unsigned secnd = (table & 0xC) >> 2;
#else
  unsigned win;
  unsigned secnd;
  switch (table) {
  case _0123:
  case _0132:
    win = 0;
    secnd = 1;
    break;
  case _0213:
  case _0231:
    win = 0;
    secnd = 2;
    break;
  case _0312:
  case _0321:
    win = 0;
    secnd = 3;
    break;
  case _1023:
  case _1032:
    win = 1;
    secnd = 0;
    break;
  case _1203:
  case _1230:
    win = 1;
    secnd = 2;
    break;
  case _1302:
  case _1320:
    win = 1;
    secnd = 3;
    break;
  case _2013:
  case _2031:
    win = 2;
    secnd = 0;
    break;
  case _2103:
  case _2130:
    win = 2;
    secnd = 1;
    break;
  case _2301:
  case _2310:
    win = 2;
    secnd = 3;
    break;
  case _3012:
  case _3021:
    win = 3;
    secnd = 0;
    break;
  case _3102:
  case _3120:
    win = 3;
    secnd = 1;
    break;
  case _3201:
  case _3210:
    win = 3;
    secnd = 2;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  assert(0 <= win && win <= 3);
  assert(0 <= secnd && secnd <= 3);
  assert(win != secnd);
#endif
  const auto teamWin = static_cast<e_team>(win + offset);
  const auto team2nd = static_cast<e_team>(secnd + offset);
  totFifa += rank[teamWin];
  totFifa += (rank[team2nd] * 60) / 100;
  unsigned saabOffset = 0;
  switch (grp) {
  case 'A':
    game[37][0] = teamWin;
    game[38][0] = team2nd;
    saabOffset = 0;
    break;
  case 'B':
    game[39][0] = teamWin;
    game[38][1] = team2nd;
    saabOffset = 1;
    break;
  case 'C':
    game[40][0] = teamWin;
    game[37][1] = team2nd;
    saabOffset = 2;
    break;
  case 'D':
    game[44][0] = teamWin;
    game[42][0] = team2nd;
    saabOffset = 3;
    break;
  case 'E':
    game[43][0] = teamWin;
    game[42][1] = team2nd;
    saabOffset = 4;
    break;
  case 'F':
    game[41][0] = teamWin;
    game[44][1] = team2nd;
    saabOffset = 5;
    break;
  default:
    cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  for (auto &saabare : saab) {
    if (static_cast<e_team>(win + offset) ==
        saabare.grupp_placering[saabOffset][0]) {
      saabare.poang += 10;
    } else if (static_cast<e_team>(win + offset) ==
               saabare.grupp_placering[saabOffset][1]) {
      saabare.poang += 7;
    }
    if (static_cast<e_team>(secnd + offset) ==
        saabare.grupp_placering[saabOffset][1]) {
      saabare.poang += 10;
    } else if (static_cast<e_team>(secnd + offset) ==
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
#ifdef GRUND6
  const unsigned thirdA = tableA & 0x3;
  const unsigned thirdB = tableB & 0x3;
  const unsigned thirdC = tableC & 0x3;
  const unsigned thirdD = tableD & 0x3;
  const unsigned thirdE = tableE & 0x3;
  const unsigned thirdF = tableF & 0x3;
#else
  unsigned thirdA;
  unsigned thirdB;
  unsigned thirdC;
  unsigned thirdD;
  unsigned thirdE;
  unsigned thirdF;
  switch (tableA) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdA = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdA = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdA = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdA = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableB) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdB = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdB = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdB = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdB = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableC) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdC = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdC = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdC = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdC = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableD) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdD = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdD = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdD = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdD = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableE) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdE = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdE = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdE = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdE = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableF) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdF = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdF = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdF = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdF = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
#endif
  const auto teamA = static_cast<e_team>(thirdA + 0);
  const auto teamB = static_cast<e_team>(thirdB + 4);
  const auto teamC = static_cast<e_team>(thirdC + 8);
  const auto teamD = static_cast<e_team>(thirdD + 12);
  const auto teamE = static_cast<e_team>(thirdE + 16);
  const auto teamF = static_cast<e_team>(thirdF + 20);
  switch (tabell) {
  case 0:
    std::cout << "ABCD--";
    // 3A 3D 3B 3C
    game[39][1] = teamA;
    game[40][1] = teamD;
    game[43][1] = teamB;
    game[41][1] = teamC;
    break;
  case 1:
    std::cout << "ABC-E-";
    // 3A 3E 3B 3C
    game[39][1] = teamA;
    game[40][1] = teamE;
    game[43][1] = teamB;
    game[41][1] = teamC;
    break;
  case 2:
    std::cout << "ABC--F";
    // 3A 3F 3B 3C
    game[39][1] = teamA;
    game[40][1] = teamF;
    game[43][1] = teamB;
    game[41][1] = teamC;
    break;
  case 3:
    std::cout << "AB-DE-";
    // 3D 3E 3A 3B
    game[39][1] = teamD;
    game[40][1] = teamE;
    game[43][1] = teamA;
    game[41][1] = teamB;
    break;
  case 4:
    std::cout << "AB-D-F";
    // 3D 3F 3A 3B
    game[39][1] = teamD;
    game[40][1] = teamF;
    game[43][1] = teamA;
    game[41][1] = teamB;
    break;
  case 5:
    std::cout << "AB--EF";
    // 3E 3F 3B 3A
    game[39][1] = teamE;
    game[40][1] = teamF;
    game[43][1] = teamB;
    game[41][1] = teamA;
    break;
  case 6:
    std::cout << "A-CDE-";
    // 3E 3D 3C 3A
    game[39][1] = teamE;
    game[40][1] = teamD;
    game[43][1] = teamC;
    game[41][1] = teamA;
    break;
  case 7:
    std::cout << "A-CD-F";
    // 3F 3D 3C 3A
    game[39][1] = teamF;
    game[40][1] = teamD;
    game[43][1] = teamC;
    game[41][1] = teamA;
    break;
  case 8:
    std::cout << "A-C-EF";
    // 3E 3F 3C 3A
    game[39][1] = teamE;
    game[40][1] = teamF;
    game[43][1] = teamC;
    game[41][1] = teamA;
    break;
  case 9:
    std::cout << "A--DEF";
    // 3E 3F 3D 3A
    game[39][1] = teamE;
    game[40][1] = teamF;
    game[43][1] = teamD;
    game[41][1] = teamA;
    break;
  case 10:
    std::cout << "-BCDE-";
    // 3E 3D 3B 3C
    game[39][1] = teamE;
    game[40][1] = teamD;
    game[43][1] = teamB;
    game[41][1] = teamC;
    break;
  case 11:
    std::cout << "-BCD-F";
    // 3F 3D 3C 3B
    game[39][1] = teamF;
    game[40][1] = teamD;
    game[43][1] = teamC;
    game[41][1] = teamB;
    break;
  case 12:
    std::cout << "-BC-EF";
    // 3F 3E 3C 3B
    game[39][1] = teamF;
    game[40][1] = teamE;
    game[43][1] = teamC;
    game[41][1] = teamB;
    break;
  case 13:
    std::cout << "-B-DEF";
    // 3F 3E 3D 3B
    game[39][1] = teamF;
    game[40][1] = teamE;
    game[43][1] = teamD;
    game[41][1] = teamB;
    break;
  case 14:
    std::cout << "--CDEF";
    // 3F 3E 3D 3C
    game[39][1] = teamF;
    game[40][1] = teamE;
    game[43][1] = teamD;
    game[41][1] = teamC;
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
#ifdef GRUND6
  const unsigned thirdA = tableA & 0x3;
  const unsigned thirdB = tableB & 0x3;
  const unsigned thirdC = tableC & 0x3;
  const unsigned thirdD = tableD & 0x3;
  const unsigned thirdE = tableE & 0x3;
  const unsigned thirdF = tableF & 0x3;
#else
  unsigned thirdA;
  unsigned thirdB;
  unsigned thirdC;
  unsigned thirdD;
  unsigned thirdE;
  unsigned thirdF;
  switch (tableA) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdA = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdA = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdA = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdA = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableB) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdB = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdB = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdB = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdB = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableC) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdC = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdC = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdC = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdC = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableD) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdD = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdD = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdD = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdD = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableE) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdE = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdE = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdE = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdE = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  switch (tableF) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdF = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdF = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdF = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdF = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
#endif
  const auto teamA = static_cast<e_team>(thirdA + 0);
  const auto teamB = static_cast<e_team>(thirdB + 4);
  const auto teamC = static_cast<e_team>(thirdC + 8);
  const auto teamD = static_cast<e_team>(thirdD + 12);
  const auto teamE = static_cast<e_team>(thirdE + 16);
  const auto teamF = static_cast<e_team>(thirdF + 20);
  switch (tabell) {
  case 0:
    // 3A 3D 3B 3C
    game[39][1] = teamA;
    game[40][1] = teamD;
    game[43][1] = teamB;
    game[41][1] = teamC;
    totFifa += (rank[teamA] * 20) / 100;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
    break;
  case 1:
    // 3A 3E 3B 3C
    game[39][1] = teamA;
    game[40][1] = teamE;
    game[43][1] = teamB;
    game[41][1] = teamC;
    totFifa += (rank[teamA] * 20) / 100;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
    break;
  case 2:
    // 3A 3F 3B 3C
    game[39][1] = teamA;
    game[40][1] = teamF;
    game[43][1] = teamB;
    game[41][1] = teamC;
    totFifa += (rank[teamA] * 20) / 100;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
    break;
  case 3:
    // 3D 3E 3A 3B
    game[39][1] = teamD;
    game[40][1] = teamE;
    game[43][1] = teamA;
    game[41][1] = teamB;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamA] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    break;
  case 4:
    // 3D 3F 3A 3B
    game[39][1] = teamD;
    game[40][1] = teamF;
    game[43][1] = teamA;
    game[41][1] = teamB;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamA] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    break;
  case 5:
    // 3E 3F 3B 3A
    game[39][1] = teamE;
    game[40][1] = teamF;
    game[43][1] = teamB;
    game[41][1] = teamA;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    totFifa += (rank[teamA] * 20) / 100;
    break;
  case 6:
    // 3E 3D 3C 3A
    game[39][1] = teamE;
    game[40][1] = teamD;
    game[43][1] = teamC;
    game[41][1] = teamA;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
    totFifa += (rank[teamA] * 20) / 100;
    break;
  case 7:
    // 3F 3D 3C 3A
    game[39][1] = teamF;
    game[40][1] = teamD;
    game[43][1] = teamC;
    game[41][1] = teamA;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
    totFifa += (rank[teamA] * 20) / 100;
    break;
  case 8:
    // 3E 3F 3C 3A
    game[39][1] = teamE;
    game[40][1] = teamF;
    game[43][1] = teamC;
    game[41][1] = teamA;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
    totFifa += (rank[teamA] * 20) / 100;
    break;
  case 9:
    // 3E 3F 3D 3A
    game[39][1] = teamE;
    game[40][1] = teamF;
    game[43][1] = teamD;
    game[41][1] = teamA;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamA] * 20) / 100;
    break;
  case 10:
    // 3E 3D 3B 3C
    game[39][1] = teamE;
    game[40][1] = teamD;
    game[43][1] = teamB;
    game[41][1] = teamC;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
    break;
  case 11:
    // 3F 3D 3C 3B
    game[39][1] = teamF;
    game[40][1] = teamD;
    game[43][1] = teamC;
    game[41][1] = teamB;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    break;
  case 12:
    // 3F 3E 3C 3B
    game[39][1] = teamF;
    game[40][1] = teamE;
    game[43][1] = teamC;
    game[41][1] = teamB;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    break;
  case 13:
    // 3F 3E 3D 3B
    game[39][1] = teamF;
    game[40][1] = teamE;
    game[43][1] = teamD;
    game[41][1] = teamB;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamB] * 20) / 100;
    break;
  case 14:
    // 3F 3E 3D 3C
    game[39][1] = teamF;
    game[40][1] = teamE;
    game[43][1] = teamD;
    game[41][1] = teamC;
    totFifa += (rank[teamF] * 20) / 100;
    totFifa += (rank[teamE] * 20) / 100;
    totFifa += (rank[teamD] * 20) / 100;
    totFifa += (rank[teamC] * 20) / 100;
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
  elaborateNames();
  uint64_t offsetStride = 0;
  gsl::span<char *> span_argv(argv, argc);
  if (argc > 1) {
    parseArgs(argc, span_argv, &completeFactor, &offsetStride, &ettPrimtal);
  }
  for (uint64_t iteration = offsetStride; iteration < upperlimit;
       iteration += (ettPrimtal * completeFactor)) {
    // Group A
#ifdef GRUND6
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
#else
    if ((iteration & 0x000000000000003F) >= 24UL) {
      continue;
    }
#endif
    // Group B
#ifdef GRUND6
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
#else
    if (((iteration & 0x0000000000000FC0) >> 6) >= 24) {
      continue;
    }
#endif
    // Group C
#ifdef GRUND6
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
#else
    if (((iteration & 0x000000000003F000) >> 12) >= 24) {
      continue;
    }
#endif
    // Group D
#ifdef GRUND6
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
#else
    if (((iteration & 0x0000000000FC0000) >> 18) >= 24) {
      continue;
    }
#endif
    // Group E
#ifdef GRUND6
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
#else
    if (((iteration & 0x000000003F000000) >> 24) >= 24) {
      continue;
    }
#endif
    // Group F
#ifdef GRUND6
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
#else
    if (((iteration & 0x0000000FC0000000) >> 30) >= 24) {
      continue;
    }
#endif
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
    totFifa = 0;
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
    e_team matchWinner;
    result = ((iteration >> (37 + 3)) & 0x1);
    matchWinner = game[37][result];
    game[46][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (38 + 3)) & 0x1);
    matchWinner = game[38][result];
    game[47][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (39 + 3)) & 0x1);
    matchWinner = game[39][result];
    game[46][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (40 + 3)) & 0x1);
    matchWinner = game[40][result];
    game[47][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (41 + 3)) & 0x1);
    matchWinner = game[41][result];
    game[45][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (42 + 3)) & 0x1);
    matchWinner = game[42][result];
    game[45][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (43 + 3)) & 0x1);
    matchWinner = game[43][result];
    game[48][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (44 + 3)) & 0x1);
    matchWinner = game[44][result];
    game[48][1] = matchWinner;
    totFifa += rank[matchWinner];
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
    matchWinner = game[45][result];
    game[49][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (46 + 3)) & 0x1);
    matchWinner = game[46][result];
    game[49][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (47 + 3)) & 0x1);
    matchWinner = game[47][result];
    game[50][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (48 + 3)) & 0x1);
    matchWinner = game[48][result];
    game[50][0] = matchWinner;
    totFifa += rank[matchWinner];
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
    matchWinner = game[49][result];
    game[51][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (50 + 3)) & 0x1);
    matchWinner = game[50][result];
    game[51][1] = matchWinner;
    totFifa += rank[matchWinner];
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
    matchWinner = game[51][result];
    game[52][0] = matchWinner;
    totFifa += rank[matchWinner];
    if (game[52][0] == saab[0].vinnare[0]) {
      saab[0].poang += 50;
    }
    if (totFifa > maxFifa) {
      maxFifa = totFifa;
      maxFifaIteration = iteration;
#define FIFARANK
#ifdef FIFARANK
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
      std::cout << ' ' << maxFifa;
      std::cout << '\n';
#endif
    }
    if (maxSoFar < saab[0].poang) {
      // Utskrift när max ökas
      maxSoFar = saab[0].poang;
      maxIteration = iteration;
    }
  }
  {
    // Utskrift på slutet:
#ifdef FIFARANK
    maxIteration = maxFifaIteration;
#endif
    const uint64_t tableA = maxIteration & 0x3FUL;
    const uint64_t tableB = (maxIteration >> 6) & 0x3FUL;
    const uint64_t tableC = (maxIteration >> 12) & 0x3FUL;
    const uint64_t tableD = (maxIteration >> 18) & 0x3FUL;
    const uint64_t tableE = (maxIteration >> 24) & 0x3FUL;
    const uint64_t tableF = (maxIteration >> 30) & 0x3FUL;
    const uint64_t thirdTable = (maxIteration >> 36) & 0xFUL;
    // Skriv ut
    std::cout << __FILE__ << __LINE__ << ' ' << span_argv[1] << ' ' << offsetStride << ' ';
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
    // Avgör match 37 till 44, fyll i match 45 till 48
    uint64_t result;
    result = ((maxIteration >> (37 + 3)) & 0x1);
    game[46][1] = game[37][result];
    result = ((maxIteration >> (38 + 3)) & 0x1);
    game[47][1] = game[38][result];
    result = ((maxIteration >> (39 + 3)) & 0x1);
    game[46][0] = game[39][result];
    result = ((maxIteration >> (40 + 3)) & 0x1);
    game[47][0] = game[40][result];
    result = ((maxIteration >> (41 + 3)) & 0x1);
    game[45][0] = game[41][result];
    result = ((maxIteration >> (42 + 3)) & 0x1);
    game[45][1] = game[42][result];
    result = ((maxIteration >> (43 + 3)) & 0x1);
    game[48][0] = game[43][result];
    result = ((maxIteration >> (44 + 3)) & 0x1);
    game[48][1] = game[44][result];
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
    // Avgör match 45 till 48, fyll i match 49 och 50
    result = ((maxIteration >> (45 + 3)) & 0x1);
    game[49][1] = game[45][result];
    result = ((maxIteration >> (46 + 3)) & 0x1);
    game[49][0] = game[46][result];
    result = ((maxIteration >> (47 + 3)) & 0x1);
    game[50][1] = game[47][result];
    result = ((maxIteration >> (48 + 3)) & 0x1);
    game[50][0] = game[48][result];
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
    // Avgör match 49 och 50
    result = ((maxIteration >> (49 + 3)) & 0x1);
    game[51][0] = game[49][result];
    result = ((maxIteration >> (50 + 3)) & 0x1);
    game[51][1] = game[50][result];
    for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
      const e_team tt = game[51][hemmaBorta];
      std::cout << tt;
      if (hemmaBorta != 1) {
        std::cout << ',';
      } else {
        std::cout << ' ';
      }
    }
    // Avgör finalen, match 51
    result = ((maxIteration >> (51 + 3)) & 0x1);
    game[52][0] = game[51][result];
    std::cout << game[52][0];
#ifdef FIFARANK
    std::cout << ' ' << maxFifa;
#else
    std::cout << ' ' << maxSoFar;
#endif
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
void parseArgs(int argc, gsl::span<char *> span_argv, uint64_t *completeFactor,
               uint64_t *offsetStride, uint64_t *ettPrimtal) {
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
  *offsetStride = static_cast<uint64_t>(lstrtol);
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
    *ettPrimtal = static_cast<uint64_t>(lstrtol);
  }
  if (argc > 3) {
    // 2 teams group A follows
    char *const arg3 = span_argv[3];
    char *const arg4 = span_argv[4];
    const e_team winA = strcmp("tur", arg3) == 0
                            ? tur
                            : strcmp("ita", arg3) == 0
                                  ? ita
                                  : strcmp("wal", arg3) == 0
                                        ? wal
                                        : strcmp("sui", arg3) == 0
                                              ? sui
                                              : static_cast<e_team>(-1);
    const e_team scndA = strcmp("tur", arg4) == 0
                             ? tur
                             : strcmp("ita", arg4) == 0
                                   ? ita
                                   : strcmp("wal", arg4) == 0
                                         ? wal
                                         : strcmp("sui", arg4) == 0
                                               ? sui
                                               : static_cast<e_team>(-1);
    e_team rd3A = (winA != tur && scndA != tur)
                      ? tur
                      : (winA != ita && scndA != ita) ? ita : wal;
    assert(winA != (e_team)-1);
    assert(scndA != (e_team)-1);
    assert(rd3A != (e_team)-1);
    assert(winA != scndA);
    assert(winA != rd3A);
    assert(scndA != rd3A);
    uint64_t tableA =
        ((winA - 0UL) << 4) + ((scndA - 0UL) << 2) + ((rd3A - 0UL) << 0);
    if (argc > 5) {
      // Group B win,2nd,3rd
      char *const arg5 = span_argv[5];
      char *const arg6 = span_argv[6];
      const e_team winB = strcmp("den", arg5) == 0
                              ? den
                              : strcmp("fin", arg5) == 0
                                    ? fin
                                    : strcmp("bel", arg5) == 0
                                          ? bel
                                          : strcmp("rus", arg5) == 0
                                                ? rus
                                                : static_cast<e_team>(-1);
      const e_team scndB = strcmp("den", arg6) == 0
                               ? den
                               : strcmp("fin", arg6) == 0
                                     ? fin
                                     : strcmp("bel", arg6) == 0
                                           ? bel
                                           : strcmp("rus", arg6) == 0
                                                 ? rus
                                                 : static_cast<e_team>(-1);
      e_team rd3B = (winB != den && scndB != den)
                        ? den
                        : (winB != fin && scndB != fin) ? fin : bel;
      assert(winB != (e_team)-1);
      assert(scndB != (e_team)-1);
      assert(rd3B != (e_team)-1);
      assert(winB != scndB);
      assert(winB != rd3B);
      assert(scndB != rd3B);
      uint64_t tableB =
          ((winB - 4UL) << 10) + ((scndB - 4UL) << 8) + ((rd3B - 4UL) << 6);
      if (argc > 7) {
        // Group C win,2nd,3rd
        char *const arg7 = span_argv[7];
        char *const arg8 = span_argv[8];
        const e_team winC = strcmp("ned", arg7) == 0
                                ? ned
                                : strcmp("ukr", arg7) == 0
                                      ? ukr
                                      : strcmp("aut", arg7) == 0
                                            ? aut
                                            : strcmp("mkd", arg7) == 0
                                                  ? mkd
                                                  : static_cast<e_team>(-1);
        const e_team scndC = strcmp("ned", arg8) == 0
                                 ? ned
                                 : strcmp("ukr", arg8) == 0
                                       ? ukr
                                       : strcmp("aut", arg8) == 0
                                             ? aut
                                             : strcmp("mkd", arg8) == 0
                                                   ? mkd
                                                   : static_cast<e_team>(-1);
        e_team rd3C = (winC != ned && scndC != ned)
                          ? ned
                          : (winC != ukr && scndC != ukr) ? ukr : aut;
        assert(winC != (e_team)-1);
        assert(scndC != (e_team)-1);
        assert(rd3C != (e_team)-1);
        assert(winC != scndC);
        assert(winC != rd3C);
        assert(scndC != rd3C);
        uint64_t tableC =
            ((winC - 8UL) << 16) + ((scndC - 8UL) << 14) + ((rd3C - 8UL) << 12);
        if (argc > 9) {
          // Group D win,2nd,3rd
          char *const arg9 = span_argv[9];
          char *const arg10 = span_argv[10];
          const e_team winD = strcmp("eng", arg9) == 0
                                  ? eng
                                  : strcmp("cro", arg9) == 0
                                        ? cro
                                        : strcmp("sco", arg9) == 0
                                              ? sco
                                              : strcmp("cze", arg9) == 0
                                                    ? cze
                                                    : static_cast<e_team>(-1);
          const e_team scndD = strcmp("eng", arg10) == 0
                                   ? eng
                                   : strcmp("cro", arg10) == 0
                                         ? cro
                                         : strcmp("sco", arg10) == 0
                                               ? sco
                                               : strcmp("cze", arg10) == 0
                                                     ? cze
                                                     : static_cast<e_team>(-1);
          e_team rd3D = (winD != eng && scndD != eng)
                            ? eng
                            : (winD != cro && scndD != cro) ? cro : cze;
          assert(winD != (e_team)-1);
          assert(scndD != (e_team)-1);
          assert(rd3D != (e_team)-1);
          assert(winD != scndD);
          assert(winD != rd3D);
          assert(scndD != rd3D);
          uint64_t tableD = ((winD - 12UL) << 22) + ((scndD - 12UL) << 20) +
                            ((rd3D - 12UL) << 18);
          if (argc > 11) {
            // Group E win,2nd,3rd
            char *const arg11 = span_argv[11];
            char *const arg12 = span_argv[12];
            const e_team winE = strcmp("esp", arg11) == 0
                                    ? esp
                                    : strcmp("swe", arg11) == 0
                                          ? swe
                                          : strcmp("pol", arg11) == 0
                                                ? pol
                                                : strcmp("svk", arg11) == 0
                                                      ? svk
                                                      : static_cast<e_team>(-1);
            const e_team scndE =
                strcmp("esp", arg12) == 0
                    ? esp
                    : strcmp("swe", arg12) == 0
                          ? swe
                          : strcmp("pol", arg12) == 0
                                ? pol
                                : strcmp("svk", arg12) == 0
                                      ? svk
                                      : static_cast<e_team>(-1);
            e_team rd3E = (winE != esp && scndE != esp)
                              ? esp
                              : (winE != swe && scndE != swe) ? swe : pol;
            assert(winE != (e_team)-1);
            assert(scndE != (e_team)-1);
            assert(rd3E != (e_team)-1);
            assert(winE != scndE);
            assert(winE != rd3E);
            assert(scndE != rd3E);
            uint64_t tableE = ((winE - 16UL) << 28) + ((scndE - 16UL) << 26) +
                              ((rd3E - 16UL) << 24);
            if (argc > 13) {
              // Group F win,2nd
              char *const arg13 = span_argv[13];
              char *const arg14 = span_argv[14];
              const e_team winF =
                  strcmp("hun", arg13) == 0
                      ? hun
                      : strcmp("por", arg13) == 0
                            ? por
                            : strcmp("fra", arg13) == 0
                                  ? fra
                                  : strcmp("ger", arg13) == 0
                                        ? ger
                                        : static_cast<e_team>(-1);
              const e_team scndF =
                  strcmp("hun", arg14) == 0
                      ? hun
                      : strcmp("por", arg14) == 0
                            ? por
                            : strcmp("fra", arg14) == 0
                                  ? fra
                                  : strcmp("ger", arg14) == 0
                                        ? ger
                                        : static_cast<e_team>(-1);
              e_team rd3F = (winF != hun && scndF != hun)
                                ? hun
                                : (winF != por && scndF != por) ? por : fra;
              assert(winF != (e_team)-1);
              assert(scndF != (e_team)-1);
              assert(rd3F != (e_team)-1);
              assert(winF != scndF);
              assert(winF != rd3F);
              assert(scndF != rd3F);
              uint64_t tableF = ((winF - 20UL) << 34) + ((scndF - 20UL) << 32) +
                                ((rd3F - 20UL) << 30);
              uint64_t rd3bits = 0; // 4 bits describing the ABCD..CDEF
              // 4 av 6 grupptreor går vidare
              char *const arg15 = span_argv[15];
              char *const arg16 = span_argv[16];
              char *const arg17 = span_argv[17];
              char *const arg18 = span_argv[18];
              e_team team15;
              e_team team16;
              e_team team17;
              e_team team18;
              for (team15 = tur; team15 < static_cast<e_team>(24); ++team15) {
                if (strcmp(names[team15], arg15) == 0) {
                  break;
                }
              }
              assert(strcmp(names[team15], arg15) == 0);
              for (team16 = tur; team16 < static_cast<e_team>(24); ++team16) {
                if (strcmp(names[team16], arg16) == 0) {
                  break;
                }
              }
              assert(strcmp(names[team16], arg16) == 0);
              for (team17 = tur; team17 < static_cast<e_team>(24); ++team17) {
                if (strcmp(names[team17], arg17) == 0) {
                  break;
                }
              }
              assert(strcmp(names[team17], arg17) == 0);
              for (team18 = tur; team18 < static_cast<e_team>(24); ++team18) {
                if (strcmp(names[team18], arg18) == 0) {
                  break;
                }
              }
              assert(strcmp(names[team18], arg18) == 0);
              assert(team15 != team16);
              assert(team15 != team17);
              assert(team15 != team18);
              assert(team16 != team17);
              assert(team16 != team18);
              assert(team17 != team18);
              // Kolla att de är från varsin grupp
              unsigned trunk15 = static_cast<unsigned>(team15) / 4U;
              unsigned trunk16 = static_cast<unsigned>(team16) / 4U;
              unsigned trunk17 = static_cast<unsigned>(team17) / 4U;
              unsigned trunk18 = static_cast<unsigned>(team18) / 4U;
              assert(trunk15 != trunk16);
              assert(trunk15 != trunk17);
              assert(trunk15 != trunk18);
              assert(trunk16 != trunk17);
              assert(trunk16 != trunk18);
              assert(trunk17 != trunk18);
              assert(trunk15 < trunk16);
              assert(trunk16 < trunk17);
              assert(trunk17 < trunk18);
              switch (trunk15) {
              case 0: // A?????
                rd3A = team15;
                assert(winA != rd3A);
                assert(scndA != rd3A);
                switch (trunk16) {
                case 1: // AB????
                  rd3B = team16;
                  assert(winB != rd3B);
                  assert(scndB != rd3B);
                  switch (trunk17) {
                  case 2: // ABC???
                    rd3C = team17;
                    assert(winC != rd3C);
                    assert(scndC != rd3C);
                    switch (trunk18) {
                    case 3: // ABCD--
                      rd3bits = 0x0UL << 36;
                      rd3D = team18;
                      assert(winD != rd3D);
                      assert(scndD != rd3D);
                      break;
                    case 4: // ABC-E-
                      rd3bits = 0x1UL << 36;
                      rd3E = team18;
                      assert(winE != rd3E);
                      assert(scndE != rd3E);
                      break;
                    case 5: // ABC--F
                      rd3bits = 0x2UL << 36;
                      rd3F = team18;
                      assert(winF != rd3F);
                      assert(scndF != rd3F);
                      break;
                    default:
                      std::cerr << __FILE__ << __LINE__ << '\n';
                      abort();
                    }
                    break;
                  case 3: // AB-D??
                    rd3D = team17;
                    assert(winD != rd3D);
                    assert(scndD != rd3D);
                    switch (trunk18) {
                    case 4: // AB-DE-
                      rd3bits = 0x3UL << 36;
                      rd3E = team18;
                      assert(winE != rd3E);
                      assert(scndE != rd3E);
                      break;
                    case 5: // AB-D-F
                      rd3bits = 0x4UL << 36;
                      rd3F = team18;
                      assert(winF != rd3F);
                      assert(scndF != rd3F);
                      break;
                    default:
                      std::cerr << __FILE__ << __LINE__ << '\n';
                      abort();
                    }
                    break;
                  case 4: // AB--EF
                    rd3bits = 0x5UL << 36;
                    rd3E = team17;
                    assert(winE != rd3E);
                    assert(scndE != rd3E);
                    rd3F = team18;
                    assert(winF != rd3F);
                    assert(scndF != rd3F);
                    break;
                  default:
                    std::cerr << __FILE__ << __LINE__ << '\n';
                    abort();
                  }
                  break;
                case 2: // A-C???
                  rd3C = team16;
                  assert(winC != rd3C);
                  assert(scndC != rd3C);
                  switch (trunk17) {
                  case 3: // A-CD??
                    rd3D = team17;
                    assert(winD != rd3D);
                    assert(scndD != rd3D);
                    switch (trunk18) {
                    case 4: // A-CDE-
                      rd3bits = 0x6UL << 36;
                      rd3E = team18;
                      assert(winE != rd3E);
                      assert(scndE != rd3E);
                      break;
                    case 5: // A-CD-F
                      rd3bits = 0x7UL << 36;
                      rd3F = team18;
                      assert(winF != rd3F);
                      assert(scndF != rd3F);
                      break;
                    default:
                      std::cerr << __FILE__ << __LINE__ << '\n';
                      abort();
                    }
                    break;
                  case 4: // A-C-EF
                    rd3bits = 0x8UL << 36;
                    rd3E = team17;
                    assert(winE != rd3E);
                    assert(scndE != rd3E);
                    rd3F = team18;
                    assert(winF != rd3F);
                    assert(scndF != rd3F);
                    break;
                  default:
                    std::cerr << __FILE__ << __LINE__ << '\n';
                    abort();
                  }
                  break;
                case 3: // A--DEF
                  rd3bits = 0x9UL << 36;
                  rd3D = team16;
                  assert(winD != rd3D);
                  assert(scndD != rd3D);
                  rd3E = team17;
                  assert(winE != rd3E);
                  assert(scndE != rd3E);
                  rd3F = team18;
                  assert(winF != rd3F);
                  assert(scndF != rd3F);
                  break;
                default:
                  std::cerr << __FILE__ << __LINE__ << '\n';
                  abort();
                }
                break;
              case 1: //-B????
                rd3B = team15;
                assert(winB != rd3B);
                assert(scndB != rd3B);
                switch (trunk16) {
                case 2: //-BC???
                  rd3C = team16;
                  assert(winC != rd3C);
                  assert(scndC != rd3C);
                  switch (trunk17) {
                  case 3: //-BCD??
                    rd3D = team17;
                    assert(winD != rd3D);
                    assert(scndD != rd3D);
                    switch (trunk18) {
                    case 4: //-BCDE-
                      rd3bits = 0xAUL << 36;
                      rd3E = team18;
                      assert(winE != rd3E);
                      assert(scndE != rd3E);
                      break;
                    case 5: //-BCD-F
                      rd3bits = 0xBUL << 36;
                      rd3F = team18;
                      assert(winF != rd3F);
                      assert(scndF != rd3F);
                      break;
                    default:
                      std::cerr << __FILE__ << __LINE__ << '\n';
                      abort();
                    }
                    break;
                  case 4: // -BC-EF
                    rd3bits = 0xCUL << 36;
                    rd3E = team17;
                    assert(winE != rd3E);
                    assert(scndE != rd3E);
                    rd3F = team18;
                    assert(winF != rd3F);
                    assert(scndF != rd3F);
                    break;
                  default:
                    std::cerr << __FILE__ << __LINE__ << '\n';
                    abort();
                  }
                  break;
                case 3: // -B-DEF
                  rd3bits = 0xDUL << 36;
                  rd3D = team16;
                  assert(winD != rd3D);
                  assert(scndD != rd3D);
                  rd3E = team17;
                  assert(winE != rd3E);
                  assert(scndE != rd3E);
                  rd3F = team18;
                  assert(winF != rd3F);
                  assert(scndF != rd3F);
                  break;
                default:
                  std::cerr << __FILE__ << __LINE__ << '\n';
                  abort();
                }
                break;
              case 2: // --CDEF
                rd3bits = 0xEUL << 36;
                rd3C = team15;
                assert(winC != rd3C);
                assert(scndC != rd3C);
                rd3D = team16;
                assert(winD != rd3D);
                assert(scndD != rd3D);
                rd3E = team17;
                assert(winE != rd3E);
                assert(scndE != rd3E);
                rd3F = team18;
                assert(winF != rd3F);
                assert(scndF != rd3F);
                break;
              default:
                std::cerr << __FILE__ << __LINE__ << '\n';
                abort();
              }
              // Recalculate the tables due to new 3rd
              tableA = ((winA - 0UL) << 4) + ((scndA - 0UL) << 2) +
                       ((rd3A - 0UL) << 0);
              tableB = ((winB - 4UL) << 10) + ((scndB - 4UL) << 8) +
                       ((rd3B - 4UL) << 6);
              tableC = ((winC - 8UL) << 16) + ((scndC - 8UL) << 14) +
                       ((rd3C - 8UL) << 12);
              tableD = ((winD - 12UL) << 22) + ((scndD - 12UL) << 20) +
                       ((rd3D - 12UL) << 18);
              tableE = ((winE - 16UL) << 28) + ((scndE - 16UL) << 26) +
                       ((rd3E - 16UL) << 24);
              tableF = ((winF - 20UL) << 34) + ((scndF - 20UL) << 32) +
                       ((rd3F - 20UL) << 30);
              *completeFactor = 1UL << 40;
              *offsetStride *= 1UL << 40;
              *offsetStride +=
                  rd3bits + tableF + tableE + tableD + tableC + tableB + tableA;
            } else {
              *completeFactor = 1UL << 30;
              *offsetStride *= 1UL << 30;
              *offsetStride += tableE + tableD + tableC + tableB + tableA;
            }
          } else {
            *completeFactor = 1UL << 24;
            *offsetStride *= 1UL << 24;
            *offsetStride += tableD + tableC + tableB + tableA;
          }
        } else {
          *completeFactor = 1UL << 18;
          *offsetStride *= 1UL << 18;
          *offsetStride += tableC + tableB + tableA;
        }
      } else {
        *completeFactor = 1UL << 12;
        *offsetStride *= 1UL << 12;
        *offsetStride += tableB + tableA;
      }
    } else {
      *completeFactor = 1UL << 6;
      *offsetStride *= 1UL << 6;
      *offsetStride += tableA;
    }
  }
}
void elaborateNames() {
  for (e_team team15 = tur; team15 < static_cast<e_team>(24); ++team15) {
    std::ostringstream stream;
    stream.rdbuf()->pubsetbuf(names[team15], 4);
    stream << team15;
    stream << std::ends << std::flush;
  }
}
