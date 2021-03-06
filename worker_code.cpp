#include <mpi.h>
#include <cassert>
#include <algorithm>    // std::sort()
#include "manager_code.h"
// Redan ute: ksa, egy, mar, per, crc, kor, tun, pan, pol
enum e_team EXCEL[46][32] = {
  /*TEST*/
  {rus, ksa, mar, irn, fra, aus, arg, isl, crc, srb, ger, mex, bel, pan, col, jpn,
   rus, mar, fra, arg, crc, ger, bel, col,
   rus, mar, crc, ger,
   rus, crc,
   mar,
   rus}
  /*ANSE*/,
  {rus, uru, esp, por, fra, den, arg, cro, bra, sui, ger, swe, bel, eng, pol, col,
   por, esp, fra, arg, bra, ger, bel, eng,
   fra, esp, bra, ger,
   bra, ger,
   fra,
   bra}
  /*ANNY*/,
  {rus, egy, esp, por, fra, den, arg, cro, bra, sui, ger, kor, bel, eng, col, sen,
   por, esp, fra, arg, bra, ger, bel, eng,
   fra, arg, bel, ger,
   bel, ger,
   arg,
   bel}
  /*HEGR*/,
  {egy, uru, por, esp, fra, den, arg, isl, sui, bra, ger, mex, bel, eng, col, pol,
   uru, por, fra, arg, bra, ger, bel, eng,
   fra, arg, bra, bel,
   arg, bel,
   fra,
   arg}
  /*JOMA*/,
  {uru, rus, esp, por, fra, per, arg, cro, bra, sui, ger, mex, bel, eng, col, pol,
   esp, uru, fra, arg, bra, ger, bel, eng,
   esp, fra, bra, ger,
   ger, bra,
   fra,
   ger}
  /*MXRE*/,
  {uru, rus, esp, por, fra, den, arg, cro, bra, sui, ger, mex, eng, bel, pol, col,
   por, esp, fra, arg, bra, ger, eng, bel,
   fra, esp, bra, ger,
   bra, ger,
   fra,
   bra}
  /*PEAL*/,
  {rus, uru, esp, por, fra, per, cro, arg, bra, srb, ger, mex, eng, bel, pol, col,
   rus, esp, arg, cro, bra, ger, eng, pol,
   arg, cro, eng, ger,
   eng, ger,
   cro,
   ger}
  /*MIBJ*/,
  {egy, rus, esp, por, fra, den, cro, arg, bra, srb, ger, swe, bel, eng, col, sen,
   por, esp, fra, cro, bra, ger, bel, col,
   por, fra, bra, col,
   fra, bra,
   col,
   bra}
  /*GUAS*/,
  {uru, rus, esp, por, fra, per, arg, cro, sui, bra, ger, mex, bel, eng, pol, col,
   esp, por, arg, fra, ger, bra, pol, bel,
   arg, esp, ger, pol,
   ger, esp,
   arg,
   ger}
  /*ADER*/,
  {uru, rus, esp, por, fra, den, arg, cro, bra, sui, ger, swe, bel, eng, col, pol,
   por, rus, cro, arg, swe, ger, bel, eng,
   por, arg, ger, swe,
   arg, ger,
   swe,
   arg}
  /*MYSJ*/,
  {uru, rus, esp, por, fra, den, arg, cro, bra, sui, ger, mex, bel, eng, col, pol,
   por, esp, fra, arg, bra, ger, bel, eng,
   fra, esp, bra, ger,
   bra, ger,
   esp,
   ger}
  /*STJOEL*/,
  {uru, rus, esp, por, fra, den, arg, nga, bra, sui, ger, mex, eng, bel, pol, col,
   uru, esp, fra, arg, bra, ger, eng, col,
   fra, arg, bra, ger,
   arg, ger,
   fra,
   arg}
  /*VIST*/,
  {uru, rus, por, esp, fra, per, arg, isl, bra, sui, ger, swe, bel, eng, col, pol,
   esp, por, arg, fra, bra, ger, bel, eng,
   arg, fra, bra, ger,
   ger, arg,
   fra,
   ger}
  /*JASH*/,
  {rus, egy, por, esp, fra, den, isl, arg, bra, srb, ger, swe, eng, bel, col, jpn,
   por, esp, fra, isl, ger, bra, eng, bel,
   por, esp, ger, bra,
   ger, por,
   bra,
   ger}
  /*ADSU*/,
  {rus, uru, por, esp, fra, aus, arg, cro, bra, crc, ger, swe, bel, eng, col, pol,
   rus, por, fra, aus, bra, ger, bel, pol,
   fra, por, ger, pol,
   por, ger,
   fra,
   por}
  /*STMEBR*/,
  {egy, ksa, esp, irn, per, den, isl, cro, sui, crc, mex, swe, eng, tun, col, sen,
   uru, por, fra, arg, bra, ger, bel, pol,
   por, arg, bra, ger,
   bra, por,
   bel,
   ger}
  /*JAYSU*/,
  {rus, ksa, esp, por, fra, den, arg, cro, bra, sui, ger, kor, bel, pan, col, jpn,
   rus, por, fra, arg, bra, ger, eng, jpn,
   arg, fra, bra, ger,
   arg , ger,
   bra,
   arg}
  /*STJORY*/,
  {uru, rus, esp, por, fra, den, arg, cro, bra , srb, ger, swe, bel, eng, col, pol,
   esp, por, fra, arg, bra, ger, bel, col,
   esp, fra, bra, bel,
   fra, bra,
   bel,
   bra}
  /*STJASU*/,
  {rus, uru, esp, por, fra, den, arg, isl, bra, sui, ger, swe, bel, eng, col, pol,
   por, esp, fra, arg, bra, ger, bel, eng,
   arg, esp, ger, eng,
   ger, esp,
   bra,
   ger}
  /*HESO*/,
  {uru, rus, esp, por, per, fra, arg, cro, bra, srb, ger, mex, bel, eng, col, pol,
   uru, esp, per, arg, ger, bra, bel, col,
   esp, arg, ger, bra,
   ger, arg,
   bra,
   ger}
  /*ULPE*/,
  {uru, rus, esp, por, fra, per, arg, isl, bra, sui, ger, mex, bel, eng, pol, col,
   por, esp, fra, arg, bra, ger, bel, eng,
   por, esp, bra, ger,
   bra, ger,
   esp,
   ger}
  /*STUFJO*/,
  {uru, rus, por, esp, den, fra, arg, isl, bra, srb, ger, swe, eng, bel, col, jpn,
   uru, por, fra, den, bra, ger, col, bel,
   uru, por, bel, ger,
   por, ger,
   bel,
   por}
  /*STASEK*/,
  {uru, rus, por, esp, per, den, arg, cro, bra, srb, ger, swe, bel, eng, col, pol,
   esp, por, per, arg, swe, ger, bel, eng,
   esp, arg, swe, ger,
   swe, arg,
   ger,
   arg}
  /*HKDY*/,
  {rus, uru, esp, por, fra, den, arg, cro, bra, crc, ger, swe, bel, eng, col, pol,
   esp, por, fra, arg, ger, swe, bel, col,
   esp, fra, ger, bel,
   esp, ger,
   bel,
   esp}
  /*STJOKX*/,
  {uru, egy, esp, por, fra, den, arg, cro, sui, bra, ger, swe, eng, bel, col, pol,
   por, esp, fra, arg, swe, bra, eng, bel,
   fra, esp, eng, bra,
   fra, bra,
   esp,
   fra}
  /*STBXWE*/,
  {uru, rus, esp, por, fra, per, arg, cro, bra, sui, ger, mex, bel, eng, col, pol,
   uru, esp, fra, arg, bra, ger, bel, col,
   esp, fra, bra, col,
   fra, bra,
   esp,
   bra}
  /*STMIBO*/,
  {rus, uru, por, esp, fra, aus, cro, arg, bra, sui, ger, mex, bel, eng, col, pol,
   rus, por, fra, cro, bra, ger, bel, eng,
   fra, cro, bra, eng,
   bra, eng,
   cro,
   bra}
  /*STWU*/,
  {uru, rus, por, esp, /*dan,*/ den, fra, arg, isl, bra, sui, ger, swe, bel, eng, sen, col,
   uru, por, fra, arg, ger, swe, bel, col,
   arg, fra, ger, bel,
   arg, bel,
   fra,
   bel}
  /*LILA*/,
  {uru, rus, por, esp, fra, den, arg, cro, bra, sui, ger, swe, bel, eng, col, pol,
   por, esp, arg, fra, ger, bra, bel, pol,
   por, ger, bel, bra,
   por, ger,
   bel,
   ger}
  /*STANNI*/,
  {uru, rus, esp, por, fra, /*dan,*/ den, arg, isl, bra, crc, ger, swe, eng, bel, col, pol,
   uru, esp, fra, arg, bra, ger, eng, col,
   esp, fra, ger, col,
   fra, ger,
   esp,
   ger}
  /*STSTAA*/,
  {rus, uru, por, esp, fra, den, arg, cro, bra, sui, ger, mex, bel, eng, col, pol,
   por, esp, fra, arg, bra, ger, bel, eng,
   por, fra, bra, bel,
   por, bra,
   bel,
   bra}
  /*STKRBU*/,
  {rus, egy, por, esp, fra, per, arg, isl, bra, sui, ger, mex, bel, eng, col, pol,
   rus, por, fra, arg, bra, ger, bel, pol,
   por, arg, bra, bel,
   por, bra,
   bel,
   por}
  /*STTHWA*/,
  {uru, egy, esp, por, fra, den, arg, cro, bra, sui, ger, mex, bel, eng, col, sen,
   por, esp, fra, arg, bra, ger, bel, col,
   fra, esp, bra, ger,
   fra, ger,
   bra,
   ger}
  /*HRJO*/,
  {egy, rus, por, esp, den, per, arg, cro, bra, sui, ger, mex, bel, eng, sen, pol,
   esp, por, den, arg, bra, ger, bel, sen,
   esp, den, bra, ger,
   esp, ger,
   ger,
   bra}
  /*HENO*/,
  {rus, egy, esp, por, fra, den, arg, cro, bra, crc, ger, mex, bel, tun, pol, col,
   egy, esp, fra, arg, ger, bra, pol, bel,
   fra, esp, ger, bra,
   fra, ger,
   esp,
   fra}
  /*STONY*/,
  {rus, uru, esp, por, fra, per, arg, nga, bra, sui, ger, mex, bel, eng, sen, col,
   por, esp, nga, arg, bra, ger, col, eng,
   nga, arg, bra, ger,
   bra, ger,
   nga,
   bra}
  /*CLWF*/,
  {uru, ksa, por, mar, fra, per, arg, nga, bra, sui, ger, mex, bel, eng, col, pol,
   uru, esp, fra, arg, bra, ger, bel, col,
   fra, arg, bra , bel,
   fra, bel,
   bra,
   fra}
  /*CKH*/,
  {uru, egy, esp, por, fra, den, arg, cro, bra, srb, ger, swe, bel, eng, col, pol,
   uru, esp, fra, arg, bra, ger, bel, eng,
   fra, arg, bra, ger,
   bra, arg,
   fra,
   arg}
  /*STANNAN*/,
  {uru, rus, por, esp, fra, den, arg, isl, bra, sui, ger, swe, bel, eng, pol, col,
   esp, por, fra, arg, bra, ger, bel, pol,
   fra, por, bra, ger,
   bra, ger,
   por,
   bra}
  /*HANO*/,
  {ksa, uru, por, mar, aus, fra, cro, isl, bra, sui, mex, swe, pan, tun, col, jpn,
   mar, uru, aus, fra, swe, sui, jpn, tun,
   aus, fra, jpn, sui,
   aus, jpn,
   sui,
   jpn}
  /*DASH*/,
  {uru, rus, por, esp, fra, per, cro, arg, bra, crc, ger, swe, bel, eng, col, pol,
   esp, por, fra, cro, bra, ger, bel, eng,
   por, fra, bra, bel,
   fra, bra,
   bra,
   fra}
  /*DAGR*/,
  {uru, rus, esp, por, den, fra, arg, cro, bra, sui, ger, swe, bel, eng, pol, col,
   por, uru, arg, den, bra, ger, bel, pol,
   por, arg, bra, ger,
   ger, arg,
   por,
   arg}
  /*PESD*/,
  {uru, rus, esp, por, fra, per, arg, cro, bra, sui, ger, swe, bel, eng, pol, col,
   esp, por, arg, fra, bra, ger, bel, eng,
   esp, fra, bra, ger,
   bra, esp,
   ger,
   bra}
  /*KJSV*/,
  {uru, rus, esp, por, fra, per, arg, nga, bra, crc, ger, swe, eng, pan, col, pol,
   uru, por, fra, arg, bra, ger, col, pol,
   uru, arg, bra, ger,
   arg, ger,
   bra,
   arg}
  /*PATSI*/,
  {uru, rus, por, esp, fra, den, arg, isl, bra, sui, ger, mex, bel, eng, pol, col,
   uru, por, fra, arg, crc, ger, bel, eng,
   por, fra, bra, bel,
   fra, bra,
   por,
   bra}
  /*OGLL*/,
  {uru, egy, por, esp, den, fra, arg, cro, bra, srb, ger, swe, bel, eng, sen, pol,
   esp, por, cro, arg, bra, ger, bel, eng,
   esp, bra, por, ger,
   bra, ger,
   por,
   ger}
};
// Early points, not including 10/7 for group placement
const int scoreFromGroups[46] = {
  /*TEST*/ 121,
  /*ANSE*/ 239,
  /*ANNY*/ 242,
  /*HEGR*/ 224,
  /*JOMA*/ 279, 
  /*MXRE*/ 208,
  /*PEAL*/ 206,
  /*MIBJ*/ 262,
  /*GUAS*/ 228,
  /*ADER*/ 225,
  /*MYSJ*/ 286,
  /*STJOEL*/ 215, 
  /*VIST*/ 216,
  /*JASH*/ 187,
  /*ADSU*/ 227,
  /*STMEBR*/ 210,
  /*JAYSU*/ 198,
  /*STJORY*/ 221,
  /*STJASU*/ 218,
  /*HESO*/ 209,
  /*ULPE*/ 270,
  /*STUFJO*/ 197,
  /*STASEK*/ 166,
  /*HKDY*/ 229,
  /*STJOKX*/ 294,
  /*STBXWE*/ 243,
  /*STMIBO*/ 202,
  /*STWU*/ 216,
  /*LILA*/ 227,
  /*STANNI*/ 214,
  /*STSTAA*/ 264,
  /*STKRBU*/ 206,
  /*STTHWA*/ 249,
  /*HRJO*/ 173,
  /*HENO*/ 162,
  /*STONY*/ 207,
  /*CLWF*/ 211,
  /*CKH*/ 228,
  /*STANNAN*/ 212,
  /*HANO*/ 159,
  /*DASH*/ 260,
  /*DAGR*/ 214,
  /*PESD*/ 207,
  /*KJSV*/ 176,
  /*PATSI*/ 200,
  /*OGLL*/ 241
};

void worker_code( void )
{
  e_team c[SIZE_ROW];
  int i, myrank;
  e_person dotp[32];
  MPI_Status status;

  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  if ( myrank <= NR_COMBS ) {
    MPI_Recv( c, SIZE_ROW, MPI_INT, 0, MPI_ANY_TAG,
	      MPI_COMM_WORLD, &status );
    while ( status.MPI_TAG > 0 ) {
      int siz = whoMatchesBest(c, dotp, myrank);
      int tag = status.MPI_TAG;
      MPI_Send( &dotp, siz, MPI_INT, 0, tag, MPI_COMM_WORLD );
      //More job to do? Look at status.MPI_TAG
      MPI_Recv( c, SIZE_ROW, MPI_INT, 0, MPI_ANY_TAG,
		MPI_COMM_WORLD, &status );
    }
    assert(status.MPI_TAG == 0); // Proper end-of-execution
  } else {
    // There are more processors than actually needed
    MPI_Recv( c, SIZE_ROW, MPI_INT, 0, MPI_ANY_TAG,
	      MPI_COMM_WORLD, &status );
    assert(status.MPI_TAG == 0); // Proper end-of-execution
  }
}
struct s_pair {
     e_person person;
     int score;
};
static bool sortPointerToInt(const s_pair left, const s_pair right)
{
  return (left.score != right.score) ? left.score > right.score : left.person < right.person;
}
int top5best(const e_team c[SIZE_ROW], e_person dotp[46], int myrank)
{
  struct s_pair pairs[46];
  for (int p = 0; p < 46; ++p) {
    pairs[p].person = (e_person)p;
    pairs[p].score = personMatch((e_person)p, c, myrank);
  }
  std::sort(&pairs[0], &pairs[46], sortPointerToInt);
  // Count the 5 best e_person:
  int fiveOrMore = 0;
  for (int ii = 0; ii < 5; ++ii) {
    assert(pairs[ii].score >= pairs[ii+1].score);
    dotp[fiveOrMore++] = pairs[ii].person;
  }
  assert(fiveOrMore == 5);
  for (int ii = 5; ii < 46; ++ii) {
    assert(pairs[ii-1].score >= pairs[ii].score);
    if (pairs[ii-1].score == pairs[ii].score) {
      dotp[fiveOrMore++] = pairs[ii].person;
    } else {
      break;
    }
  }
  assert(5 <= fiveOrMore && fiveOrMore <= 46);
  assert(((5 == fiveOrMore) && (pairs[4].score > pairs[5].score))
     || ((fiveOrMore > 5) && (pairs[4].score == pairs[5].score)));
  return fiveOrMore;
}
int whoMatchesBest(const e_team c[SIZE_ROW], e_person dotp[32], int myrank)
{
  int bestPointSoFar = -1;
  int nrTie = 0;
  for (int p = 0; p < 46; ++p) {
    const int score = personMatch((e_person)p, c, myrank);
    if (score > bestPointSoFar) {
      bestPointSoFar = score;
      nrTie = 0;
      dotp[0] = (e_person)p;
    } else if (score == bestPointSoFar) {
      dotp[++nrTie] = (e_person)p;
    } else {
      // Just chuck it away
    }
  }
  return nrTie + 1;
}
int personMatch(e_person p, const e_team c[SIZE_ROW], int myrank)
{
    int score_16 = 0;
    for (int i = 0; i < 16; i += 2) {
      if (c[i] == EXCEL[p][i]) {
	score_16 += 10;
      } else if (c[i] == EXCEL[p][i+1]) {
	score_16 += 7;
      }
      if (c[i+1] == EXCEL[p][i+1]) {
	score_16 += 10;
      } else if (c[i+1] == EXCEL[p][i]) {
	score_16 += 7;
      }
    }
    int score_8 = 0;
    for (int i = 16; i < (16+8); ++i) {
      if (c[i] == EXCEL[p][16] || c[i] == EXCEL[p][17]
	  || c[i] == EXCEL[p][18] || c[i] == EXCEL[p][19]
	  || c[i] == EXCEL[p][20] || c[i] == EXCEL[p][21]
	  || c[i] == EXCEL[p][22] || c[i] == EXCEL[p][23])
	score_8 += 15;
    }
    int score_4 = 0;
    for (int i = 24; i < (24+4); ++i) {
      if (c[i] == EXCEL[p][24] || c[i] == EXCEL[p][25]
	  || c[i] == EXCEL[p][26] || c[i] == EXCEL[p][27])
	score_4 += 25; // Rätt semifinallag
    }
    int score_2 = 0;
    for (int i = 28; i < (28+2); ++i) {
      if (c[i] == EXCEL[p][28] || c[i] == EXCEL[p][29])
	score_2 += 35; // Rätt finallag
    }
    int score_20 = 0;
    if (c[30] == EXCEL[p][30])
      score_20 = 20; // Rätt bronsvinnare
    int score_50 = 0;
    if (c[31] == EXCEL[p][31])
      score_50 = 50; // Rätt världsmästare
    const int score
       = scoreFromGroups[p] +
         score_16 + score_8 + score_4 + score_2 + score_20 + score_50;
    return score;
}
std::ostream& operator<<(std::ostream& o, enum e_team aTeam)
{
  switch(aTeam)
    {
    case rus: o << "rus"; break;
    case ksa: o << "ksa"; break;
    case egy: o << "egy"; break;
    case uru: o << "uru"; break;
    case mar: o << "mar"; break;
    case irn: o << "irn"; break;
    case por: o << "por"; break;
    case esp: o << "esp"; break;
    case fra: o << "fra"; break;
    case aus: o << "aus"; break;
    case per: o << "per"; break;
    case den: o << "den"; break;
    case arg: o << "arg"; break;
    case isl: o << "isl"; break;
    case cro: o << "cro"; break;
    case nga: o << "nga"; break;
    case crc: o << "crc"; break;
    case srb: o << "srb"; break;
    case bra: o << "bra"; break;
    case sui: o << "sui"; break;
    case ger: o << "ger"; break;
    case mex: o << "mex"; break;
    case swe: o << "swe"; break;
    case kor: o << "kor"; break;
    case bel: o << "bel"; break;
    case pan: o << "pan"; break;
    case tun: o << "tun"; break;
    case eng: o << "eng"; break;
    case col: o << "col"; break;
    case jpn: o << "jpn"; break;
    case pol: o << "pol"; break;
    case sen: o << "sen"; break;
    default:
      assert("Should not happen!"[0]==0);
    }
  return o;
}
