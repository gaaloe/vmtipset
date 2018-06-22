#include <mpi.h>
#include <iostream>
#include <cassert>
#include "manager_code.h"
#define MIN( x, y ) ((x) < (y) ? x : y)
typedef e_team cupResult_t[SIZE_ROW];
e_team game_result[SIZE_ROW];
void construct_row(long numsent, cupResult_t* vals);

void manager_code( int numprocs )
{
  int i, sender, row;
  long numsent = 0;
  e_person dotp;
  MPI_Status status;
  int count_eight[32] = {0};
  int count_quart[32] = {0};
  int count_semi[32] = {0};
  int count_final[32] = {0};
  int count_win[32] = {0};

  for ( i = 1; i < MIN( numprocs, NR_COMBS ); i++ ) {
    construct_row(numsent, &game_result);
    {
      const enum e_team winnigTeam = game_result[30];
      assert(0 <= winnigTeam && winnigTeam < 32);
      ++count_win[winnigTeam];
      const enum e_team finalist1Team = game_result[28];
      const enum e_team finalist2Team = game_result[29];
      assert(0 <= finalist1Team && finalist1Team < 32);
      assert(0 <= finalist2Team && finalist2Team < 32);
      ++count_final[finalist1Team];
      ++count_final[finalist2Team];
      const enum e_team semi1Team = game_result[24];
      const enum e_team semi2Team = game_result[25];
      const enum e_team semi3Team = game_result[26];
      const enum e_team semi4Team = game_result[27];
      assert(0 <= semi1Team && semi1Team < 32);
      assert(0 <= semi2Team && semi2Team < 32);
      assert(0 <= semi3Team && semi3Team < 32);
      assert(0 <= semi4Team && semi4Team < 32);
      ++count_semi[semi1Team];
      ++count_semi[semi2Team];
      ++count_semi[semi3Team];
      ++count_semi[semi4Team];
      const enum e_team quart1Team = game_result[16];
      const enum e_team quart2Team = game_result[17];
      const enum e_team quart3Team = game_result[18];
      const enum e_team quart4Team = game_result[19];
      const enum e_team quart5Team = game_result[20];
      const enum e_team quart6Team = game_result[21];
      const enum e_team quart7Team = game_result[22];
      const enum e_team quart8Team = game_result[23];
      assert(0 <= quart1Team && quart1Team < 32);
      assert(0 <= quart2Team && quart2Team < 32);
      assert(0 <= quart3Team && quart3Team < 32);
      assert(0 <= quart4Team && quart4Team < 32);
      assert(0 <= quart5Team && quart5Team < 32);
      assert(0 <= quart6Team && quart6Team < 32);
      assert(0 <= quart7Team && quart7Team < 32);
      assert(0 <= quart8Team && quart8Team < 32);
      ++count_quart[quart1Team];
      ++count_quart[quart2Team];
      ++count_quart[quart3Team];
      ++count_quart[quart4Team];
      ++count_quart[quart5Team];
      ++count_quart[quart6Team];
      ++count_quart[quart7Team];
      ++count_quart[quart8Team];
      ++count_eight[game_result[0]];
      ++count_eight[game_result[1]];
      ++count_eight[game_result[2]];
      ++count_eight[game_result[3]];
      ++count_eight[game_result[4]];
      ++count_eight[game_result[5]];
      ++count_eight[game_result[6]];
      ++count_eight[game_result[7]];
      ++count_eight[game_result[8]];
      ++count_eight[game_result[9]];
      ++count_eight[game_result[10]];
      ++count_eight[game_result[11]];
      ++count_eight[game_result[12]];
      ++count_eight[game_result[13]];
      ++count_eight[game_result[14]];
      ++count_eight[game_result[15]];
    }
    MPI_Send( game_result, SIZE_ROW, MPI_INT, i, i, MPI_COMM_WORLD );
    numsent++;
  }
  if (NR_COMBS < numprocs) {
    for (long j = NR_COMBS; j < numprocs; j++ ) {
      MPI_Send( MPI_BOTTOM, 0, MPI_INT, (int)j, 0,
		MPI_COMM_WORLD );
    }
  }
  /* receive X back from workers */
  for (long j = 0; j < NR_COMBS; j++ ) {
    MPI_Recv( &dotp, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
	      MPI_COMM_WORLD, &status );
    sender = status.MPI_SOURCE;
    row    = status.MPI_TAG - 1;
    /* send another piece of work to this worker if there is one */
    if ( numsent < NR_COMBS ) {
      construct_row(numsent, &game_result);
      {
        const enum e_team winnigTeam = game_result[30];
        assert(0 <= winnigTeam && winnigTeam < 32);
        ++count_win[winnigTeam];
        const enum e_team finalist1Team = game_result[28];
        const enum e_team finalist2Team = game_result[29];
        assert(0 <= finalist1Team && finalist1Team < 32);
        assert(0 <= finalist2Team && finalist2Team < 32);
        ++count_final[finalist1Team];
        ++count_final[finalist2Team];
      const enum e_team semi1Team = game_result[24];
      const enum e_team semi2Team = game_result[25];
      const enum e_team semi3Team = game_result[26];
      const enum e_team semi4Team = game_result[27];
      assert(0 <= semi1Team && semi1Team < 32);
      assert(0 <= semi2Team && semi2Team < 32);
      assert(0 <= semi3Team && semi3Team < 32);
      assert(0 <= semi4Team && semi4Team < 32);
      ++count_semi[semi1Team];
      ++count_semi[semi2Team];
      ++count_semi[semi3Team];
      ++count_semi[semi4Team];
      const enum e_team quart1Team = game_result[16];
      const enum e_team quart2Team = game_result[17];
      const enum e_team quart3Team = game_result[18];
      const enum e_team quart4Team = game_result[19];
      const enum e_team quart5Team = game_result[20];
      const enum e_team quart6Team = game_result[21];
      const enum e_team quart7Team = game_result[22];
      const enum e_team quart8Team = game_result[23];
      assert(0 <= quart1Team && quart1Team < 32);
      assert(0 <= quart2Team && quart2Team < 32);
      assert(0 <= quart3Team && quart3Team < 32);
      assert(0 <= quart4Team && quart4Team < 32);
      assert(0 <= quart5Team && quart5Team < 32);
      assert(0 <= quart6Team && quart6Team < 32);
      assert(0 <= quart7Team && quart7Team < 32);
      assert(0 <= quart8Team && quart8Team < 32);
      ++count_quart[quart1Team];
      ++count_quart[quart2Team];
      ++count_quart[quart3Team];
      ++count_quart[quart4Team];
      ++count_quart[quart5Team];
      ++count_quart[quart6Team];
      ++count_quart[quart7Team];
      ++count_quart[quart8Team];
      ++count_eight[game_result[0]];
      ++count_eight[game_result[1]];
      ++count_eight[game_result[2]];
      ++count_eight[game_result[3]];
      ++count_eight[game_result[4]];
      ++count_eight[game_result[5]];
      ++count_eight[game_result[6]];
      ++count_eight[game_result[7]];
      ++count_eight[game_result[8]];
      ++count_eight[game_result[9]];
      ++count_eight[game_result[10]];
      ++count_eight[game_result[11]];
      ++count_eight[game_result[12]];
      ++count_eight[game_result[13]];
      ++count_eight[game_result[14]];
      ++count_eight[game_result[15]];
      }
      MPI_Send( game_result, SIZE_ROW, MPI_INT, sender,
		(numsent + 1)%200000000, MPI_COMM_WORLD );
      numsent++;
      {
        if (numsent % 100000000 == 0) {
	  std::cout << __FILE__<<__LINE__<<' '<<numsent/100000000 << ' ';
	  std::cout << NR_COMBS/100000000 << std::endl;
        }
      }
    }
    else                    /* no more work */
      MPI_Send( MPI_BOTTOM, 0, MPI_INT, sender, 0,
		MPI_COMM_WORLD );
  }
  assert(numsent == NR_COMBS);
  for (enum e_team i = (e_team)0; i < 32; ++i) {
    std::cout << __FILE__<<__LINE__<<' '<<count_eight[i]<<std::endl;
    //assert(count_win[i] == NR_COMBS/32);
  }
}
void construct_row(long numsent, cupResult_t* vals)
{
  // Group A:
#define MOD_A 6
  switch (numsent % MOD_A) {
  case 0:
    (*vals)[0] = rus;
    (*vals)[1] = ksa;
    break;
  case 1:
    (*vals)[0] = rus;
    (*vals)[1] = egy;
    break;
  case 2:
    (*vals)[0] = rus;
    (*vals)[1] = uru;
    break;
  case 3:
    (*vals)[0] = ksa;
    (*vals)[1] = egy;
    break;
  case 4:
    (*vals)[0] = ksa;
    (*vals)[1] = uru;
    break;
  case 5:
    (*vals)[0] = egy;
    (*vals)[1] = uru;
    break;
  }
  assert((*vals)[0] != (*vals)[1]);
  assert((*vals)[0] == rus || (*vals)[0] == uru || (*vals)[0] == ksa || (*vals)[0] == egy);
  assert((*vals)[1] == rus || (*vals)[1] == uru || (*vals)[1] == ksa || (*vals)[1] == egy);
  // Group B:
#define WIN_B 4
#define MOD_B (MOD_A*WIN_B*(WIN_B-1))
  switch ((numsent/MOD_A) % WIN_B) {
  case 0:
    (*vals)[2] = mar;
    (*vals)[3] = ((numsent/(MOD_A*WIN_B) % (WIN_B-1)) == 0) ?
      irn : ((numsent/(MOD_A*WIN_B) % (WIN_B-1)) == 1) ?
      por :
      esp;
    break;
  case 1:
    (*vals)[2] = irn;
    (*vals)[3] = ((numsent/(MOD_A*WIN_B) % (WIN_B-1)) == 0) ?
      mar : ((numsent/(MOD_A*WIN_B) % (WIN_B-1)) == 1) ?
      por :
      esp;
    break;
  case 2:
    (*vals)[2] = por;
    (*vals)[3] = ((numsent/(MOD_A*WIN_B) % (WIN_B-1)) == 0) ?
      mar : ((numsent/(MOD_A*WIN_B) % (WIN_B-1)) == 1) ?
      irn :
      esp;
    break;
  case 3:
    (*vals)[2] = esp;
    (*vals)[3] = ((numsent/(MOD_A*WIN_B) % (WIN_B-1)) == 0) ?
      mar : ((numsent/(MOD_A*WIN_B) % (WIN_B-1)) == 1) ?
      irn :
      por;
    break;
  }
  assert((*vals)[2] != (*vals)[3]);
  assert((*vals)[2] == mar || (*vals)[2] == irn || (*vals)[2] == por || (*vals)[2] == esp);
  assert((*vals)[3] == mar || (*vals)[3] == irn || (*vals)[3] == por || (*vals)[3] == esp);
  // Group C: fra, aus, per, den,
#define MOD_C 6
  switch ((numsent/MOD_B) % MOD_C) {
  case 0:
    (*vals)[4] = fra;
    (*vals)[5] = aus;
    break;
  case 1:
    (*vals)[4] = fra;
    (*vals)[5] = per;
    break;
  case 2:
    (*vals)[4] = fra;
    (*vals)[5] = den;
    break;
  case 3:
    (*vals)[4] = aus;
    (*vals)[5] = per;
    break;
  case 4:
    (*vals)[4] = aus;
    (*vals)[5] = den;
    break;
  case 5:
    (*vals)[4] = per;
    (*vals)[5] = den;
    break;
  }
  assert((*vals)[4] != (*vals)[5]);
  assert((*vals)[4] == fra || (*vals)[4] == aus || (*vals)[4] == per || (*vals)[4] == den);
  assert((*vals)[5] == fra || (*vals)[5] == aus || (*vals)[5] == per || (*vals)[5] == den);
  // Group D: arg, isl, cro, nga
#define WIN_D 4
#define MOD_D (MOD_C*WIN_D*(WIN_D-1))
  switch ((numsent/MOD_C) % WIN_D) {
  case 0:
    (*vals)[6] = arg;
    (*vals)[7] = ((numsent/(MOD_C*WIN_D) % (WIN_D-1)) == 0) ?
      isl : ((numsent/(MOD_C*WIN_D) % (WIN_D-1)) == 1) ?
      cro :
      nga;
    break;
  case 1:
    (*vals)[6] = isl;
    (*vals)[7] = ((numsent/(MOD_C*WIN_D) % (WIN_D-1)) == 0) ?
      arg : ((numsent/(MOD_C*WIN_D) % (WIN_D-1)) == 1) ?
      cro :
      nga;
    break;
  case 2:
    (*vals)[6] = cro;
    (*vals)[7] = ((numsent/(MOD_C*WIN_D) % (WIN_D-1)) == 0) ?
      arg : ((numsent/(MOD_C*WIN_D) % (WIN_D-1)) == 1) ?
      isl :
      nga;
    break;
  case 3:
    (*vals)[6] = nga;
    (*vals)[7] = ((numsent/(MOD_C*WIN_D) % (WIN_D-1)) == 0) ?
      arg : ((numsent/(MOD_C*WIN_D) % (WIN_D-1)) == 1) ?
      isl :
      cro;
    break;
  }
  assert((*vals)[6] != (*vals)[7]);
  assert((*vals)[6] == arg || (*vals)[6] == isl || (*vals)[6] == cro || (*vals)[6] == nga);
  assert((*vals)[7] == arg || (*vals)[7] == isl || (*vals)[7] == cro || (*vals)[7] == nga);
  // Group E: crc, srb, bra, sui
#define MOD_E 6
  switch ((numsent/MOD_D) % MOD_E) {
  case 0:
    (*vals)[8] = crc;
    (*vals)[9] = srb;
    break;
  case 1:
    (*vals)[8] = crc;
    (*vals)[9] = bra;
    break;
  case 2:
    (*vals)[8] = crc;
    (*vals)[9] = sui;
    break;
  case 3:
    (*vals)[8] = srb;
    (*vals)[9] = bra;
    break;
  case 4:
    (*vals)[8] = srb;
    (*vals)[9] = sui;
    break;
  case 5:
    (*vals)[8] = bra;
    (*vals)[9] = sui;
    break;
  }
  assert((*vals)[8] != (*vals)[9]);
  assert((*vals)[8] == crc || (*vals)[8] == srb || (*vals)[8] == bra || (*vals)[8] == sui);
  assert((*vals)[9] == crc || (*vals)[9] == srb || (*vals)[9] == bra || (*vals)[9] == sui);
  // Group F:              ger, mex, swe, kor
#define WIN_F 4
#define MOD_F (MOD_E*WIN_F*(WIN_F-1))
  switch ((numsent/MOD_E) % WIN_F) {
  case 0:
    (*vals)[10] = ger;
    (*vals)[11] = ((numsent/(MOD_E*WIN_F) % (WIN_F-1)) == 0) ?
      mex : ((numsent/(MOD_E*WIN_F) % (WIN_F-1)) == 1) ?
      swe :
      kor;
    break;
  case 1:
    (*vals)[10] = mex;
    (*vals)[11] = ((numsent/(MOD_E*WIN_F) % (WIN_F-1)) == 0) ?
      ger : ((numsent/(MOD_E*WIN_F) % (WIN_F-1)) == 1) ?
      swe :
      kor;
    break;
  case 2:
    (*vals)[10] = swe;
    (*vals)[11] = ((numsent/(MOD_E*WIN_F) % (WIN_F-1)) == 0) ?
      ger : ((numsent/(MOD_E*WIN_F) % (WIN_F-1)) == 1) ?
      mex :
      kor;
    break;
  case 3:
    (*vals)[10] = kor;
    (*vals)[11] = ((numsent/(MOD_E*WIN_F) % (WIN_F-1)) == 0) ?
      ger : ((numsent/(MOD_E*WIN_F) % (WIN_F-1)) == 1) ?
      mex :
      swe;
    break;
  }
  assert((*vals)[10] != (*vals)[11]);
  assert((*vals)[10] == ger || (*vals)[10] == mex || (*vals)[10] == swe || (*vals)[10] == kor);
  assert((*vals)[11] == ger || (*vals)[11] == mex || (*vals)[11] == swe || (*vals)[11] == kor);
  // Group G: bel, pan, tun, eng
#define MOD_G 6
  switch ((numsent/MOD_F) % MOD_G) {
  case 0:
    (*vals)[12] = bel;
    (*vals)[13] = pan;
    break;
  case 1:
    (*vals)[12] = bel;
    (*vals)[13] = tun;
    break;
  case 2:
    (*vals)[12] = bel;
    (*vals)[13] = eng;
    break;
  case 3:
    (*vals)[12] = pan;
    (*vals)[13] = tun;
    break;
  case 4:
    (*vals)[12] = pan;
    (*vals)[13] = eng;
    break;
  case 5:
    (*vals)[12] = tun;
    (*vals)[13] = eng;
    break;
  }
  assert((*vals)[12] != (*vals)[13]);
  assert((*vals)[12] == bel || (*vals)[12] == pan || (*vals)[12] == tun || (*vals)[12] == eng);
  assert((*vals)[13] == bel || (*vals)[13] == pan || (*vals)[13] == tun || (*vals)[13] == eng);
  // Group H: col, jpn, pol, sen
#define WIN_H 4
#define MOD_H ((long)(MOD_G*WIN_H*(WIN_H-1)))
  switch ((numsent/MOD_G) % WIN_H) {
  case 0:
    (*vals)[14] = col;
    (*vals)[15] = ((numsent/(MOD_G*WIN_H) % (WIN_H-1)) == 0) ?
      jpn : ((numsent/(MOD_G*WIN_H) % (WIN_H-1)) == 1) ?
      pol :
      sen;
    break;
  case 1:
    (*vals)[14] = jpn;
    (*vals)[15] = ((numsent/(MOD_G*WIN_H) % (WIN_H-1)) == 0) ?
      col : ((numsent/(MOD_G*WIN_H) % (WIN_H-1)) == 1) ?
      pol :
      sen;
    break;
  case 2:
    (*vals)[14] = pol;
    (*vals)[15] = ((numsent/(MOD_G*WIN_H) % (WIN_H-1)) == 0) ?
      col : ((numsent/(MOD_G*WIN_H) % (WIN_H-1)) == 1) ?
      jpn :
      sen;
    break;
  case 3:
    (*vals)[14] = sen;
    (*vals)[15] = ((numsent/(MOD_G*WIN_H) % (WIN_H-1)) == 0) ?
      col : ((numsent/(MOD_G*WIN_H) % (WIN_H-1)) == 1) ?
      jpn :
      pol;
    break;
  }
  assert((*vals)[14] != (*vals)[15]);
  assert((*vals)[14] == col || (*vals)[14] == jpn || (*vals)[14] == pol || (*vals)[14] == sen);
  assert((*vals)[15] == col || (*vals)[15] == jpn || (*vals)[15] == pol || (*vals)[15] == sen);
  // Slutspel, Åttondelsfinal:
  (*vals)[16] = ((numsent/MOD_H % 2) == 0) ? (*vals)[0] : (*vals)[1];
  (*vals)[17] = ((numsent/(MOD_H*2) % 2) == 0) ? (*vals)[2] : (*vals)[3];
  (*vals)[18] = ((numsent/(MOD_H*2*2) % 2) == 0) ? (*vals)[4] : (*vals)[5];
  (*vals)[19] = ((numsent/(MOD_H*2*2*2) % 2) == 0) ? (*vals)[6] : (*vals)[7];
  (*vals)[20] = ((numsent/(MOD_H*2*2*2*2) % 2) == 0) ? (*vals)[8] : (*vals)[9];
  (*vals)[21] = ((numsent/(MOD_H*2*2*2*2*2) % 2) == 0) ? (*vals)[10] : (*vals)[11];
  (*vals)[22] = ((numsent/(MOD_H*2*2*2*2*2*2) % 2) == 0) ? (*vals)[12] : (*vals)[13];
  (*vals)[23] = ((numsent/(MOD_H*2*2*2*2*2*2*2) % 2) == 0) ? (*vals)[14] : (*vals)[15];
#define MOD_8 (MOD_H*2*2*2*2*2*2*2*2)
  // Slutspel, kvartsfinal:
  (*vals)[24] = ((numsent/MOD_8 % 2) == 0) ? (*vals)[16] : (*vals)[17];
  (*vals)[25] = ((numsent/(MOD_8*2) % 2) == 0) ? (*vals)[18] : (*vals)[19];
  (*vals)[26] = ((numsent/(MOD_8*2*2) % 2) == 0) ? (*vals)[20] : (*vals)[21];
  (*vals)[27] = ((numsent/(MOD_8*2*2*2) % 2) == 0) ? (*vals)[22] : (*vals)[23];
  assert((*vals)[24] != (*vals)[25]);
  assert((*vals)[24] != (*vals)[26]);
  assert((*vals)[24] != (*vals)[27]);
  assert((*vals)[25] != (*vals)[26]);
  assert((*vals)[25] != (*vals)[27]);
  assert((*vals)[26] != (*vals)[27]);
#define MOD_4 (MOD_8*2*2*2*2)
  // semifinal:
  (*vals)[28] = ((numsent/MOD_4 % 2) == 0) ? (*vals)[24] : (*vals)[25];
  (*vals)[29] = ((numsent/(MOD_4*2) % 2) == 0) ? (*vals)[26] : (*vals)[27];
  assert((*vals)[28] != (*vals)[29]);
#define MOD_2 (MOD_4*2*2)
  //Final:
  (*vals)[30] = ((numsent/MOD_2 % 2) == 0) ? (*vals)[28] : (*vals)[29];
#if 0
  std::cout << __FILE__<<__LINE__<<' '<<MOD_2*2 << std::endl;
#endif
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
