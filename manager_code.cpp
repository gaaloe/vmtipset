#include <mpi.h>
#include <iostream>
#include <iomanip>
#include <cassert>
#include "manager_code.h"
#define MIN( x, y ) ((x) < (y) ? x : y)
typedef e_team cupResult_t[SIZE_ROW];
#define GRIDX 100
e_team game_result[GRIDX][SIZE_ROW];
int grIdx = 0;
int save_grIdx[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
void construct_row(long numsent, cupResult_t* vals);

void manager_code( int numprocs )
{
  int i, sender, receiveGrIdx;
  long numsent = 0;
  long hashRow = 0;
  e_person dotp[46];
  double accum[46] = {0};
  MPI_Status status;
  for ( i = 1; i < MIN( numprocs, NR_COMBS / JUMP_HASH); i++ ) {
    construct_row(hashRow, &game_result[grIdx]);
    const int sendTag = grIdx + 1;
    assert(sendTag != 0);
    MPI_Send( game_result[grIdx], SIZE_ROW, MPI_INT, i, sendTag, MPI_COMM_WORLD );
    save_grIdx[i] = grIdx;
    ++grIdx %= GRIDX;
    numsent++;
    hashRow += JUMP_HASH;
  }
  if (NR_COMBS / JUMP_HASH < numprocs) {
    for (long j = NR_COMBS / JUMP_HASH; j < numprocs; j++ ) {
      MPI_Send( MPI_BOTTOM, 0, MPI_INT, (int)j, 0,
		MPI_COMM_WORLD );
    }
  }
  /* receive X back from workers */
  for (long j = 0; j < NR_COMBS / JUMP_HASH; j++ ) {
    dotp[0]=(e_person)-1;
    MPI_Recv( &dotp, 46, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
	      MPI_COMM_WORLD, &status );
    assert(0 <= dotp[0] && dotp[0] < 46);
    sender = status.MPI_SOURCE;
    receiveGrIdx = status.MPI_TAG - 1;
    assert(save_grIdx[sender] == receiveGrIdx);
    save_grIdx[sender] = -1;
    int number = -1;
    MPI_Get_count(&status, MPI_INT, &number);
    assert(1 <= number && number <= 46);
    for (int ii = 0; ii < number; ++ii) {
      assert(0 <= dotp[ii] && dotp[ii] < 46);
      accum[dotp[ii]] += 1.0 / number;
#ifndef NDEBUG
      // Perform a 'smoke test'
      const int score1 = personMatch(dotp[ii], game_result[receiveGrIdx], 2);
      const int scoreN = personMatch((e_person)(4711%46), game_result[receiveGrIdx], 2);
      assert(score1 >= scoreN);
#endif
#if 0
      if (dotp[ii] == STONY) {
	// Exempel på en rad som gör att STONY vinner:
        const int score1 = personMatch(dotp[ii], game_result[receiveGrIdx], 2);
	std::cout << __FILE__<<__LINE__<<' '<< score1 << ' '<< "1/" << number<<' ' << accum[dotp[ii]] << std::endl;
	for (int ii = 0; ii < 16; ++ii) {
	  std::cout << game_result[receiveGrIdx][ii] << ' ';
	}
	std::cout << std::endl << std::flush;
	std::cout << game_result[receiveGrIdx][17] << ' ';
	std::cout << game_result[receiveGrIdx][18] << ' ';
	std::cout << game_result[receiveGrIdx][16] << ' ';
	std::cout << game_result[receiveGrIdx][19] << ' ';
	std::cout << game_result[receiveGrIdx][20] << ' ';
	std::cout << game_result[receiveGrIdx][22] << ' ';
	std::cout << game_result[receiveGrIdx][21] << ' ';
	std::cout << game_result[receiveGrIdx][23] << ' ';
	std::cout << std::endl << std::flush;
	std::cout << game_result[receiveGrIdx][24] << ' ';
	std::cout << game_result[receiveGrIdx][27] << ' ';
	std::cout << game_result[receiveGrIdx][25] << ' ';
	std::cout << game_result[receiveGrIdx][26] << ' ';
	std::cout << std::endl << std::flush;
	for (int ii = 28; ii < 30; ++ii) {
	  std::cout << game_result[receiveGrIdx][ii] << ' ';
	}
	std::cout << std::endl << std::flush;
	std::cout << game_result[receiveGrIdx][30] << ' '<< std::endl;
	std::cout << game_result[receiveGrIdx][31] << ' '<< std::endl;
      }
#endif
    }
    /* send another piece of work to this worker if there is one */
    if ( numsent < NR_COMBS  / JUMP_HASH) {
      construct_row(hashRow, &game_result[grIdx]);
      const int sendTag = grIdx + 1;
      assert(sendTag != 0);
      MPI_Send( game_result[grIdx], SIZE_ROW, MPI_INT, sender,
		sendTag, MPI_COMM_WORLD );
      save_grIdx[sender] = grIdx;
      for (;;) {
        ++grIdx %= GRIDX;
        int ii = 1; 
        for (; ii < 8; ++ii) {
          if (save_grIdx[ii] == grIdx) {
	    break; // Not OK!
          }
        }
        if (ii == 8) {
          // OK to use this 'grIdx'
          break;
        }
      }
#ifndef NDEBUG
      // The new 'grIdx' is ready to use, it is not outstanding in any CPU
      for (int ii = 0; ii < 8; ++ii) {
	assert(save_grIdx[ii] != grIdx);
      }
#endif
      numsent++;
      hashRow += JUMP_HASH;
      {
        const int modul = 10000;
	if (numsent % modul == 0) {
	  std::cout << __FILE__<<__LINE__<<' '<<numsent/modul << ' ';
	  std::cout << (NR_COMBS/JUMP_HASH)/modul << std::endl;
	}
      }
    }
    else                    /* no more work */
      MPI_Send( MPI_BOTTOM, 0, MPI_INT, sender, 0,
		MPI_COMM_WORLD );
  }
  assert(numsent == NR_COMBS / JUMP_HASH);
  {
    std::ios init(NULL);
    init.copyfmt(std::cout);
    double sum = 0;
    for (e_person ii = (e_person)0; ii < (e_person)46; ++ii) {
      std::cout << std::setw( 7 ) << ii << ' ';
      std::cout << std::fixed << std::setw( 11 ) << std::setprecision( 1 );
      std::cout << (long)accum[ii] << ' ';
      std::cout << std::fixed << std::setw( 5 ) << std::setprecision( 1 );
      std::cout << (accum[ii] / NR_COMBS) * 100 << '%';
      std::cout << std::endl;
      std::cout.copyfmt(init); // restore default formatting
      sum += accum[ii];
    }
    std::cout << std::setw( 7 ) << "sum:" << ' ';
    std::cout << std::fixed << std::setw( 11 ) << std::setprecision( 1 );
    std::cout << sum << std::endl;
    std::cout.copyfmt(init); // restore default formatting
  }
}
void construct_row(long hashRow, cupResult_t* vals)
{
  assert(0 <= hashRow && hashRow < NR_COMBS);
  // Group A: //rus, ksa, egy, uru
#define MOD_A 1
  (*vals)[0] = uru;
  (*vals)[1] = rus;
  // Group B:
#define MOD_B 1
  (*vals)[2] = esp;
  (*vals)[3] = por;
  // Group C: fra, aus, per, den,
#define WIN_C 1
#define MOD_C (MOD_B*WIN_C)
  //fra,aus fra,den, den,fra?
  (*vals)[4] = fra;
  (*vals)[5] = den;
  assert((*vals)[4] != (*vals)[5]);
  assert((*vals)[4] == fra || (*vals)[4] == den);
  assert((*vals)[5] == fra || (*vals)[5] == aus || (*vals)[5] == den);
  // Group D: arg, isl, cro, nga
#define WIN_D 1
#define MOD_D (MOD_C*WIN_D)
  (*vals)[6] = cro;
  (*vals)[7] = arg;
  assert((*vals)[6] != (*vals)[7]);
  assert((*vals)[6] == arg || (*vals)[6] == isl || (*vals)[6] == cro || (*vals)[6] == nga);
  assert((*vals)[7] == arg || (*vals)[7] == isl || (*vals)[7] == cro || (*vals)[7] == nga);
  // Group E: crc, srb, bra, sui
#define MOD_E (MOD_D)
  (*vals)[8] = bra;
  (*vals)[9] = sui;
  assert((*vals)[8] != (*vals)[9]);
  assert((*vals)[8] == srb || (*vals)[8] == bra || (*vals)[8] == sui);
  assert((*vals)[9] == srb || (*vals)[9] == bra || (*vals)[9] == sui);
  // Group F:              ger, mex, swe, kor
#define MOD_F (MOD_E)
  (*vals)[10] = swe;
  (*vals)[11] = mex;
  assert((*vals)[10] != (*vals)[11]);
  assert((*vals)[10] == ger || (*vals)[10] == mex || (*vals)[10] == swe);
  assert((*vals)[11] == ger || (*vals)[11] == mex || (*vals)[11] == swe);
  // Group G: bel, pan, tun, eng
#define WIN_G 2
#define MOD_G (MOD_F*WIN_G*(WIN_G-1))
  switch ((hashRow/MOD_F) % WIN_G) {
  case 0:
    (*vals)[12] = bel;
    (*vals)[13] = eng;
    break;
  case 1:
    (*vals)[12] = eng;
    (*vals)[13] = bel;
    break;
  default:
    assert("Should not arrive here!"[0]==0);
  }
  assert((*vals)[12] != (*vals)[13]);
  assert((*vals)[12] == bel || (*vals)[12] == eng);
  assert((*vals)[13] == bel || (*vals)[13] == eng);
  // Group H: col, jpn, pol, sen
#define MOD_H ((long)(MOD_G))
  (*vals)[14] = col;
  (*vals)[15] = jpn;
  assert((*vals)[14] != (*vals)[15]);
  assert((*vals)[14] == col || (*vals)[14] == jpn || (*vals)[14] == sen);
  assert((*vals)[15] == col || (*vals)[15] == jpn || (*vals)[15] == sen);
  // Slutspel, Åttondelsfinal:
  (*vals)[16] = ((hashRow/MOD_H % 2) == 0) ? (*vals)[4] : (*vals)[7]; // CD
  (*vals)[17] = ((hashRow/(MOD_H*2) % 2) == 0) ? (*vals)[0] : (*vals)[3]; // AB
  (*vals)[18] = ((hashRow/(MOD_H*2*2) % 2) == 0) ? (*vals)[2] : (*vals)[1]; // AB
  (*vals)[19] = ((hashRow/(MOD_H*2*2*2) % 2) == 0) ? (*vals)[6] : (*vals)[5]; // CD
  (*vals)[20] = ((hashRow/(MOD_H*2*2*2*2) % 2) == 0) ? (*vals)[8] : (*vals)[11]; // EF
  (*vals)[21] = ((hashRow/(MOD_H*2*2*2*2*2) % 2) == 0) ? (*vals)[12] : (*vals)[15]; // GH
  (*vals)[22] = ((hashRow/(MOD_H*2*2*2*2*2*2) % 2) == 0) ? (*vals)[10] : (*vals)[9]; // EF
  (*vals)[23] = ((hashRow/(MOD_H*2*2*2*2*2*2*2) % 2) == 0) ? (*vals)[14] : (*vals)[13]; // GH
#define MOD_8 (MOD_H*2*2*2*2*2*2*2*2)
  // Slutspel, kvartsfinal:
  (*vals)[24] = ((hashRow/MOD_8 % 2) == 0) ? (*vals)[16] : (*vals)[17]; // ABCD
  (*vals)[25] = ((hashRow/(MOD_8*2) % 2) == 0) ? (*vals)[20] : (*vals)[21]; // EFGH
  (*vals)[26] = ((hashRow/(MOD_8*2*2) % 2) == 0) ? (*vals)[22] : (*vals)[23]; // EFGH
  (*vals)[27] = ((hashRow/(MOD_8*2*2*2) % 2) == 0) ? (*vals)[18] : (*vals)[19]; // ABCD
  assert((*vals)[24] != (*vals)[25]);
  assert((*vals)[24] != (*vals)[26]);
  assert((*vals)[24] != (*vals)[27]);
  assert((*vals)[25] != (*vals)[26]);
  assert((*vals)[25] != (*vals)[27]);
  assert((*vals)[26] != (*vals)[27]);
#define MOD_4 (MOD_8*2*2*2*2)
  // semifinal:
  (*vals)[28] = ((hashRow/MOD_4 % 2) == 0) ? (*vals)[24] : (*vals)[25];
  (*vals)[29] = ((hashRow/(MOD_4*2) % 2) == 0) ? (*vals)[26] : (*vals)[27];
  assert((*vals)[28] != (*vals)[29]);
  const enum e_team p3t0 = ((hashRow/MOD_4 % 2) == 1) ? (*vals)[24] : (*vals)[25];
  const enum e_team p3t1 = ((hashRow/(MOD_4*2) % 2) == 1) ? (*vals)[26] : (*vals)[27];
#define MOD_2 (MOD_4*2*2)
  //Final:
  (*vals)[30] = ((hashRow/MOD_2 % 2) == 0) ? p3t0 : p3t1;
  (*vals)[31] = ((hashRow/(MOD_2*2) % 2) == 0) ? (*vals)[28] : (*vals)[29];
#ifndef NDEBUG
  if (!(MOD_2*2*2 == NR_COMBS)) {
    std::cout << __FILE__<<__LINE__<<' '<<MOD_2*2*2 << ' ' << NR_COMBS << std::endl;
  }
#endif
  assert(MOD_2*2*2 == NR_COMBS);
}
e_team operator++(e_team& that)
{
  that = static_cast<e_team>(static_cast<int>(that) + 1);
  return that;
}
e_team operator++(e_team& that, int)
{
  e_team result = that;
  ++that;
  return result;
}
e_person operator++(e_person& that)
{
  that = static_cast<e_person>(static_cast<int>(that) + 1);
  return that;
}
e_person operator++(e_person& that, int)
{
  e_person result = that;
  ++that;
  return result;
}
std::ostream& operator<<(std::ostream& o, enum e_person aPerson)
{
  switch(aPerson)
    {
    case TEST: o << "TEST"; break;
    case ANSE: o << "ANSE"; break;
    case ANNY: o << "ANNY"; break;
    case HEGR: o << "HEGR"; break;
    case JOMA: o << "JOMA"; break;
    case MXRE: o << "MXRE"; break;
    case PEAL: o << "PEAL"; break;
    case MIBJ: o << "MIBJ"; break;
    case GUAS: o << "GUAS"; break;
    case ADER: o << "ADER"; break;
    case MYSJ: o << "MYSJ"; break;
    case STJOEL: o << "STJOEL"; break;
    case VIST: o << "VIST"; break;
    case JASH: o << "JASH"; break;
    case ADSU: o << "ADSU"; break;
    case STMEBR: o << "STMEBR"; break;
    case JAYSU: o << "JAYSU"; break;
    case STJORY: o << "STJORY"; break;
    case STJASU: o << "STJASU"; break;
    case HESO: o << "HESO"; break;
    case ULPE: o << "ULPE"; break;
    case STUFJO: o << "STUFJO"; break;
    case STASEK: o << "STASEK"; break;
    case HKDY: o << "HKDY"; break;
    case STJOKX: o << "STJOKX"; break;
    case STBXWE: o << "STBXWE"; break;
    case STMIBO: o << "STMIBO"; break;
    case STWU: o << "STWU"; break;
    case LILA: o << "LILA"; break;
    case STANNI: o << "STANNI"; break;
    case STSTAA: o << "STSTAA"; break;
    case STKRBU: o << "STKRBU"; break;
    case STTHWA: o << "STTHWA"; break;
    case HRJO: o << "HRJO"; break;
    case HENO: o << "HENO"; break;
    case STONY: o << "STONY"; break;
    case CLWF: o << "CLWF"; break;
    case CKH: o << "CKH"; break;
    case STANNAN: o << "STANNAN"; break;
    case HANO: o << "HANO"; break;
    case DASH: o << "DASH"; break;
    case DAGR: o << "DAGR"; break;
    case PESD: o << "PESD"; break;
    case KJSV: o << "KJSV"; break;
    case PATSI: o << "PATSI"; break;
    case OGLL: o << "OGLL"; break;
    default:
      assert("Should not happen!"[0]==0);
    }
  return o;
}
