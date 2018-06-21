#include <mpi.h>
#include <iostream>
#include <cassert>
#include "manager_code.h"
#define MIN( x, y ) ((x) < (y) ? x : y)
typedef e_team cupResult_t[SIZE_ROW];
e_team game_result[SIZE_ROW];
void construct_row(int numsent, cupResult_t* vals);

void manager_code( int numprocs )
{
  int i, sender, row;
  int numsent = 0;
  e_person dotp;
  MPI_Status status;
  int count_win[16] = {0};

  for ( i = 1; i < MIN( numprocs, NR_COMBS ); i++ ) {
    construct_row(numsent, &game_result);
    {
      const enum e_team winnigTeam = game_result[SIZE_ROW-1];
      assert(0 <= winnigTeam && winnigTeam < 16);
      ++count_win[winnigTeam];
    }
    MPI_Send( game_result, SIZE_ROW, MPI_INT, i, i, MPI_COMM_WORLD );
    numsent++;
  }
  if (NR_COMBS < numprocs) {
    for ( i = NR_COMBS; i < numprocs; i++ ) {
      MPI_Send( MPI_BOTTOM, 0, MPI_INT, i, 0,
		MPI_COMM_WORLD );
    }
  }
  /* receive X back from workers */
  for ( i = 0; i < NR_COMBS; i++ ) {
    MPI_Recv( &dotp, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
	      MPI_COMM_WORLD, &status );
    sender = status.MPI_SOURCE;
    row    = status.MPI_TAG - 1;
    /* send another piece of work to this worker if there is one */
    if ( numsent < NR_COMBS ) {
      construct_row(numsent, &game_result);
      {
        const enum e_team winnigTeam = game_result[SIZE_ROW-1];
        assert(0 <= winnigTeam && winnigTeam < 16);
        ++count_win[winnigTeam];
      }
      MPI_Send( game_result, SIZE_ROW, MPI_INT, sender,
		numsent + 1, MPI_COMM_WORLD );
      numsent++;
    }
    else                    /* no more work */
      MPI_Send( MPI_BOTTOM, 0, MPI_INT, sender, 0,
		MPI_COMM_WORLD );
  }
  assert(numsent == NR_COMBS);
  for (enum e_team i = (e_team)0; i < 16; ++i) {
    assert(count_win[i] == NR_COMBS/16);
  }
}
void construct_row(int numsent, cupResult_t* vals)
{
  // Group A:
#define WIN_A 4
#define ND2_A 3
#define MOD_A (WIN_A*ND2_A)
  switch (numsent % WIN_A) {
  case 0:
    (*vals)[0] = rus;
    (*vals)[1] = ((numsent/WIN_A) % ND2_A == 0) ?
      ksa : ((numsent/WIN_A % ND2_A) == 1) ?
      egy :
      uru;
    break;
  case 1:
    (*vals)[0] = ksa;
    (*vals)[1] = ((numsent/WIN_A) % ND2_A == 0) ?
      rus : ((numsent/WIN_A % ND2_A) == 1) ?
      egy :
      uru;
    break;
  case 2:
    (*vals)[0] = egy;
    (*vals)[1] = ((numsent/WIN_A) % ND2_A == 0) ?
      rus : ((numsent/WIN_A % ND2_A) == 1) ?
      ksa :
      uru;
    break;
  case 3:
    (*vals)[0] = uru;
    (*vals)[1] = ((numsent/WIN_A) % ND2_A == 0) ?
      rus : ((numsent/WIN_A % ND2_A) == 1) ?
      ksa :
      egy;
    break;
  }
  assert((*vals)[0] != (*vals)[1]);
  // Group B:
#define WIN_B 4
#define ND2_B 3
#define MOD_B (MOD_A*WIN_B*ND2_B)
  switch ((numsent/MOD_A) % WIN_B) {
  case 0:
    (*vals)[2] = mar;
    (*vals)[3] = ((numsent/(MOD_A*WIN_B) % ND2_B) == 0) ?
      irn : ((numsent/(MOD_A*WIN_B) % ND2_B) == 1) ?
      por :
      esp;
    break;
  case 1:
    (*vals)[2] = irn;
    (*vals)[3] = ((numsent/(MOD_A*WIN_B) % ND2_B) == 0) ?
      mar : ((numsent/(MOD_A*WIN_B) % ND2_B) == 1) ?
      por :
      esp;
    break;
  case 2:
    (*vals)[2] = por;
    (*vals)[3] = ((numsent/(MOD_A*WIN_B) % ND2_B) == 0) ?
      mar : ((numsent/(MOD_A*WIN_B) % ND2_B) == 1) ?
      irn :
      esp;
    break;
  case 3:
    (*vals)[2] = esp;
    (*vals)[3] = ((numsent/(MOD_A*WIN_B) % ND2_B) == 0) ?
      mar : ((numsent/(MOD_A*WIN_B) % ND2_B) == 1) ?
      irn :
      por;
    break;
  }
  assert((*vals)[2] != (*vals)[3]);
  // Group C: fra, aus, per, den,
#define WIN_C 4
#define ND2_C 3
#define MOD_C (MOD_B*WIN_C*ND2_C)
  switch ((numsent/MOD_B) % WIN_C) {
  case 0:
    (*vals)[4] = fra;
    (*vals)[5] = ((numsent/(MOD_B*WIN_C) % ND2_C) == 0) ?
      aus : ((numsent/(MOD_B*WIN_C) % ND2_C) == 1) ?
      per :
      den;
    break;
  case 1:
    (*vals)[4] = aus;
    (*vals)[5] = ((numsent/(MOD_B*WIN_C) % ND2_C) == 0) ?
      fra : ((numsent/(MOD_B*WIN_C) % ND2_C) == 1) ?
      per :
      den;
    break;
  case 2:
    (*vals)[4] = per;
    (*vals)[5] = ((numsent/(MOD_B*WIN_C) % ND2_C) == 0) ?
      fra : ((numsent/(MOD_B*WIN_C) % ND2_C) == 1) ?
      aus :
      den;
    break;
  case 3:
    (*vals)[4] = den;
    (*vals)[5] = ((numsent/(MOD_B*WIN_C) % ND2_C) == 0) ?
      fra : ((numsent/(MOD_B*WIN_C) % ND2_C) == 1) ?
      aus :
      per;
    break;
  }
  assert((*vals)[4] != (*vals)[5]);
  // Group D: arg, isl, cro, nga};
#define WIN_D 4
#define ND2_D 3
#define MOD_D (MOD_C*WIN_D*ND2_D)
  switch ((numsent/MOD_C) % WIN_D) {
  case 0:
    (*vals)[6] = arg;
    (*vals)[7] = ((numsent/(MOD_C*WIN_D) % ND2_D) == 0) ?
      isl : ((numsent/(MOD_C*WIN_D) % ND2_D) == 1) ?
      cro :
      nga;
    break;
  case 1:
    (*vals)[6] = isl;
    (*vals)[7] = ((numsent/(MOD_C*WIN_D) % ND2_D) == 0) ?
      arg : ((numsent/(MOD_C*WIN_D) % ND2_D) == 1) ?
      cro :
      nga;
    break;
  case 2:
    (*vals)[6] = cro;
    (*vals)[7] = ((numsent/(MOD_C*WIN_D) % ND2_D) == 0) ?
      arg : ((numsent/(MOD_C*WIN_D) % ND2_D) == 1) ?
      isl :
      nga;
    break;
  case 3:
    (*vals)[6] = nga;
    (*vals)[7] = ((numsent/(MOD_C*WIN_D) % ND2_D) == 0) ?
      arg : ((numsent/(MOD_C*WIN_D) % ND2_D) == 1) ?
      isl :
      cro;
    break;
  }
  assert((*vals)[6] != (*vals)[7]);
  // Group E: crc, srb, bra, sui};
#define WIN_E 4
#define ND2_E 3
#define MOD_E (MOD_D*WIN_E*ND2_E)
  switch ((numsent/MOD_D) % WIN_E) {
  case 0:
    (*vals)[8] = crc;
    (*vals)[9] = ((numsent/(MOD_D*WIN_E) % ND2_E) == 0) ?
      srb : ((numsent/(MOD_D*WIN_E) % ND2_E) == 1) ?
      bra :
      sui;
    break;
  case 1:
    (*vals)[8] = srb;
    (*vals)[9] = ((numsent/(MOD_D*WIN_E) % ND2_E) == 0) ?
      crc : ((numsent/(MOD_D*WIN_E) % ND2_E) == 1) ?
      bra :
      sui;
    break;
  case 2:
    (*vals)[8] = bra;
    (*vals)[9] = ((numsent/(MOD_D*WIN_E) % ND2_E) == 0) ?
      crc : ((numsent/(MOD_D*WIN_E) % ND2_E) == 1) ?
      srb :
      sui;
    break;
  case 3:
    (*vals)[8] = sui;
    (*vals)[9] = ((numsent/(MOD_D*WIN_E) % ND2_E) == 0) ?
      crc : ((numsent/(MOD_D*WIN_E) % ND2_E) == 1) ?
      srb :
      bra;
    break;
  }
  assert((*vals)[8] != (*vals)[9]);
  // Slutspel, kvartsfinal:
  (*vals)[8] = ((numsent/MOD_D % 2) == 0) ? (*vals)[0] : (*vals)[1];
  (*vals)[9] = ((numsent/(MOD_D*2) % 2) == 0) ? (*vals)[2] : (*vals)[3];
  (*vals)[10] = ((numsent/(MOD_D*2*2) % 2) == 0) ? (*vals)[4] : (*vals)[5];
  (*vals)[11] = ((numsent/(MOD_D*2*2*2) % 2) == 0) ? (*vals)[6] : (*vals)[7];
  assert((*vals)[8] != (*vals)[9]);
  assert((*vals)[8] != (*vals)[10]);
  assert((*vals)[8] != (*vals)[11]);
  assert((*vals)[9] != (*vals)[10]);
  assert((*vals)[9] != (*vals)[11]);
  assert((*vals)[10] != (*vals)[11]);
  // semifinal:
  (*vals)[12] = ((numsent/(MOD_D*2*2*2*2) % 2) == 0) ? (*vals)[8] : (*vals)[9];
  (*vals)[13] = ((numsent/(MOD_D*2*2*2*2*2) % 2) == 0) ? (*vals)[10] : (*vals)[11];
  assert((*vals)[12] != (*vals)[13]);
  //Final:
  (*vals)[14] = ((numsent/(MOD_D*2*2*2*2*2*2) % 2) == 0) ? (*vals)[12] : (*vals)[13];
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
