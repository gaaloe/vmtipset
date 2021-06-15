#include "allege.h"
#include <algorithm> //std::find_if
#include <cassert>
#include <cinttypes>
#include <cstring>
#define gsl_CONFIG_CONTRACT_VIOLATION_ASSERTS
#include <gsl/gsl-lite.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
using std::cerr;
// g++ -I ~/gsl-lite/include main.cpp
// clang-format -i main.cpp
// ./a.out
//
// Gruppspel, treor, m37..m44
// ./a.out 0 1 tur ita den fin ned ukr eng cro esp swe hun por wal bel aut sco
// tur ita den ned hun cro esp eng
//
// seq -w 0 3 | parallel -u ./a.out {} 524287
// seq -w 0 15 | parallel -u ./a.out {} 16127
// seq -w 0 15 | parallel -u ./a.out {} 16127 tur ita
void parseArgs(int argc, gsl::span<char *> span_argv, uint64_t *completeFactor,
               uint64_t *offsetStride, uint64_t *ettPrimtal);
const uint64_t upperlimit = 1UL << 49;
const uint64_t ettPrimtal_1 = 1UL;
const uint64_t ettPrimtal_16127 = 16127UL;
const uint64_t ettPrimtal_19997 = 19997UL;
const uint64_t ettPrimtal_131071 = 131071UL;
const uint64_t ettPrimtal_524287 = 524287UL;
uint64_t ettPrimtal = ettPrimtal_1;
uint64_t completeFactor = 1UL;
static int maxSoFar = 0;
static uint64_t maxIteration = 0;
int totFifa;
int maxFifa = 0;
static uint64_t maxFifaIteration = 0;
unsigned whosThird(uint64_t tableX);
int rank20procent(int fifaRank) {
  // Really silly that clang-tidy can not shut up sometimes:
  const int _20 = 20;
  const int _100 = 100;
  return (fifaRank * _20) / _100;
}
int rank60procent(int fifaRank) {
  const int _60 = 60;
  const int _100 = 100;
  return (fifaRank * _60) / _100;
}
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
  ger,
  num_teams = 24
};
const int rank[num_teams] = {
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
  _3210,
  group_table_size = 24
};
enum e_gruppTreor {
  ABCD,
  ABCE,
  ABCF,
  ABDE,
  ABDF,
  ABEF,
  ACDE,
  ACDF,
  ACEF,
  ADEF,
  BCDE,
  BCDF,
  BCEF,
  BDEF,
  CDEF,
  treor_size = 15
};
const int shift_5 = 5; // Table B bits position within entire bitfield
const int shift_10 = 10;
const int shift_15 = 15;
const int shift_20 = 20;
const int shift_25 = 25;
const int shift_30 = 30;
const int shift_34 = 34; // Shift of beginning of everything non-group play
const int shift_36 = 36;
const int shift_38 = 38;
const int shift_40 = 40;
const int shift_42 = 42;
const uint64_t mask_1FUL = 0x1FUL; // Five time bit one, for & operator
const uint64_t mask_FUL = 0xFUL;
void groupFand3rd(int argc, gsl::span<char *> span_argv, e_team winA,
                  e_team winB, e_team winC, e_team winD, e_team winE,
                  e_team scndA, e_team scndB, e_team scndC, e_team scndD,
                  e_team scndE, e_team *winF, e_team *scndF, e_team *rd3A,
                  e_team *rd3B, e_team *rd3C, e_team *rd3D, e_team *rd3E,
                  e_team *rd3F, uint64_t *rd3bits, uint64_t *tableA,
                  uint64_t *tableB, uint64_t *tableC, uint64_t *tableD,
                  uint64_t *tableE, uint64_t *tableF);
void setup_45_48(uint64_t iteration);

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
char names[num_teams][4];
void elaborateNames();
// Games are officially numbered from 1 to 51.
enum e_matches {
  m37 = 37,
  m38 = 38,
  m39 = 39,
  m40 = 40,
  m41 = 41,
  m42 = 42,
  m43 = 43,
  m44 = 44,
  m45 = 45,
  m46 = 46,
  m47 = 47,
  m48 = 48,
  m49 = 49,
  m50 = 50,
  finalMatchNumber = 51
};
// Add one unused slot for 0
e_team game[1 + finalMatchNumber][2] = {
    {} /*Winner*/,     {tur, ita} /*1*/,  {wal, sui},       {den, fin},
    {bel, rus},        {ned, ukr},        {aut, mkd},       {eng, cro},
    {sco, cze},        {esp, swe},        {pol, svk},       {hun, por},
    {fra, ger},        {tur, wal},        {ita, sui},       {fin, rus},
    {den, bel},        {ned, aut},        {ukr, mkd},       {cro, cze},
    {eng, sco},        {swe, svk},        {esp, pol},       {hun, fra},
    {por, ger},        {sui, tur},        {ita, wal},       {rus, den},
    {fin, bel},        {mkd, ned},        {ukr, aut},       {cro, sco},
    {cze, eng},        {svk, esp},        {swe, pol},       {por, fra},
    {ger, hun} /*36*/, {} /*1A-2C*/,      {} /*2A-2B*/,     {} /*1B-3ADEF 39*/,
    {} /*1C-3DEF 40*/, {} /*1F-3ABC 41*/, {} /*2D-2E*/,     {} /*1E-3ABCD 43*/,
    {} /*1D-2F, 44*/,  {} /*41-42, 45*/,  {} /*37-39, 46*/, {} /*40-38, 47*/,
    {} /*43-44, 48*/,  {} /*46-45, 49*/,  {} /*48-47, 50*/, {} /*49-50, 51*/
};
struct s_saabare {
  const char *namnkod;
  e_team grupp_placering[6][2];
  e_team kvartsfinallag[8];
  e_team semifinallag[4];
  e_team finallag[2];
  e_team vinnare[1];
  int poang;
} saab[] = {
    {"ANNY",
     {{ita, sui}, {bel, den}, {ned, ukr}, {eng, cro}, {esp, swe}, {fra, ger}},
     {ita, bel, ned, eng, cro, esp, fra, ger},
     {ita, bel, fra, ger},
     {bel, fra},
     {bel},
     0},
    {"ANSE",
     {{ita, sui}, {den, bel}, {ned, ukr}, {eng, cro}, {esp, swe}, {fra, por}},
     {ita, den, bel, eng, esp, fra, por, ger},
     {bel, eng, fra, por},
     {bel, fra},
     {bel},
     0},
    {"STROEL",
     {{ita, sui}, {bel, den}, {ned, aut}, {eng, cro}, {esp, swe}, {fra, ger}},
     {ita, bel, ned, eng, esp, fra, ger, por},
     {bel, fra, eng, ger},
     {fra, bel},
     {fra},
     0},
    {"STJAVE",
     {{ita, tur}, {bel, rus}, {ned, aut}, {eng, cro}, {esp, swe}, {por, ger}},
     {rus, cro, por, ita, ger, esp, bel, fra},
     {por, ger, fra, ita},
     {por, ger},
     {por},
     0},
    {"ADER",
     {{sui, ita}, {bel, rus}, {ned, aut}, {eng, cro}, {esp, pol}, {por, fra}},
     {ita, sui, swe, bel, cro, por, fra, esp},
     {por, bel, swe, esp},
     {por, esp},
     {por},
     0},
    {"STJOEL",
     {{sui, ita}, {bel, rus}, {aut, ned}, {eng, cro}, {esp, pol}, {fra, ger}},
     {ita, ned, por, bel, pol, fra, eng, den},
     {bel, eng, pol, den},
     {eng, bel},
     {eng},
     0},
    {"STHRJO",
     {{sui, ita}, {bel, den}, {ned, ukr}, {cro, eng}, {esp, swe}, {por, ger}},
     {por, eng, bel, sui, fra, ita, esp, ger},
     {bel, eng, ger, fra},
     {bel, fra},
     {bel},
     0},
    {"MXRE",
     {{ita, tur}, {bel, den}, {ned, ukr}, {eng, cze}, {esp, pol}, {ger, fra}},
     {bel, ita, ger, cze, fra, esp, ned, den},
     {ita, ger, /*spa*/ esp, ned},
     {ger, /*spa*/ esp},
     {ger},
     0},
    {"STESEN",
     {{tur, ita}, {bel, fin}, {ukr, ned}, {eng, cze}, {esp, pol}, {fra, por}},
     {bel, fra, esp, ukr, tur, pol, por, swe},
     {tur, fra, por, ukr},
     {fra, por},
     {por},
     0},
    {"JUDU",
     {{ita, sui}, {rus, den}, {ned, aut}, {eng, cro}, {esp, pol}, {ger, por}},
     {ita, bel, ned, eng, esp, ger, por, pol},
     {eng, bel, ger, pol},
     {eng, ger},
     {eng},
     0},
    {"HEGR",
     {{sui, ita}, {den, bel}, {ned, aut}, {eng, cro}, {esp, swe}, {fra, por}},
     {sui, den, ned, eng, esp, swe, fra, por},
     {den, esp, eng, fra},
     {eng, fra},
     {fra},
     0},
    {"ULPE",
     {{ita, tur}, {bel, den}, {ned, aut}, {cro, eng}, {esp, swe}, {fra, por}},
     {bel, ita, fra, eng, /*spa*/ esp, por, ger, tur},
     {bel, fra, por, ger},
     {fra, por},
     {fra},
     0},
    {"STASEK",
     {{ita, tur}, {bel, den}, {ned, aut}, {eng, cro}, {swe, esp}, {ger, por}},
     {ita, bel, ned, eng, swe, esp, ger, por},
     {bel, ger, por, swe},
     {bel, ger},
     {ger},
     0},
    {"GUAS",
     {{ita, sui}, {den, bel}, {ned, aut}, {eng, cro}, {esp, swe}, {ger, por}},
     {bel, ita, ned, den, por, ger, eng, esp},
     {ger, ned, ita, esp},
     {ger, esp},
     {esp},
     0},
    {"STMIBO",
     {{ita, tur}, {bel, rus}, {ned, ukr}, {eng, sco}, {esp, swe}, {ger, por}},
     {bel, ita, ger, swe, esp, eng, ned, rus},
     {bel, ger, eng, ned},
     {bel, eng},
     {eng},
     0},
    {"STLNAL",
     {{ita, sui}, {rus, den}, {ned, aut}, {eng, cro}, {esp, swe}, {ger, fra}},
     {ita, den, ned, eng, ger, fra, bel, cro},
     {ita, cro, ger, fra},
     {ger, fra},
     {fra},
     0},
    {"STMISA",
     {{tur, ita}, {bel, den}, {ned, aut}, {eng, cro}, {esp, swe}, {fra, ger}},
     {tur, bel, ned, cro, esp, fra, ger, swe},
     {ned, ger, fra, cro},
     {ger, fra},
     {fra},
     0},
    {"HANO",
     {{ita, sui}, {bel, den}, {ned, aut}, {eng, cro}, {esp, swe}, {ger, fra}},
     {ita, bel, ned, eng, cro, esp, fra, ger},
     {eng, ned, ger, fra},
     {ger, eng},
     {eng},
     0},
    {"JOMA",
     {{ita, tur}, {bel, rus}, {ned, ukr}, {eng, cro}, {esp, pol}, {fra, ger}},
     {bel, ita, fra, cro, esp, ger, ned, tur},
     {bel, fra, esp, ned},
     {fra, esp},
     {fra},
     0},
    {"SELI",
     {{ita, tur}, {bel, den}, {ned, aut}, {eng, cro}, {esp, swe}, {fra, por}},
     {ita, bel, ned, eng, esp, fra, por, swe},
     {bel, eng, fra, por},
     {eng, fra},
     {fra},
     0},
    {"SINI",
     {{ita, sui}, {bel, rus}, {ned, aut}, {cro, eng}, {esp, swe}, {ger, por}},
     {ita, bel, ned, eng, swe, por, fra, esp},
     {ita, swe, esp, ned},
     {ita, esp},
     {ita},
     0},
    {"STBJJO1",
     {{ita, sui}, {bel, rus}, {ned, ukr}, {eng, cze}, {esp, swe}, {fra, ger}},
     {ita, bel, rus, ned, swe, eng, esp, fra},
     {bel, ned, eng, fra},
     {fra, bel},
     {fra},
     0},
    {"PATSI",
     {{ita, sui}, {bel, den}, {ned, aut}, {eng, cro}, {esp, swe}, {fra, por}},
     {bel, fra, eng, por, esp, ita, den, sui},
     {bel, fra, eng, por},
     {bel, fra},
     {bel},
     0},
    {"STLUL",
     {{ita, sui}, {bel, rus}, {ned, aut}, {eng, cro}, {esp, swe}, {por, ger}},
     {fra, por, bel, eng, ger, swe, den, cro},
     {ger, cro, esp, por},
     {esp, por},
     {esp},
     0},
    {"STPEDAL",
     {{ita, sui}, {bel, den}, {ned, aut}, {eng, cro}, {esp, swe}, {ger, fra}},
     {ita, den, bel, ned, ger, swe, esp, eng},
     {ger, ita, ned, esp},
     {ger, esp},
     {ger},
     0},
    {"ERSK",
     {{ita, sui}, {bel, den}, {ukr, ned}, {eng, cro}, {esp, swe}, {fra, ger}},
     {bel, ita, fra, swe, esp, ger, por, den},
     {bel, fra, ger, por},
     {fra, ger},
     {fra},
     0},
    {"STMYSJ",
     {{ita, sui}, {bel, den}, {ned, ukr}, {eng, cro}, {esp, pol}, {fra, ger}},
     {den, ita, ned, bel, cro, fra, eng, esp},
     {fra, bel, ned, eng},
     {bel, eng},
     {eng},
     0},
    {"STOSGR",
     {{ita, tur}, {bel, den}, {ned, ukr}, {cro, eng}, {esp, swe}, {fra, ger}},
     {por, ger, swe, ita, fra, cro, eng, esp},
     {fra, esp, por, cro},
     {fra, esp},
     {fra},
     0},
    {"STJOFR1",
     {{ita, sui}, {bel, rus}, {ned, aut}, {eng, cro}, {pol, swe}, {fra, por}},
     {sui, ita, ned, ger, swe, fra, eng, den},
     {ita, ned, fra, eng},
     {ned, fra},
     {ned},
     0},
    {"STJASH",
     {{ita, sui}, {bel, den}, {ned, aut}, {eng, cze}, {esp, swe}, {fra, ger}},
     {fra, bel, esp, ita, eng, swe, ger, den},
     {bel, fra, eng, ger},
     {bel, eng},
     {eng},
     0},
    {"STLILA",
     {{ita, tur}, {bel, den}, {ned, ukr}, {eng, cro}, {esp, swe}, {fra, ger}},
     {tur, ita, por, bel, cro, fra, ger, esp},
     {bel, ita, ger, fra},
     {bel, ger},
     {bel},
     0},

};
const int poangGroupWinner = 10;
const int poangGroupSecond = 10;
const int poangSwapWinner = 7;
const int poangSwapSecond = 7;
const int poangKvarts = 15;
const int poangSemi = 25;
const int poangFinal = 35;
const int poangVinnare = 50;
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
  default:
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
  const auto teamWin = static_cast<e_team>(win + offset);
  const auto team2nd = static_cast<e_team>(secnd + offset);
  const auto team3rd = static_cast<e_team>(third + offset);
  std::cout << teamWin << ',' << team2nd << ',' << team3rd << ' ';
  switch (grp) {
  case 'A':
    game[m37][0] = teamWin;
    game[m38][0] = team2nd;
    break;
  case 'B':
    game[m39][0] = teamWin;
    game[m38][1] = team2nd;
    break;
  case 'C':
    game[m40][0] = teamWin;
    game[m37][1] = team2nd;
    break;
  case 'D':
    game[m44][0] = teamWin;
    game[m42][0] = team2nd;
    break;
  case 'E':
    game[m43][0] = teamWin;
    game[m42][1] = team2nd;
    break;
  case 'F':
    game[m41][0] = teamWin;
    game[m44][1] = team2nd;
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
  totFifa += rank60procent(rank[team2nd]);
  unsigned saabOffset = grp - 'A';
  switch (grp) {
  case 'A':
    game[m37][0] = teamWin;
    game[m38][0] = team2nd;
    break;
  case 'B':
    game[m39][0] = teamWin;
    game[m38][1] = team2nd;
    break;
  case 'C':
    game[m40][0] = teamWin;
    game[m37][1] = team2nd;
    break;
  case 'D':
    game[m44][0] = teamWin;
    game[m42][0] = team2nd;
    break;
  case 'E':
    game[m43][0] = teamWin;
    game[m42][1] = team2nd;
    break;
  case 'F':
    game[m41][0] = teamWin;
    game[m44][1] = team2nd;
    break;
  default:
    cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  for (auto &saabare : saab) {
    if (teamWin == saabare.grupp_placering[saabOffset][0]) {
      saabare.poang += poangGroupWinner;
    } else if (teamWin == saabare.grupp_placering[saabOffset][1]) {
      saabare.poang += poangSwapWinner;
    }
    if (team2nd == saabare.grupp_placering[saabOffset][1]) {
      saabare.poang += poangGroupSecond;
    } else if (team2nd == saabare.grupp_placering[saabOffset][0]) {
      saabare.poang += poangSwapSecond;
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
  const unsigned thirdA = whosThird(tableA);
  const unsigned thirdB = whosThird(tableB);
  const unsigned thirdC = whosThird(tableC);
  const unsigned thirdD = whosThird(tableD);
  const unsigned thirdE = whosThird(tableE);
  const unsigned thirdF = whosThird(tableF);
  const auto teamA = static_cast<e_team>(thirdA + 0);
  const auto teamB = static_cast<e_team>(thirdB + 4);
  const auto teamC = static_cast<e_team>(thirdC + 8);
  const auto teamD = static_cast<e_team>(thirdD + 12);
  const auto teamE = static_cast<e_team>(thirdE + 16);
  const auto teamF = static_cast<e_team>(thirdF + 20);
  switch (tabell) {
  case ABCD:
    std::cout << "ABCD--";
    // 3A 3D 3B 3C
    game[m39][1] = teamA;
    game[m40][1] = teamD;
    game[m43][1] = teamB;
    game[m41][1] = teamC;
    break;
  case ABCE:
    std::cout << "ABC-E-";
    // 3A 3E 3B 3C
    game[m39][1] = teamA;
    game[m40][1] = teamE;
    game[m43][1] = teamB;
    game[m41][1] = teamC;
    break;
  case ABCF:
    std::cout << "ABC--F";
    // 3A 3F 3B 3C
    game[m39][1] = teamA;
    game[m40][1] = teamF;
    game[m43][1] = teamB;
    game[m41][1] = teamC;
    break;
  case ABDE:
    std::cout << "AB-DE-";
    // 3D 3E 3A 3B
    game[m39][1] = teamD;
    game[m40][1] = teamE;
    game[m43][1] = teamA;
    game[m41][1] = teamB;
    break;
  case ABDF:
    std::cout << "AB-D-F";
    // 3D 3F 3A 3B
    game[m39][1] = teamD;
    game[m40][1] = teamF;
    game[m43][1] = teamA;
    game[m41][1] = teamB;
    break;
  case ABEF:
    std::cout << "AB--EF";
    // 3E 3F 3B 3A
    game[m39][1] = teamE;
    game[m40][1] = teamF;
    game[m43][1] = teamB;
    game[m41][1] = teamA;
    break;
  case ACDE:
    std::cout << "A-CDE-";
    // 3E 3D 3C 3A
    game[m39][1] = teamE;
    game[m40][1] = teamD;
    game[m43][1] = teamC;
    game[m41][1] = teamA;
    break;
  case ACDF:
    std::cout << "A-CD-F";
    // 3F 3D 3C 3A
    game[m39][1] = teamF;
    game[m40][1] = teamD;
    game[m43][1] = teamC;
    game[m41][1] = teamA;
    break;
  case ACEF:
    std::cout << "A-C-EF";
    // 3E 3F 3C 3A
    game[m39][1] = teamE;
    game[m40][1] = teamF;
    game[m43][1] = teamC;
    game[m41][1] = teamA;
    break;
  case ADEF:
    std::cout << "A--DEF";
    // 3E 3F 3D 3A
    game[m39][1] = teamE;
    game[m40][1] = teamF;
    game[m43][1] = teamD;
    game[m41][1] = teamA;
    break;
  case BCDE:
    std::cout << "-BCDE-";
    // 3E 3D 3B 3C
    game[m39][1] = teamE;
    game[m40][1] = teamD;
    game[m43][1] = teamB;
    game[m41][1] = teamC;
    break;
  case BCDF:
    std::cout << "-BCD-F";
    // 3F 3D 3C 3B
    game[m39][1] = teamF;
    game[m40][1] = teamD;
    game[m43][1] = teamC;
    game[m41][1] = teamB;
    break;
  case BCEF:
    std::cout << "-BC-EF";
    // 3F 3E 3C 3B
    game[m39][1] = teamF;
    game[m40][1] = teamE;
    game[m43][1] = teamC;
    game[m41][1] = teamB;
    break;
  case BDEF:
    std::cout << "-B-DEF";
    // 3F 3E 3D 3B
    game[m39][1] = teamF;
    game[m40][1] = teamE;
    game[m43][1] = teamD;
    game[m41][1] = teamB;
    break;
  case CDEF:
    std::cout << "--CDEF";
    // 3F 3E 3D 3C
    game[m39][1] = teamF;
    game[m40][1] = teamE;
    game[m43][1] = teamD;
    game[m41][1] = teamC;
    break;
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
  const unsigned thirdA = whosThird(tableA);
  const unsigned thirdB = whosThird(tableB);
  const unsigned thirdC = whosThird(tableC);
  const unsigned thirdD = whosThird(tableD);
  const unsigned thirdE = whosThird(tableE);
  const unsigned thirdF = whosThird(tableF);
  const auto teamA = static_cast<e_team>(thirdA + 0);
  const auto teamB = static_cast<e_team>(thirdB + 4);
  const auto teamC = static_cast<e_team>(thirdC + 8);
  const auto teamD = static_cast<e_team>(thirdD + 12);
  const auto teamE = static_cast<e_team>(thirdE + 16);
  const auto teamF = static_cast<e_team>(thirdF + 20);
  switch (tabell) {
  case ABCD:
    // 3A 3D 3B 3C
    game[m39][1] = teamA;
    game[m40][1] = teamD;
    game[m43][1] = teamB;
    game[m41][1] = teamC;
    totFifa += rank20procent(rank[teamA]);
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamB]);
    totFifa += rank20procent(rank[teamC]);
    break;
  case ABCE:
    // 3A 3E 3B 3C
    game[m39][1] = teamA;
    game[m40][1] = teamE;
    game[m43][1] = teamB;
    game[m41][1] = teamC;
    totFifa += rank20procent(rank[teamA]);
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamB]);
    totFifa += rank20procent(rank[teamC]);
    break;
  case ABCF:
    // 3A 3F 3B 3C
    game[m39][1] = teamA;
    game[m40][1] = teamF;
    game[m43][1] = teamB;
    game[m41][1] = teamC;
    totFifa += rank20procent(rank[teamA]);
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamB]);
    totFifa += rank20procent(rank[teamC]);
    break;
  case ABDE:
    // 3D 3E 3A 3B
    game[m39][1] = teamD;
    game[m40][1] = teamE;
    game[m43][1] = teamA;
    game[m41][1] = teamB;
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamA]);
    totFifa += rank20procent(rank[teamB]);
    break;
  case ABDF:
    // 3D 3F 3A 3B
    game[m39][1] = teamD;
    game[m40][1] = teamF;
    game[m43][1] = teamA;
    game[m41][1] = teamB;
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamA]);
    totFifa += rank20procent(rank[teamB]);
    break;
  case ABEF:
    // 3E 3F 3B 3A
    game[m39][1] = teamE;
    game[m40][1] = teamF;
    game[m43][1] = teamB;
    game[m41][1] = teamA;
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamB]);
    totFifa += rank20procent(rank[teamA]);
    break;
  case ACDE:
    // 3E 3D 3C 3A
    game[m39][1] = teamE;
    game[m40][1] = teamD;
    game[m43][1] = teamC;
    game[m41][1] = teamA;
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamC]);
    totFifa += rank20procent(rank[teamA]);
    break;
  case ACDF:
    // 3F 3D 3C 3A
    game[m39][1] = teamF;
    game[m40][1] = teamD;
    game[m43][1] = teamC;
    game[m41][1] = teamA;
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamC]);
    totFifa += rank20procent(rank[teamA]);
    break;
  case ACEF:
    // 3E 3F 3C 3A
    game[m39][1] = teamE;
    game[m40][1] = teamF;
    game[m43][1] = teamC;
    game[m41][1] = teamA;
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamC]);
    totFifa += rank20procent(rank[teamA]);
    break;
  case ADEF:
    // 3E 3F 3D 3A
    game[m39][1] = teamE;
    game[m40][1] = teamF;
    game[m43][1] = teamD;
    game[m41][1] = teamA;
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamA]);
    break;
  case BCDE:
    // 3E 3D 3B 3C
    game[m39][1] = teamE;
    game[m40][1] = teamD;
    game[m43][1] = teamB;
    game[m41][1] = teamC;
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamB]);
    totFifa += rank20procent(rank[teamC]);
    break;
  case BCDF:
    // 3F 3D 3C 3B
    game[m39][1] = teamF;
    game[m40][1] = teamD;
    game[m43][1] = teamC;
    game[m41][1] = teamB;
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamC]);
    totFifa += rank20procent(rank[teamB]);
    break;
  case BCEF:
    // 3F 3E 3C 3B
    game[m39][1] = teamF;
    game[m40][1] = teamE;
    game[m43][1] = teamC;
    game[m41][1] = teamB;
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamC]);
    totFifa += rank20procent(rank[teamB]);
    break;
  case BDEF:
    // 3F 3E 3D 3B
    game[m39][1] = teamF;
    game[m40][1] = teamE;
    game[m43][1] = teamD;
    game[m41][1] = teamB;
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamB]);
    break;
  case CDEF:
    // 3F 3E 3D 3C
    game[m39][1] = teamF;
    game[m40][1] = teamE;
    game[m43][1] = teamD;
    game[m41][1] = teamC;
    totFifa += rank20procent(rank[teamF]);
    totFifa += rank20procent(rank[teamE]);
    totFifa += rank20procent(rank[teamD]);
    totFifa += rank20procent(rank[teamC]);
    break;
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
    if ((iteration & mask_1FUL) >= group_table_size) {
      continue;
    }
    // Group B
    if (((iteration & (mask_1FUL << shift_5)) >> shift_5) >= group_table_size) {
      continue;
    }
    // Group C
    if (((iteration & (mask_1FUL << shift_10)) >> shift_10) >=
        group_table_size) {
      continue;
    }
    // Group D
    if (((iteration & (mask_1FUL << shift_15)) >> shift_15) >=
        group_table_size) {
      continue;
    }
    // Group E
    if (((iteration & (mask_1FUL << shift_20)) >> shift_20) >=
        group_table_size) {
      continue;
    }
    // Group F
    if (((iteration & (mask_1FUL << shift_25)) >> shift_25) >=
        group_table_size) {
      continue;
    }
    // One of 15 ways to pick the best 3rd place set:
    // See table on https://en.wikipedia.org/wiki/UEFA_Euro_2020#Knockout_phase
    if (((iteration & (mask_FUL << shift_30)) >> shift_30) >= treor_size) {
      continue;
    }
    const uint64_t tableA = iteration & mask_1FUL;
    const uint64_t tableB = (iteration >> shift_5) & mask_1FUL;
    const uint64_t tableC = (iteration >> shift_10) & mask_1FUL;
    const uint64_t tableD = (iteration >> shift_15) & mask_1FUL;
    const uint64_t tableE = (iteration >> shift_20) & mask_1FUL;
    const uint64_t tableF = (iteration >> shift_25) & mask_1FUL;
    const uint64_t thirdTable = (iteration >> shift_30) & mask_FUL;
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
    for (int match = m37; match <= m44; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        for (int match2 = m37; match2 <= m44; ++match2) {
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
    setup_45_48(iteration);
    totFifa += rank[game[m46][1]];
    totFifa += rank[game[m47][1]];
    totFifa += rank[game[m46][0]];
    totFifa += rank[game[m47][0]];
    totFifa += rank[game[m45][0]];
    totFifa += rank[game[m45][1]];
    totFifa += rank[game[m48][0]];
    totFifa += rank[game[m48][1]];
#ifndef NDEBUG
    // Kontrollera att alla fält match 45-48 är olika
    for (int match = m45; match <= m48; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        for (int match2 = m45; match2 <= m48; ++match2) {
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
      for (int match = m45; match <= m48; ++match) {
        for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
          const e_team tt = game[match][hemmaBorta];
          const auto *f =
              std::find_if(span_quarts.cbegin(), span_quarts.cend(),
                           [tt](const e_team tm) { return tt == tm; });
          if (f != span_quarts.cend()) {
            saab[0].poang += poangKvarts;
          }
        }
      }
    }
    // Avgör match 45 till 48, fyll i match 49 och 50
    uint64_t result = ((iteration >> (m45 - 3)) & 0x1);
    e_team matchWinner = game[m45][result];
    game[m49][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (m46 - 3)) & 0x1);
    matchWinner = game[m46][result];
    game[m49][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (m47 - 3)) & 0x1);
    matchWinner = game[m47][result];
    game[m50][1] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (m48 - 3)) & 0x1);
    matchWinner = game[m48][result];
    game[m50][0] = matchWinner;
    totFifa += rank[matchWinner];
#ifndef NDEBUG
    // Kontrollera att alla fält match 49-50 är olika
    for (int match = m49; match <= m50; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        for (int match2 = m49; match2 <= m50; ++match2) {
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
      for (int match = m49; match <= m50; ++match) {
        for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
          const e_team tt = game[match][hemmaBorta];
          const auto *f =
              std::find_if(span_semi.cbegin(), span_semi.cend(),
                           [tt](const e_team tm) { return tt == tm; });
          if (f != span_semi.cend()) {
            saab[0].poang += poangSemi;
          }
        }
      }
    }
    // Avgör match 49 och 50
    result = ((iteration >> (m49 - 3)) & 0x1);
    matchWinner = game[m49][result];
    game[finalMatchNumber][0] = matchWinner;
    totFifa += rank[matchWinner];
    result = ((iteration >> (m50 - 3)) & 0x1);
    matchWinner = game[m50][result];
    game[finalMatchNumber][1] = matchWinner;
    totFifa += rank[matchWinner];
    {
      gsl::span<e_team> span_final(saab[0].finallag, 2);
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[finalMatchNumber][hemmaBorta];
        const auto *f =
            std::find_if(span_final.cbegin(), span_final.cend(),
                         [tt](const e_team tm) { return tt == tm; });
        if (f != span_final.cend()) {
          saab[0].poang += poangFinal;
        }
      }
    }
    // Avgör finalen, match 51
    result = ((iteration >> (finalMatchNumber - 3)) & 0x1);
    matchWinner = game[finalMatchNumber][result];
    game[0][0] = matchWinner;
    totFifa += rank[matchWinner];
    if (game[0][0] == saab[0].vinnare[0]) {
      saab[0].poang += poangVinnare;
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
      std::cout << iteration << '\n';
      std::cout.copyfmt(init); // restore default formatting
      showGrundSpel('A', tableA);
      showGrundSpel('B', tableB);
      showGrundSpel('C', tableC);
      showGrundSpel('D', tableD);
      showGrundSpel('E', tableE);
      showGrundSpel('F', tableF);
      std::cout << '\n';
      for (int match = m45; match <= m48; ++match) {
        for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
          const e_team tt = game[match][hemmaBorta];
          std::cout << tt;
          if (match != m48 || hemmaBorta != 1) {
            std::cout << ',';
          } else {
            std::cout << ' ';
          }
        }
      }
      for (int match = m49; match <= m50; ++match) {
        for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
          const e_team tt = game[match][hemmaBorta];
          std::cout << tt;
          if (match != m50 || hemmaBorta != 1) {
            std::cout << ',';
          } else {
            std::cout << ' ';
          }
        }
      }
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[finalMatchNumber][hemmaBorta];
        std::cout << tt;
        if (hemmaBorta != 1) {
          std::cout << ',';
        } else {
          std::cout << ' ';
        }
      }
      std::cout << game[0][0]; // Vinnaren!
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
    const uint64_t tableA = maxIteration & mask_1FUL;
    const uint64_t tableB = (maxIteration >> shift_5) & mask_1FUL;
    const uint64_t tableC = (maxIteration >> shift_10) & mask_1FUL;
    const uint64_t tableD = (maxIteration >> shift_15) & mask_1FUL;
    const uint64_t tableE = (maxIteration >> shift_20) & mask_1FUL;
    const uint64_t tableF = (maxIteration >> shift_25) & mask_1FUL;
    const uint64_t thirdTable = (maxIteration >> shift_30) & mask_FUL;
    // Skriv ut
    std::cout << __FILE__ << __LINE__ << ' ' << span_argv[1] << ' ';
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
    setup_45_48(maxIteration);
    for (int match = m45; match <= m48; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        std::cout << tt;
        if (match != m48 || hemmaBorta != 1) {
          std::cout << ',';
        } else {
          std::cout << ' ';
        }
      }
    }
    // Avgör match 45 till 48, fyll i match 49 och 50
    uint64_t result = ((maxIteration >> (m45 - 3)) & 0x1);
    game[m49][1] = game[m45][result];
    result = ((maxIteration >> (m46 - 3)) & 0x1);
    game[m49][0] = game[m46][result];
    result = ((maxIteration >> (m47 - 3)) & 0x1);
    game[m50][1] = game[m47][result];
    result = ((maxIteration >> (m48 - 3)) & 0x1);
    game[m50][0] = game[m48][result];
    for (int match = m49; match <= m50; ++match) {
      for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
        const e_team tt = game[match][hemmaBorta];
        std::cout << tt;
        if (match != m50 || hemmaBorta != 1) {
          std::cout << ',';
        } else {
          std::cout << ' ';
        }
      }
    }
    // Avgör match 49 och 50
    result = ((maxIteration >> (m49 - 3)) & 0x1);
    game[finalMatchNumber][0] = game[m49][result];
    result = ((maxIteration >> (m50 - 3)) & 0x1);
    game[finalMatchNumber][1] = game[m50][result];
    for (int hemmaBorta = 0; hemmaBorta < 2; ++hemmaBorta) {
      const e_team tt = game[finalMatchNumber][hemmaBorta];
      std::cout << tt;
      if (hemmaBorta != 1) {
        std::cout << ',';
      } else {
        std::cout << ' ';
      }
    }
    // Avgör finalen, match 51
    result = ((maxIteration >> (finalMatchNumber - 3)) & 0x1);
    game[0][0] = game[finalMatchNumber][result];
    std::cout << game[0][0];
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
  const int base = 10;
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
    DEBUG_allege(argc > 4);
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
    DEBUG_allege(winA != (e_team)-1);
    DEBUG_allege(scndA != (e_team)-1);
    DEBUG_allege(rd3A != (e_team)-1);
    DEBUG_allege(winA != scndA);
    DEBUG_allege(winA != rd3A);
    DEBUG_allege(scndA != rd3A);
    uint64_t tableA = tableFromTeam('A', winA, scndA, rd3A);
    if (argc > 5) {
      // Group B win,2nd,3rd
      DEBUG_allege(argc > 6);
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
      DEBUG_allege(winB != (e_team)-1);
      DEBUG_allege(scndB != (e_team)-1);
      DEBUG_allege(rd3B != (e_team)-1);
      DEBUG_allege(winB != scndB);
      DEBUG_allege(winB != rd3B);
      DEBUG_allege(scndB != rd3B);
      uint64_t tableB = tableFromTeam('B', winB, scndB, rd3B) << shift_5;
      if (argc > 7) {
        DEBUG_allege(argc > 8);
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
        DEBUG_allege(winC != (e_team)-1);
        DEBUG_allege(scndC != (e_team)-1);
        DEBUG_allege(rd3C != (e_team)-1);
        DEBUG_allege(winC != scndC);
        DEBUG_allege(winC != rd3C);
        DEBUG_allege(scndC != rd3C);
        uint64_t tableC = tableFromTeam('C', winC, scndC, rd3C) << shift_10;
        if (argc > 9) {
          // Group D win,2nd,3rd
          DEBUG_allege(argc > 10);
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
                            : (winD != cro && scndD != cro) ? cro : sco;
          DEBUG_allege(winD != (e_team)-1);
          DEBUG_allege(scndD != (e_team)-1);
          DEBUG_allege(rd3D != (e_team)-1);
          DEBUG_allege(winD != scndD);
          DEBUG_allege(winD != rd3D);
          DEBUG_allege(scndD != rd3D);
          uint64_t tableD = tableFromTeam('D', winD, scndD, rd3D) << shift_15;
          if (argc > 11) {
            // Group E win,2nd,3rd
            DEBUG_allege(argc > 12);
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
            DEBUG_allege(winE != (e_team)-1);
            DEBUG_allege(scndE != (e_team)-1);
            DEBUG_allege(rd3E != (e_team)-1);
            DEBUG_allege(winE != scndE);
            DEBUG_allege(winE != rd3E);
            DEBUG_allege(scndE != rd3E);
            uint64_t tableE = tableFromTeam('E', winE, scndE, rd3E) << shift_20;
            if (argc > 13) {
              e_team winF;
              e_team scndF;
              e_team rd3F;
              uint64_t tableF;
              uint64_t rd3bits = 0; // 4 bits describing the ABCD..CDEF
              groupFand3rd(argc, span_argv, winA, winB, winC, winD, winE, scndA,
                           scndB, scndC, scndD, scndE, &winF, &scndF, &rd3A,
                           &rd3B, &rd3C, &rd3D, &rd3E, &rd3F, &rd3bits, &tableA,
                           &tableB, &tableC, &tableD, &tableE, &tableF);
              if (argc > 19) {
                DEBUG_allege(argc > 20);
                // Grundspel, tredjeplats, två sextondelsmatcher:
                // m37: Winner Group A eller Runner-up Group C?
                // m38: Runner-up Group A eller Runner-up Group B?
                char *const arg19 = span_argv[19];
                DEBUG_allege((strcmp(names[winA], arg19) == 0) ||
                             (strcmp(names[scndC], arg19) == 0));
                char *const arg20 = span_argv[20];
                DEBUG_allege((strcmp(names[scndA], arg20) == 0) ||
                             (strcmp(names[scndB], arg20) == 0));
                if (argc > 21) {
                  DEBUG_allege(argc > 22);
                  // m39: Winner Group B eller 3rd Group A/D/E/F?
                  // m40: Winner Group C eller 3rd Group D/E/F
                  // OBS att game[m{39,40,41,43}][1] satts av groupFand3rd()
                  // ovan
                  char *const arg21 = span_argv[21];
                  DEBUG_allege((strcmp(names[winB], arg21) == 0) ||
                               (strcmp(names[game[m39][1]], arg21) == 0));
                  char *const arg22 = span_argv[22];
                  DEBUG_allege((strcmp(names[winC], arg22) == 0) ||
                               (strcmp(names[game[m40][1]], arg22) == 0));
                  if (argc > 23) {
                    // m41: Winner Group F eller 3rd Group A/B/C
                    // m42: Runner-up Group D eller Runner-up Group E
                    DEBUG_allege(argc > 24);
                    char *const arg23 = span_argv[23];
                    DEBUG_allege((strcmp(names[winF], arg23) == 0) ||
                                 (strcmp(names[game[m41][1]], arg23) == 0));
                    char *const arg24 = span_argv[24];
                    DEBUG_allege((strcmp(names[scndD], arg24) == 0) ||
                                 (strcmp(names[scndE], arg24) == 0));
                    if (argc > 25) {
                      DEBUG_allege(argc > 26);
                      // m43: Winner Group E eller 3rd Group A/B/C/D
                      // m44: Winner Group D eller Runner-up Group F
                      char *const arg25 = span_argv[25];
                      DEBUG_allege((strcmp(names[winE], arg25) == 0) ||
                                   (strcmp(names[game[m43][1]], arg25) == 0));
                      char *const arg26 = span_argv[26];
                      DEBUG_allege((strcmp(names[winD], arg26) == 0) ||
                                   (strcmp(names[scndF], arg26) == 0));
                      if (argc > 27) {
                        DEBUG_allege(argc > 28);
                        // TODO(henrik) fortsätt här
                      } else {
                        *completeFactor = 1UL << shift_42;
                        *offsetStride *= 1UL << shift_42;
                        if (strcmp(names[scndC], arg19) == 0) {
                          *offsetStride += 1UL << shift_34;
                        }
                        if (strcmp(names[scndB], arg20) == 0) {
                          *offsetStride += 1UL << (shift_34 + 1);
                        }
                        if (strcmp(names[game[m39][1]], arg21) == 0) {
                          *offsetStride += 1UL << shift_36;
                        }
                        if (strcmp(names[game[m40][1]], arg22) == 0) {
                          *offsetStride += 1UL << (shift_36 + 1);
                        }
                        if (strcmp(names[game[m41][1]], arg23) == 0) {
                          *offsetStride += 1UL << shift_38;
                        }
                        if (strcmp(names[scndE], arg24) == 0) {
                          *offsetStride += 1UL << (shift_38 + 1);
                        }
                        if (strcmp(names[game[m43][1]], arg25) == 0) {
                          *offsetStride += 1UL << shift_40;
                        }
                        if (strcmp(names[scndF], arg26) == 0) {
                          *offsetStride += 1UL << (shift_40 + 1);
                        }
                        *offsetStride += rd3bits + tableF + tableE + tableD +
                                         tableC + tableB + tableA;
                      }
                    } else {
                      *completeFactor = 1UL << shift_40;
                      *offsetStride *= 1UL << shift_40;
                      if (strcmp(names[scndC], arg19) == 0) {
                        *offsetStride += 1UL << shift_34;
                      }
                      if (strcmp(names[scndB], arg20) == 0) {
                        *offsetStride += 1UL << (shift_34 + 1);
                      }
                      if (strcmp(names[game[m39][1]], arg21) == 0) {
                        *offsetStride += 1UL << shift_36;
                      }
                      if (strcmp(names[game[m40][1]], arg22) == 0) {
                        *offsetStride += 1UL << (shift_36 + 1);
                      }
                      if (strcmp(names[game[m41][1]], arg23) == 0) {
                        *offsetStride += 1UL << shift_38;
                      }
                      if (strcmp(names[scndE], arg24) == 0) {
                        *offsetStride += 1UL << (shift_38 + 1);
                      }
                      *offsetStride += rd3bits + tableF + tableE + tableD +
                                       tableC + tableB + tableA;
                    }
                  } else {
                    *completeFactor = 1UL << shift_38;
                    *offsetStride *= 1UL << shift_38;
                    if (strcmp(names[scndC], arg19) == 0) {
                      *offsetStride += 1UL << shift_34;
                    }
                    if (strcmp(names[scndB], arg20) == 0) {
                      *offsetStride += 1UL << (shift_34 + 1);
                    }
                    if (strcmp(names[game[m39][1]], arg21) == 0) {
                      *offsetStride += 1UL << shift_36;
                    }
                    if (strcmp(names[game[m40][1]], arg22) == 0) {
                      *offsetStride += 1UL << (shift_36 + 1);
                    }
                    *offsetStride += rd3bits + tableF + tableE + tableD +
                                     tableC + tableB + tableA;
                  }
                } else {
                  *completeFactor = 1UL << shift_36;
                  *offsetStride *= 1UL << shift_36;
                  if (strcmp(names[scndC], arg19) == 0) {
                    *offsetStride += 1UL << shift_34;
                  }
                  if (strcmp(names[scndB], arg20) == 0) {
                    *offsetStride += 1UL << (shift_34 + 1);
                  }
                  *offsetStride += rd3bits + tableF + tableE + tableD + tableC +
                                   tableB + tableA;
                }
              } else {
                *completeFactor = 1UL << shift_34;
                *offsetStride *= 1UL << shift_34;
                *offsetStride += rd3bits + tableF + tableE + tableD + tableC +
                                 tableB + tableA;
              }
            } else {
              *completeFactor = 1UL << shift_25;
              *offsetStride *= 1UL << shift_25;
              *offsetStride += tableE + tableD + tableC + tableB + tableA;
            }
          } else {
            *completeFactor = 1UL << shift_20;
            *offsetStride *= 1UL << shift_20;
            *offsetStride += tableD + tableC + tableB + tableA;
          }
        } else {
          *completeFactor = 1UL << shift_15;
          *offsetStride *= 1UL << shift_15;
          *offsetStride += tableC + tableB + tableA;
        }
      } else {
        *completeFactor = 1UL << shift_10;
        *offsetStride *= 1UL << shift_10;
        *offsetStride += tableB + tableA;
      }
    } else {
      *completeFactor = 1UL << shift_5;
      *offsetStride *= 1UL << shift_5;
      *offsetStride += tableA;
    }
  }
}
void elaborateNames() {
  for (e_team teamX = tur; teamX < num_teams; ++teamX) {
    std::ostringstream stream;
    stream.rdbuf()->pubsetbuf(names[teamX], 4);
    stream << teamX;
    stream << std::ends << std::flush;
  }
}
unsigned whosThird(uint64_t tableX) {
  unsigned thirdX;
  switch (tableX) {
  case _1203:
  case _1302:
  case _2103:
  case _2301:
  case _3102:
  case _3201:
    thirdX = 0;
    break;
  case _0213:
  case _0312:
  case _2013:
  case _2310:
  case _3012:
  case _3210:
    thirdX = 1;
    break;
  case _0123:
  case _0321:
  case _1320:
  case _1023:
  case _3021:
  case _3120:
    thirdX = 2;
    break;
  case _0132:
  case _0231:
  case _1032:
  case _1230:
  case _2031:
  case _2130:
    thirdX = 3;
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  return thirdX;
}
void groupFand3rd(int argc, gsl::span<char *> span_argv, e_team winA,
                  e_team winB, e_team winC, e_team winD, e_team winE,
                  e_team scndA, e_team scndB, e_team scndC, e_team scndD,
                  e_team scndE, e_team *winF, e_team *scndF, e_team *rd3A,
                  e_team *rd3B, e_team *rd3C, e_team *rd3D, e_team *rd3E,
                  e_team *rd3F, uint64_t *rd3bits, uint64_t *tableA,
                  uint64_t *tableB, uint64_t *tableC, uint64_t *tableD,
                  uint64_t *tableE, uint64_t *tableF) {
  // Group F win,2nd
  DEBUG_allege(argc > 18);
  char *const arg13 = span_argv[13];
  char *const arg14 = span_argv[14];
  *winF = strcmp("hun", arg13) == 0
              ? hun
              : strcmp("por", arg13) == 0
                    ? por
                    : strcmp("fra", arg13) == 0
                          ? fra
                          : strcmp("ger", arg13) == 0 ? ger
                                                      : static_cast<e_team>(-1);
  *scndF = strcmp("hun", arg14) == 0
               ? hun
               : strcmp("por", arg14) == 0
                     ? por
                     : strcmp("fra", arg14) == 0
                           ? fra
                           : strcmp("ger", arg14) == 0
                                 ? ger
                                 : static_cast<e_team>(-1);
  *rd3F = (*winF != hun && *scndF != hun)
              ? hun
              : (*winF != por && *scndF != por) ? por : fra;
  DEBUG_allege(*winF != (e_team)-1);
  DEBUG_allege(*scndF != (e_team)-1);
  DEBUG_allege(*rd3F != (e_team)-1);
  DEBUG_allege(*winF != *scndF);
  DEBUG_allege(*winF != *rd3F);
  DEBUG_allege(*scndF != *rd3F);
  // 4 av 6 grupptreor går vidare
  char *const arg15 = span_argv[15];
  char *const arg16 = span_argv[16];
  char *const arg17 = span_argv[17];
  char *const arg18 = span_argv[18];
  e_team team15;
  e_team team16;
  e_team team17;
  e_team team18;
  for (team15 = tur; team15 < num_teams; ++team15) {
    if (strcmp(names[team15], arg15) == 0) {
      break;
    }
  }
  DEBUG_allege(strcmp(names[team15], arg15) == 0);
  for (team16 = tur; team16 < num_teams; ++team16) {
    if (strcmp(names[team16], arg16) == 0) {
      break;
    }
  }
  DEBUG_allege(strcmp(names[team16], arg16) == 0);
  for (team17 = tur; team17 < num_teams; ++team17) {
    if (strcmp(names[team17], arg17) == 0) {
      break;
    }
  }
  DEBUG_allege(strcmp(names[team17], arg17) == 0);
  for (team18 = tur; team18 < num_teams; ++team18) {
    if (strcmp(names[team18], arg18) == 0) {
      break;
    }
  }
  DEBUG_allege(strcmp(names[team18], arg18) == 0);
  DEBUG_allege(team15 != team16);
  DEBUG_allege(team15 != team17);
  DEBUG_allege(team15 != team18);
  DEBUG_allege(team16 != team17);
  DEBUG_allege(team16 != team18);
  DEBUG_allege(team17 != team18);
  // Kolla att de är från varsin grupp
  unsigned trunk15 = static_cast<unsigned>(team15) / 4U;
  unsigned trunk16 = static_cast<unsigned>(team16) / 4U;
  unsigned trunk17 = static_cast<unsigned>(team17) / 4U;
  unsigned trunk18 = static_cast<unsigned>(team18) / 4U;
  DEBUG_allege(trunk15 != trunk16);
  DEBUG_allege(trunk15 != trunk17);
  DEBUG_allege(trunk15 != trunk18);
  DEBUG_allege(trunk16 != trunk17);
  DEBUG_allege(trunk16 != trunk18);
  DEBUG_allege(trunk17 != trunk18);
  DEBUG_allege(trunk15 < trunk16);
  DEBUG_allege(trunk16 < trunk17);
  DEBUG_allege(trunk17 < trunk18);
  switch (static_cast<char>(trunk15) + 'A') {
  case 'A': // A?????
    *rd3A = team15;
    DEBUG_allege(winA != *rd3A);
    DEBUG_allege(scndA != *rd3A);
    switch (static_cast<char>(trunk16) + 'A') {
    case 'B': // AB????
      *rd3B = team16;
      DEBUG_allege(winB != *rd3B);
      DEBUG_allege(scndB != *rd3B);
      switch (static_cast<char>(trunk17) + 'A') {
      case 'C': // ABC???
        *rd3C = team17;
        DEBUG_allege(winC != *rd3C);
        DEBUG_allege(scndC != *rd3C);
        switch (static_cast<char>(trunk18) + 'A') {
        case 'D': // ABCD--
          *rd3bits = static_cast<uint64_t>(ABCD) << shift_30;
          *rd3D = team18;
          DEBUG_allege(winD != *rd3D);
          DEBUG_allege(scndD != *rd3D);
          break;
        case 'E': // ABC-E-
          *rd3bits = static_cast<uint64_t>(ABCE) << shift_30;
          *rd3E = team18;
          DEBUG_allege(winE != *rd3E);
          DEBUG_allege(scndE != *rd3E);
          break;
        case 'F': // ABC--F
          *rd3bits = static_cast<uint64_t>(ABCF) << shift_30;
          *rd3F = team18;
          DEBUG_allege(*winF != *rd3F);
          DEBUG_allege(*scndF != *rd3F);
          break;
        default:
          std::cerr << __FILE__ << __LINE__ << '\n';
          abort();
        }
        break;
      case 'D': // AB-D??
        *rd3D = team17;
        DEBUG_allege(winD != *rd3D);
        DEBUG_allege(scndD != *rd3D);
        switch (static_cast<char>(trunk18) + 'A') {
        case 'E': // AB-DE-
          *rd3bits = static_cast<uint64_t>(ABDE) << shift_30;
          *rd3E = team18;
          DEBUG_allege(winE != *rd3E);
          DEBUG_allege(scndE != *rd3E);
          break;
        case 'F': // AB-D-F
          *rd3bits = static_cast<uint64_t>(ABDF) << shift_30;
          *rd3F = team18;
          DEBUG_allege(*winF != *rd3F);
          DEBUG_allege(*scndF != *rd3F);
          break;
        default:
          std::cerr << __FILE__ << __LINE__ << '\n';
          abort();
        }
        break;
      case 'E': // AB--EF
        *rd3bits = static_cast<uint64_t>(ABEF) << shift_30;
        *rd3E = team17;
        DEBUG_allege(winE != *rd3E);
        DEBUG_allege(scndE != *rd3E);
        *rd3F = team18;
        DEBUG_allege(*winF != *rd3F);
        DEBUG_allege(*scndF != *rd3F);
        break;
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 'C': // A-C???
      *rd3C = team16;
      DEBUG_allege(winC != *rd3C);
      DEBUG_allege(scndC != *rd3C);
      switch (static_cast<char>(trunk17) + 'A') {
      case 'D': // A-CD??
        *rd3D = team17;
        DEBUG_allege(winD != *rd3D);
        DEBUG_allege(scndD != *rd3D);
        switch (static_cast<char>(trunk18) + 'A') {
        case 'E': // A-CDE-
          *rd3bits = static_cast<uint64_t>(ACDE) << shift_30;
          *rd3E = team18;
          DEBUG_allege(winE != *rd3E);
          DEBUG_allege(scndE != *rd3E);
          break;
        case 'F': // A-CD-F
          *rd3bits = static_cast<uint64_t>(ACDF) << shift_30;
          *rd3F = team18;
          DEBUG_allege(*winF != *rd3F);
          DEBUG_allege(*scndF != *rd3F);
          break;
        default:
          std::cerr << __FILE__ << __LINE__ << '\n';
          abort();
        }
        break;
      case 'E': // A-C-EF
        *rd3bits = static_cast<uint64_t>(ACEF) << shift_30;
        *rd3E = team17;
        DEBUG_allege(winE != *rd3E);
        DEBUG_allege(scndE != *rd3E);
        *rd3F = team18;
        DEBUG_allege(*winF != *rd3F);
        DEBUG_allege(*scndF != *rd3F);
        break;
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 'D': // A--DEF
      *rd3bits = static_cast<uint64_t>(ADEF) << shift_30;
      *rd3D = team16;
      DEBUG_allege(winD != *rd3D);
      DEBUG_allege(scndD != *rd3D);
      *rd3E = team17;
      DEBUG_allege(winE != *rd3E);
      DEBUG_allege(scndE != *rd3E);
      *rd3F = team18;
      DEBUG_allege(*winF != *rd3F);
      DEBUG_allege(*scndF != *rd3F);
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    break;
  case 'B': //-B????
    *rd3B = team15;
    DEBUG_allege(winB != *rd3B);
    DEBUG_allege(scndB != *rd3B);
    switch (static_cast<char>(trunk16) + 'A') {
    case 'C': //-BC???
      *rd3C = team16;
      DEBUG_allege(winC != *rd3C);
      DEBUG_allege(scndC != *rd3C);
      switch (static_cast<char>(trunk17) + 'A') {
      case 'D': //-BCD??
        *rd3D = team17;
        DEBUG_allege(winD != *rd3D);
        DEBUG_allege(scndD != *rd3D);
        switch (static_cast<char>(trunk18) + 'A') {
        case 'E': //-BCDE-
          *rd3bits = static_cast<uint64_t>(BCDE) << shift_30;
          *rd3E = team18;
          DEBUG_allege(winE != *rd3E);
          DEBUG_allege(scndE != *rd3E);
          break;
        case 'F': //-BCD-F
          *rd3bits = static_cast<uint64_t>(BCDF) << shift_30;
          *rd3F = team18;
          DEBUG_allege(*winF != *rd3F);
          DEBUG_allege(*scndF != *rd3F);
          break;
        default:
          std::cerr << __FILE__ << __LINE__ << '\n';
          abort();
        }
        break;
      case 'E': // -BC-EF
        *rd3bits = static_cast<uint64_t>(BCEF) << shift_30;
        *rd3E = team17;
        DEBUG_allege(winE != *rd3E);
        DEBUG_allege(scndE != *rd3E);
        *rd3F = team18;
        DEBUG_allege(*winF != *rd3F);
        DEBUG_allege(*scndF != *rd3F);
        break;
      default:
        std::cerr << __FILE__ << __LINE__ << '\n';
        abort();
      }
      break;
    case 'D': // -B-DEF
      *rd3bits = static_cast<uint64_t>(BDEF) << shift_30;
      *rd3D = team16;
      DEBUG_allege(winD != *rd3D);
      DEBUG_allege(scndD != *rd3D);
      *rd3E = team17;
      DEBUG_allege(winE != *rd3E);
      DEBUG_allege(scndE != *rd3E);
      *rd3F = team18;
      DEBUG_allege(*winF != *rd3F);
      DEBUG_allege(*scndF != *rd3F);
      break;
    default:
      std::cerr << __FILE__ << __LINE__ << '\n';
      abort();
    }
    break;
  case 'C': // --CDEF
    *rd3bits = static_cast<uint64_t>(CDEF) << shift_30;
    *rd3C = team15;
    DEBUG_allege(winC != *rd3C);
    DEBUG_allege(scndC != *rd3C);
    *rd3D = team16;
    DEBUG_allege(winD != *rd3D);
    DEBUG_allege(scndD != *rd3D);
    *rd3E = team17;
    DEBUG_allege(winE != *rd3E);
    DEBUG_allege(scndE != *rd3E);
    *rd3F = team18;
    DEBUG_allege(*winF != *rd3F);
    DEBUG_allege(*scndF != *rd3F);
    break;
  default:
    std::cerr << __FILE__ << __LINE__ << '\n';
    abort();
  }
  // Recalculate the tables due to new 3rd
  *tableA = tableFromTeam('A', winA, scndA, *rd3A);
  *tableB = tableFromTeam('B', winB, scndB, *rd3B) << shift_5;
  *tableC = tableFromTeam('C', winC, scndC, *rd3C) << shift_10;
  *tableD = tableFromTeam('D', winD, scndD, *rd3D) << shift_15;
  *tableE = tableFromTeam('E', winE, scndE, *rd3E) << shift_20;
  *tableF = tableFromTeam('F', *winF, *scndF, *rd3F) << shift_25;
}
void setup_45_48(uint64_t iteration) {
  uint64_t result;
  result = ((iteration >> (m37 - 3)) & 0x1);
  game[m46][1] = game[m37][result];
  result = ((iteration >> (m38 - 3)) & 0x1);
  game[m47][1] = game[m38][result];
  result = ((iteration >> (m39 - 3)) & 0x1);
  game[m46][0] = game[m39][result];
  result = ((iteration >> (m40 - 3)) & 0x1);
  game[m47][0] = game[m40][result];
  result = ((iteration >> (m41 - 3)) & 0x1);
  game[m45][0] = game[m41][result];
  result = ((iteration >> (m42 - 3)) & 0x1);
  game[m45][1] = game[m42][result];
  result = ((iteration >> (m43 - 3)) & 0x1);
  game[m48][0] = game[m43][result];
  result = ((iteration >> (m44 - 3)) & 0x1);
  game[m48][1] = game[m44][result];
}
