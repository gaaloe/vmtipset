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
  long hashRow = 0;
  e_person dotp[2];
  MPI_Status status;
#if 0
  int count_eight[32] = {0};
  int count_quart[32] = {0};
  int count_semi[32] = {0};
  int count_final[32] = {0};
#endif
  int count_win[32] = {0};

  for ( i = 1; i < MIN( numprocs, NR_COMBS / JUMP_HASH); i++ ) {
    construct_row(hashRow, &game_result);
    {
      const enum e_team winnigTeam = game_result[30];
      assert(0 <= winnigTeam && winnigTeam < 32);
      ++count_win[winnigTeam];
#if 0
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
#endif
    }
    MPI_Send( game_result, SIZE_ROW, MPI_INT, i, i, MPI_COMM_WORLD );
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
    MPI_Recv( &dotp, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
	      MPI_COMM_WORLD, &status );
    assert(dotp[0]==sthrjo);
    sender = status.MPI_SOURCE;
    row    = status.MPI_TAG - 1;
    int number = -1;
    MPI_Get_count(&status, MPI_INT, &number);
    assert(number == 1);
    /* send another piece of work to this worker if there is one */
    if ( numsent < NR_COMBS  / JUMP_HASH) {
      construct_row(hashRow, &game_result);
      {
        const enum e_team winnigTeam = game_result[30];
        assert(0 <= winnigTeam && winnigTeam < 32);
        ++count_win[winnigTeam];
#if 0
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
#endif
      }
      MPI_Send( game_result, SIZE_ROW, MPI_INT, sender,
		(numsent + 1)%200000000, MPI_COMM_WORLD );
      numsent++;
      hashRow += JUMP_HASH;
    {
      if (numsent % 1000000 == 0) {
       std::cout << __FILE__<<__LINE__<<' '<<numsent/1000000 << ' ';
       std::cout << (NR_COMBS/JUMP_HASH)/1000000 << std::endl;
      }
    }
    }
    else                    /* no more work */
      MPI_Send( MPI_BOTTOM, 0, MPI_INT, sender, 0,
		MPI_COMM_WORLD );
  }
  assert(numsent == NR_COMBS / JUMP_HASH);
#if 1
  for (enum e_team i = (e_team)0; i < 32; ++i) {
    std::cout << __FILE__<<__LINE__<<' ' << i << ' ' <<count_win[i]<<std::endl;
  }
#endif
}
void construct_row(long hashRow, cupResult_t* vals)
{
  assert(0 <= hashRow && hashRow < NR_COMBS);
  // Group A: //rus, ksa, egy, uru
#define WIN_A 4
#define MOD_A (WIN_A*(WIN_A-1))
  switch ((hashRow/MOD_A) % WIN_A) {
  case 0:
    (*vals)[0] = rus;
    (*vals)[1] = ((hashRow/(MOD_A*WIN_A) % (WIN_A-1)) == 0) ?
      ksa : ((hashRow/(MOD_A*WIN_A) % (WIN_A-1)) == 1) ?
      egy :
      uru;
    break;
  case 1:
    (*vals)[0] = ksa;
    (*vals)[1] = ((hashRow/(MOD_A*WIN_A) % (WIN_A-1)) == 0) ?
      rus : ((hashRow/(MOD_A*WIN_A) % (WIN_A-1)) == 1) ?
      egy :
      uru;
    break;
  case 2:
    (*vals)[0] = egy;
    (*vals)[1] = ((hashRow/(MOD_A*WIN_A) % (WIN_A-1)) == 0) ?
      rus : ((hashRow/(MOD_A*WIN_A) % (WIN_A-1)) == 1) ?
      ksa :
      uru;
    break;
  case 3:
    (*vals)[0] = uru;
    (*vals)[1] = ((hashRow/(MOD_A*WIN_A) % (WIN_A-1)) == 0) ?
      rus : ((hashRow/(MOD_A*WIN_A) % (WIN_A-1)) == 1) ?
      ksa :
      egy;
    break;
  default:
    assert("Should not arrive here!"[0]==0);
  }
  assert((*vals)[0] != (*vals)[1]);
  assert((*vals)[0] == rus || (*vals)[0] == uru || (*vals)[0] == ksa || (*vals)[0] == egy);
  assert((*vals)[1] == rus || (*vals)[1] == uru || (*vals)[1] == ksa || (*vals)[1] == egy);
  // Group B:
#define WIN_B 4
#define MOD_B (MOD_A*WIN_B*(WIN_B-1))
  switch ((hashRow/MOD_A) % WIN_B) {
  case 0:
    (*vals)[2] = mar;
    (*vals)[3] = ((hashRow/(MOD_A*WIN_B) % (WIN_B-1)) == 0) ?
      irn : ((hashRow/(MOD_A*WIN_B) % (WIN_B-1)) == 1) ?
      por :
      esp;
    break;
  case 1:
    (*vals)[2] = irn;
    (*vals)[3] = ((hashRow/(MOD_A*WIN_B) % (WIN_B-1)) == 0) ?
      mar : ((hashRow/(MOD_A*WIN_B) % (WIN_B-1)) == 1) ?
      por :
      esp;
    break;
  case 2:
    (*vals)[2] = por;
    (*vals)[3] = ((hashRow/(MOD_A*WIN_B) % (WIN_B-1)) == 0) ?
      mar : ((hashRow/(MOD_A*WIN_B) % (WIN_B-1)) == 1) ?
      irn :
      esp;
    break;
  case 3:
    (*vals)[2] = esp;
    (*vals)[3] = ((hashRow/(MOD_A*WIN_B) % (WIN_B-1)) == 0) ?
      mar : ((hashRow/(MOD_A*WIN_B) % (WIN_B-1)) == 1) ?
      irn :
      por;
    break;
  default:
    assert("Should not arrive here!"[0]==0);
  }
  assert((*vals)[2] != (*vals)[3]);
  assert((*vals)[2] == mar || (*vals)[2] == irn || (*vals)[2] == por || (*vals)[2] == esp);
  assert((*vals)[3] == mar || (*vals)[3] == irn || (*vals)[3] == por || (*vals)[3] == esp);
  // Group C: fra, aus, per, den,
#define WIN_C 4
#define MOD_C (MOD_B*WIN_C*(WIN_C-1))
  switch ((hashRow/MOD_B) % WIN_C) {
  case 0:
    (*vals)[4] = fra;
    (*vals)[5] = ((hashRow/(MOD_B*WIN_C) % (WIN_C-1)) == 0) ?
      aus : ((hashRow/(MOD_B*WIN_C) % (WIN_C-1)) == 1) ?
      per :
      den;
    break;
  case 1:
    (*vals)[4] = aus;
    (*vals)[5] = ((hashRow/(MOD_B*WIN_C) % (WIN_C-1)) == 0) ?
      fra : ((hashRow/(MOD_B*WIN_C) % (WIN_C-1)) == 1) ?
      per :
      den;
    break;
  case 2:
    (*vals)[4] = per;
    (*vals)[5] = ((hashRow/(MOD_B*WIN_C) % (WIN_C-1)) == 0) ?
      fra : ((hashRow/(MOD_B*WIN_C) % (WIN_C-1)) == 1) ?
      aus :
      den;
    break;
  case 3:
    (*vals)[4] = den;
    (*vals)[5] = ((hashRow/(MOD_B*WIN_C) % (WIN_C-1)) == 0) ?
      fra : ((hashRow/(MOD_B*WIN_C) % (WIN_C-1)) == 1) ?
      aus :
      per;
    break;
  default:
    assert("Should not arrive here!"[0]==0);
  }
  assert((*vals)[4] != (*vals)[5]);
  assert((*vals)[4] == fra || (*vals)[4] == aus || (*vals)[4] == per || (*vals)[4] == den);
  assert((*vals)[5] == fra || (*vals)[5] == aus || (*vals)[5] == per || (*vals)[5] == den);
  // Group D: arg, isl, cro, nga
#define WIN_D 4
#define MOD_D (MOD_C*WIN_D*(WIN_D-1))
  switch ((hashRow/MOD_C) % WIN_D) {
  case 0:
    (*vals)[6] = arg;
    (*vals)[7] = ((hashRow/(MOD_C*WIN_D) % (WIN_D-1)) == 0) ?
      isl : ((hashRow/(MOD_C*WIN_D) % (WIN_D-1)) == 1) ?
      cro :
      nga;
    break;
  case 1:
    (*vals)[6] = isl;
    (*vals)[7] = ((hashRow/(MOD_C*WIN_D) % (WIN_D-1)) == 0) ?
      arg : ((hashRow/(MOD_C*WIN_D) % (WIN_D-1)) == 1) ?
      cro :
      nga;
    break;
  case 2:
    (*vals)[6] = cro;
    (*vals)[7] = ((hashRow/(MOD_C*WIN_D) % (WIN_D-1)) == 0) ?
      arg : ((hashRow/(MOD_C*WIN_D) % (WIN_D-1)) == 1) ?
      isl :
      nga;
    break;
  case 3:
    (*vals)[6] = nga;
    (*vals)[7] = ((hashRow/(MOD_C*WIN_D) % (WIN_D-1)) == 0) ?
      arg : ((hashRow/(MOD_C*WIN_D) % (WIN_D-1)) == 1) ?
      isl :
      cro;
    break;
  default:
    assert("Should not arrive here!"[0]==0);
  }
  assert((*vals)[6] != (*vals)[7]);
  assert((*vals)[6] == arg || (*vals)[6] == isl || (*vals)[6] == cro || (*vals)[6] == nga);
  assert((*vals)[7] == arg || (*vals)[7] == isl || (*vals)[7] == cro || (*vals)[7] == nga);
  // Group E: crc, srb, bra, sui
#define WIN_E 4
#define MOD_E (MOD_D*WIN_E*(WIN_E-1))
  switch ((hashRow/MOD_D) % WIN_E) {
  case 0:
    (*vals)[8] = crc;
    (*vals)[9] = ((hashRow/(MOD_D*WIN_E) % (WIN_E-1)) == 0) ?
      srb : ((hashRow/(MOD_D*WIN_E) % (WIN_E-1)) == 1) ?
      bra :
      sui;
    break;
  case 1:
    (*vals)[8] = srb;
    (*vals)[9] = ((hashRow/(MOD_D*WIN_E) % (WIN_E-1)) == 0) ?
      crc : ((hashRow/(MOD_D*WIN_E) % (WIN_E-1)) == 1) ?
      bra :
      sui;
    break;
  case 2:
    (*vals)[8] = bra;
    (*vals)[9] = ((hashRow/(MOD_D*WIN_E) % (WIN_E-1)) == 0) ?
      crc : ((hashRow/(MOD_D*WIN_E) % (WIN_E-1)) == 1) ?
      srb :
      sui;
    break;
  case 3:
    (*vals)[8] = sui;
    (*vals)[9] = ((hashRow/(MOD_D*WIN_E) % (WIN_E-1)) == 0) ?
      crc : ((hashRow/(MOD_D*WIN_E) % (WIN_E-1)) == 1) ?
      srb :
      bra;
    break;
  default:
    assert("Should not arrive here!"[0]==0);
  }
  assert((*vals)[8] != (*vals)[9]);
  assert((*vals)[8] == crc || (*vals)[8] == srb || (*vals)[8] == bra || (*vals)[8] == sui);
  assert((*vals)[9] == crc || (*vals)[9] == srb || (*vals)[9] == bra || (*vals)[9] == sui);
  // Group F:              ger, mex, swe, kor
#define WIN_F 4
#define MOD_F (MOD_E*WIN_F*(WIN_F-1))
  switch ((hashRow/MOD_E) % WIN_F) {
  case 0:
    (*vals)[10] = ger;
    (*vals)[11] = ((hashRow/(MOD_E*WIN_F) % (WIN_F-1)) == 0) ?
      mex : ((hashRow/(MOD_E*WIN_F) % (WIN_F-1)) == 1) ?
      swe :
      kor;
    break;
  case 1:
    (*vals)[10] = mex;
    (*vals)[11] = ((hashRow/(MOD_E*WIN_F) % (WIN_F-1)) == 0) ?
      ger : ((hashRow/(MOD_E*WIN_F) % (WIN_F-1)) == 1) ?
      swe :
      kor;
    break;
  case 2:
    (*vals)[10] = swe;
    (*vals)[11] = ((hashRow/(MOD_E*WIN_F) % (WIN_F-1)) == 0) ?
      ger : ((hashRow/(MOD_E*WIN_F) % (WIN_F-1)) == 1) ?
      mex :
      kor;
    break;
  case 3:
    (*vals)[10] = kor;
    (*vals)[11] = ((hashRow/(MOD_E*WIN_F) % (WIN_F-1)) == 0) ?
      ger : ((hashRow/(MOD_E*WIN_F) % (WIN_F-1)) == 1) ?
      mex :
      swe;
    break;
  default:
    assert("Should not arrive here!"[0]==0);
  }
  assert((*vals)[10] != (*vals)[11]);
  assert((*vals)[10] == ger || (*vals)[10] == mex || (*vals)[10] == swe || (*vals)[10] == kor);
  assert((*vals)[11] == ger || (*vals)[11] == mex || (*vals)[11] == swe || (*vals)[11] == kor);
  // Group G: bel, pan, tun, eng
#define WIN_G 6
#define MOD_G (MOD_F*WIN_G)
  switch ((hashRow/MOD_F) % WIN_G) {
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
  default:
    assert("Should not arrive here!"[0]==0);
  }
  assert((*vals)[12] != (*vals)[13]);
  assert((*vals)[12] == bel || (*vals)[12] == pan || (*vals)[12] == tun || (*vals)[12] == eng);
  assert((*vals)[13] == bel || (*vals)[13] == pan || (*vals)[13] == tun || (*vals)[13] == eng);
  // Group H: col, jpn, pol, sen
#define WIN_H 4
#define MOD_H ((long)(MOD_G*WIN_H*(WIN_H-1)))
  switch ((hashRow/MOD_G) % WIN_H) {
  case 0:
    (*vals)[14] = col;
    (*vals)[15] = ((hashRow/(MOD_G*WIN_H) % (WIN_H-1)) == 0) ?
      jpn : ((hashRow/(MOD_G*WIN_H) % (WIN_H-1)) == 1) ?
      pol :
      sen;
    break;
  case 1:
    (*vals)[14] = jpn;
    (*vals)[15] = ((hashRow/(MOD_G*WIN_H) % (WIN_H-1)) == 0) ?
      col : ((hashRow/(MOD_G*WIN_H) % (WIN_H-1)) == 1) ?
      pol :
      sen;
    break;
  case 2:
    (*vals)[14] = pol;
    (*vals)[15] = ((hashRow/(MOD_G*WIN_H) % (WIN_H-1)) == 0) ?
      col : ((hashRow/(MOD_G*WIN_H) % (WIN_H-1)) == 1) ?
      jpn :
      sen;
    break;
  case 3:
    (*vals)[14] = sen;
    (*vals)[15] = ((hashRow/(MOD_G*WIN_H) % (WIN_H-1)) == 0) ?
      col : ((hashRow/(MOD_G*WIN_H) % (WIN_H-1)) == 1) ?
      jpn :
      pol;
    break;
  default:
    assert("Should not arrive here!"[0]==0);
  }
  assert((*vals)[14] != (*vals)[15]);
  assert((*vals)[14] == col || (*vals)[14] == jpn || (*vals)[14] == pol || (*vals)[14] == sen);
  assert((*vals)[15] == col || (*vals)[15] == jpn || (*vals)[15] == pol || (*vals)[15] == sen);
  // Slutspel, Åttondelsfinal:
  (*vals)[16] = ((hashRow/MOD_H % 2) == 0) ? (*vals)[0] : (*vals)[3];
  (*vals)[17] = ((hashRow/(MOD_H*2) % 2) == 0) ? (*vals)[2] : (*vals)[1];
  (*vals)[18] = ((hashRow/(MOD_H*2*2) % 2) == 0) ? (*vals)[4] : (*vals)[7];
  (*vals)[19] = ((hashRow/(MOD_H*2*2*2) % 2) == 0) ? (*vals)[6] : (*vals)[5];
  (*vals)[20] = ((hashRow/(MOD_H*2*2*2*2) % 2) == 0) ? (*vals)[8] : (*vals)[11];
  (*vals)[21] = ((hashRow/(MOD_H*2*2*2*2*2) % 2) == 0) ? (*vals)[10] : (*vals)[9];
  (*vals)[22] = ((hashRow/(MOD_H*2*2*2*2*2*2) % 2) == 0) ? (*vals)[12] : (*vals)[15];
  (*vals)[23] = ((hashRow/(MOD_H*2*2*2*2*2*2*2) % 2) == 0) ? (*vals)[14] : (*vals)[13];
#define MOD_8 (MOD_H*2*2*2*2*2*2*2*2)
  // Slutspel, kvartsfinal:
  (*vals)[24] = ((hashRow/MOD_8 % 2) == 0) ? (*vals)[16] : (*vals)[17];
  (*vals)[25] = ((hashRow/(MOD_8*2) % 2) == 0) ? (*vals)[18] : (*vals)[19];
  (*vals)[26] = ((hashRow/(MOD_8*2*2) % 2) == 0) ? (*vals)[20] : (*vals)[21];
  (*vals)[27] = ((hashRow/(MOD_8*2*2*2) % 2) == 0) ? (*vals)[22] : (*vals)[23];
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
