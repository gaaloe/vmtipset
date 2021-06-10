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
const uint64_t upperlimit = 1UL << 49;
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
uint64_t tableFromTeam(char grp, e_team win, e_team secnd, e_team third) {
  const int offset =
      grp == 'A'
          ? 0
          : grp == 'B'
                ? 4
                : grp == 'C' ? 8 : grp == 'D' ? 12 : grp == 'E' ? 16 : 20;
  switch (win - offset) {
  case 0:
    switch (secnd - offset) {
    case 1: // 01??
      switch (third - offset) {
      case 2:
        return _0123;
        break;
      case 3:
        return _0132;
        break;
      case 0:
      case 1:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 2: // 02??
      switch (third - offset) {
      case 1:
        return _0213;
        break;
      case 3:
        return _0231;
        break;
      case 0:
      case 2:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 3: // 03??
      switch (third - offset) {
      case 1:
        return _0312;
        break;
      case 2:
        return _0321;
        break;
      case 0:
      case 3:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 0:
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    break;
  case 1:
    switch (secnd - offset) {
    case 0: // 10??
      switch (third - offset) {
      case 2:
        return _1023;
        break;
      case 3:
        return _1032;
        break;
      case 0:
      case 1:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 2: // 12??
      switch (third - offset) {
      case 0:
        return _1203;
        break;
      case 3:
        return _1230;
        break;
      case 1:
      case 2:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 3: // 13??
      switch (third - offset) {
      case 0:
        return _1302;
        break;
      case 2:
        return _1320;
        break;
      case 1:
      case 3:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 1:
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    break;
  case 2:
    switch (secnd - offset) {
    case 0: // 20??
      switch (third - offset) {
      case 1:
        return _2013;
        break;
      case 3:
        return _2031;
        break;
      case 0:
      case 2:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 1: // 21??
      switch (third - offset) {
      case 0:
        return _2103;
        break;
      case 3:
        return _2130;
        break;
      case 1:
      case 2:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 3: // 23??
      switch (third - offset) {
      case 0:
        return _2301;
        break;
      case 1:
        return _2310;
        break;
      case 2:
      case 3:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 2:
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    break;
  case 3:
    switch (secnd - offset) {
    case 0: // 30??
      switch (third - offset) {
      case 1:
        return _3012;
        break;
      case 2:
        return _3021;
        break;
      case 0:
      case 3:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 1: // 31??
      switch (third - offset) {
      case 0:
        return _3102;
        break;
      case 2:
        return _3120;
        break;
      case 1:
      case 3:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 2: // 32??
      switch (third - offset) {
      case 0:
        return _3201;
        break;
      case 1:
        return _3210;
        break;
      case 2:
      case 3:
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 3:
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
}
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
    abort();
  }
  assert(0 <= win && win <= 3);
  assert(0 <= secnd && secnd <= 3);
  assert(0 <= third && third <= 3);
  assert(win != secnd);
  assert(win != third);
  assert(secnd != third);
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
    std::cout.width(13);
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
    std::cout.width(13);
    std::cout << tabell << '\n';
    std::cout.copyfmt(init); // restore default formatting
    abort();
  }
}
int main(int argc, char *argv[]) {
  elaborateNames();
  assert(tableFromTeam('A', tur, ita, wal) == _0123); // En liten unittest
  assert(tableFromTeam('F', ger, fra, por) == _3210);
  uint64_t offsetStride = 0;
  gsl::span<char *> span_argv(argv, argc);
  if (argc > 1) {
    parseArgs(argc, span_argv, &completeFactor, &offsetStride, &ettPrimtal);
  }
  for (uint64_t iteration = offsetStride; iteration < upperlimit;
       iteration += (ettPrimtal * completeFactor)) {
    // Group A
    if ((iteration & 0x000000000000001FUL) >= 24UL) {
      continue;
    }
    // Group B
    if (((iteration & (0x000000000000001FUL << 5)) >> 5) >= 24UL) {
      continue;
    }
    // Group C
    if (((iteration & (0x000000000000001FUL << 10)) >> 10) >= 24UL) {
      continue;
    }
    // Group D
    if (((iteration & (0x000000000000001FUL << 15)) >> 15) >= 24UL) {
      continue;
    }
    // Group E
    if (((iteration & (0x000000000000001FUL << 20)) >> 20) >= 24UL) {
      continue;
    }
    // Group F
    if (((iteration & (0x000000000000001FUL << 25)) >> 25) >= 24UL) {
      continue;
    }
    // One of 15 ways to pick the best 3rd place set:
    // See table on https://en.wikipedia.org/wiki/UEFA_Euro_2020#Knockout_phase
    switch (iteration & (0xFL << 30)) {
    case 0x0UL << 30: // ABCD
    case 0x1UL << 30: // ABC E
    case 0x2UL << 30: // ABC  F
    case 0x3UL << 30: // AB DE
    case 0x4UL << 30: // AB D F
    case 0x5UL << 30: // AB  EF
    case 0x6UL << 30: // A CDE
    case 0x7UL << 30: // A CD F
    case 0x8UL << 30: // A C EF
    case 0x9UL << 30: // A  DEF
    case 0xAUL << 30: //  BCDE
    case 0xBUL << 30: //  BCD F
    case 0xCUL << 30: //  BC EF
    case 0xDUL << 30: //  B DEF
    case 0xEUL << 30: //   CDEF
      break;
    case 0xFUL << 30: // There are 15 alternatives, not 16
      continue;
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      std::ios init(nullptr);
      init.copyfmt(std::cout);
      std::cout << std::hex;
      std::cout.width(13);
      std::cout << (iteration & 0x000000F000000000L) << ' ';
      std::cout << iteration << '\n';
      std::cout.copyfmt(init); // restore default formatting
      abort();
    }
    const uint64_t tableA = iteration & 0x1FUL;
    const uint64_t tableB = (iteration >> 5) & 0x1FUL;
    const uint64_t tableC = (iteration >> 10) & 0x1FUL;
    const uint64_t tableD = (iteration >> 15) & 0x1FUL;
    const uint64_t tableE = (iteration >> 20) & 0x1FUL;
    const uint64_t tableF = (iteration >> 25) & 0x1FUL;
    const uint64_t thirdTable = (iteration >> 30) & 0xFUL;
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
    result = ((iteration >> (37 - 3)) & 0x1);
    matchWinner = game[37][result];
    game[46][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (38 - 3)) & 0x1);
    matchWinner = game[38][result];
    game[47][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (39 - 3)) & 0x1);
    matchWinner = game[39][result];
    game[46][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (40 - 3)) & 0x1);
    matchWinner = game[40][result];
    game[47][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (41 - 3)) & 0x1);
    matchWinner = game[41][result];
    game[45][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (42 - 3)) & 0x1);
    matchWinner = game[42][result];
    game[45][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (43 - 3)) & 0x1);
    matchWinner = game[43][result];
    game[48][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (44 - 3)) & 0x1);
    matchWinner = game[44][result];
    game[48][1] = matchWinner;
    totFifa += rank[matchWinner];
#ifndef NDEBUG
    // Kontrollera att alla fält match 45-48 är olika
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
    result = ((iteration >> (45 - 3)) & 0x1);
    matchWinner = game[45][result];
    game[49][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (46 - 3)) & 0x1);
    matchWinner = game[46][result];
    game[49][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (47 - 3)) & 0x1);
    matchWinner = game[47][result];
    game[50][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (48 - 3)) & 0x1);
    matchWinner = game[48][result];
    game[50][0] = matchWinner;
    totFifa += rank[matchWinner];
#ifndef NDEBUG
    // Kontrollera att alla fält match 49-50 är olika
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
    result = ((iteration >> (49 - 3)) & 0x1);
    matchWinner = game[49][result];
    game[51][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (50 - 3)) & 0x1);
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
    result = ((iteration >> (51 - 3)) & 0x1);
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
      std::cout.width(13);
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
      std::cout << game[52][0]; // Vinnaren!
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
    const uint64_t tableA = maxIteration & 0x1FUL;
    const uint64_t tableB = (maxIteration >> 5) & 0x1FUL;
    const uint64_t tableC = (maxIteration >> 10) & 0x1FUL;
    const uint64_t tableD = (maxIteration >> 15) & 0x1FUL;
    const uint64_t tableE = (maxIteration >> 20) & 0x1FUL;
    const uint64_t tableF = (maxIteration >> 25) & 0x1FUL;
    const uint64_t thirdTable = (maxIteration >> 30) & 0xFUL;
    // Skriv ut
    std::cout << __FILE__ << __LINE__ << ' ' << span_argv[1] << ' '
              << offsetStride << ' ';
    std::ios init(nullptr);
    init.copyfmt(std::cout);
    std::cout << std::hex;
    std::cout.width(13);
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
    result = ((maxIteration >> (37 - 3)) & 0x1);
    game[46][1] = game[37][result];
    result = ((maxIteration >> (38 - 3)) & 0x1);
    game[47][1] = game[38][result];
    result = ((maxIteration >> (39 - 3)) & 0x1);
    game[46][0] = game[39][result];
    result = ((maxIteration >> (40 - 3)) & 0x1);
    game[47][0] = game[40][result];
    result = ((maxIteration >> (41 - 3)) & 0x1);
    game[45][0] = game[41][result];
    result = ((maxIteration >> (42 - 3)) & 0x1);
    game[45][1] = game[42][result];
    result = ((maxIteration >> (43 - 3)) & 0x1);
    game[48][0] = game[43][result];
    result = ((maxIteration >> (44 - 3)) & 0x1);
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
    result = ((maxIteration >> (45 - 3)) & 0x1);
    game[49][1] = game[45][result];
    result = ((maxIteration >> (46 - 3)) & 0x1);
    game[49][0] = game[46][result];
    result = ((maxIteration >> (47 - 3)) & 0x1);
    game[50][1] = game[47][result];
    result = ((maxIteration >> (48 - 3)) & 0x1);
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
    result = ((maxIteration >> (49 - 3)) & 0x1);
    game[51][0] = game[49][result];
    result = ((maxIteration >> (50 - 3)) & 0x1);
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
    result = ((maxIteration >> (51 - 3)) & 0x1);
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
    } else if (endptr == span_argv[2]) {
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
    uint64_t tableA = tableFromTeam('A', winA, scndA, rd3A);
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
      uint64_t tableB = tableFromTeam('B', winB, scndB, rd3B) << 5;
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
        uint64_t tableC = tableFromTeam('C', winC, scndC, rd3C) << 10;
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
          uint64_t tableD = tableFromTeam('D', winD, scndD, rd3D) << 15;
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
            uint64_t tableE = tableFromTeam('E', winE, scndE, rd3E) << 20;
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
                      rd3bits = 0x0UL << 30;
                      rd3D = team18;
                      assert(winD != rd3D);
                      assert(scndD != rd3D);
                      break;
                    case 4: // ABC-E-
                      rd3bits = 0x1UL << 30;
                      rd3E = team18;
                      assert(winE != rd3E);
                      assert(scndE != rd3E);
                      break;
                    case 5: // ABC--F
                      rd3bits = 0x2UL << 30;
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
                      rd3bits = 0x3UL << 30;
                      rd3E = team18;
                      assert(winE != rd3E);
                      assert(scndE != rd3E);
                      break;
                    case 5: // AB-D-F
                      rd3bits = 0x4UL << 30;
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
                    rd3bits = 0x5UL << 30;
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
                      rd3bits = 0x6UL << 30;
                      rd3E = team18;
                      assert(winE != rd3E);
                      assert(scndE != rd3E);
                      break;
                    case 5: // A-CD-F
                      rd3bits = 0x7UL << 30;
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
                    rd3bits = 0x8UL << 30;
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
                  rd3bits = 0x9UL << 30;
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
                      rd3bits = 0xAUL << 30;
                      rd3E = team18;
                      assert(winE != rd3E);
                      assert(scndE != rd3E);
                      break;
                    case 5: //-BCD-F
                      rd3bits = 0xBUL << 30;
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
                    rd3bits = 0xCUL << 30;
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
                  rd3bits = 0xDUL << 30;
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
                rd3bits = 0xEUL << 30;
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
              tableA = tableFromTeam('A', winA, scndA, rd3A);
              tableB = tableFromTeam('B', winB, scndB, rd3B) << 5;
              tableC = tableFromTeam('C', winC, scndC, rd3C) << 10;
              tableD = tableFromTeam('D', winD, scndD, rd3D) << 15;
              tableE = tableFromTeam('E', winE, scndE, rd3E) << 20;
              const uint64_t tableF = tableFromTeam('F', winF, scndF, rd3F)
                                      << 25;
              *completeFactor = 1UL << 40;
              *offsetStride *= 1UL << 40;
              *offsetStride +=
                  rd3bits + tableF + tableE + tableD + tableC + tableB + tableA;
            } else {
              *completeFactor = 1UL << 25;
              *offsetStride *= 1UL << 25;
              *offsetStride += tableE + tableD + tableC + tableB + tableA;
            }
          } else {
            *completeFactor = 1UL << 20;
            *offsetStride *= 1UL << 20;
            *offsetStride += tableD + tableC + tableB + tableA;
          }
        } else {
          *completeFactor = 1UL << 15;
          *offsetStride *= 1UL << 15;
          *offsetStride += tableC + tableB + tableA;
        }
      } else {
        *completeFactor = 1UL << 10;
        *offsetStride *= 1UL << 10;
        *offsetStride += tableB + tableA;
      }
    } else {
      *completeFactor = 1UL << 5;
      *offsetStride *= 1UL << 5;
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
