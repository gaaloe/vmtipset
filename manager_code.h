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
enum e_person {sthrjo, stanny};
#define SIZE_ROW 32
#define NR_COMBS 7044820107264L
//It is probably good if JUMP_HASH is a prime number (?). See..
//https://primes.utm.edu/lists/small/10000.txt
#define JUMP_HASH        64007L
extern e_team operator++(e_team& that);
extern e_team operator++(e_team& that, int);
extern std::ostream& operator<<(std::ostream& o, enum e_team);
extern std::ostream& operator<<(std::ostream& o, enum e_person);
#endif
