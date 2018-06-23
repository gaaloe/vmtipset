#ifndef manager_code_h
#define manager_code_h
enum e_team {rus, ksa, egy, uru,
             mar, irn, por, esp,
             fra, aus, per, den,
             arg, isl, cro, nga,
             crc, srb, bra, sui,
             ger, mex, swe, kor,
             bel, pan, tun, eng,
             col, jpn, pol, sen};
enum e_person {sthrjo, stanny};
#define SIZE_ROW 31
#define NR_COMBS 880602513408L
#define JUMP_HASH        7919L
extern e_team operator++(e_team& that);
extern e_team operator++(e_team& that, int);
#endif
