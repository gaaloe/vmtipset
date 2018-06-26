// -*-c++-*-
#ifndef manager_code_h
#define manager_code_h
#include <iostream>
enum e_team {rus, ksa, egy, uru,
             mar, irn, por, esp,
             fra, aus, per, den,
             arg, isl, cro, nga,
             crc, srb, bra, sui,
             ger, mex, swe, kor,
             bel, pan, tun, eng,
             col, jpn, pol, sen};
enum e_person {
  TEST,
  ANSE,
  ANNY,
  HEGR,
  JOMA,
  MXRE,
  PEAL,
  MIBJ,
  GUAS,
  ADER,
  MYSJ,
  STJOEL,
  VIST,
  JASH,
  ADSU,
  STMEBR,
  JAYSU,
  STJORY,
  STJASU,
  HESO,
  ULPE,
  STUFJO,
  STASEK,
  HKDY,
  STJOKX,
  STBXWE,
  STMIBO,
  STWU,
  LILA,
  STANNI,
  STSTAA,
  STKRBU,
  STTHWA,
  HRJO,
  HENO,
  STONY,
  CLWF,
  CKH,
  STANNAN,
  HANO,
  DASH,
  DAGR,
  PESD,
  KJSV,
  PATSI,
  OGLL};
#define SIZE_ROW 32
#define NR_COMBS 339738624L
//It is probably good if JUMP_HASH is a prime number (?). See..
//https://primes.utm.edu/lists/small/10000.txt
#define JUMP_HASH        3L
extern e_team operator++(e_team& that);
extern e_team operator++(e_team& that, int);
extern e_person operator++(e_person& that);
extern e_person operator++(e_person& that, int);
extern std::ostream& operator<<(std::ostream& o, enum e_team);
extern std::ostream& operator<<(std::ostream& o, enum e_person);
extern int whoMatchesBest(const e_team c[SIZE_ROW], e_person dotp[32], int myrank);
extern int personMatch(e_person p, const e_team c[SIZE_ROW], int myrank);
extern const int scoreFromGroups[46];
#endif
