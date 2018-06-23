#include <mpi.h>
#include <iostream>
#include <cassert>
#include "manager_code.h"
enum e_team HRJO[32] = {
  egy, rus, por, esp, den, per, arg, cro, bra, sui, ger, mex, bel, eng, sen, pol,
  esp, por, den, arg, bra, ger, bel, sen,
  esp, den, bra, ger,
  esp, ger,
  ger,
  bra};

void worker_code( void )
{
  e_team c[SIZE_ROW];
  int i, myrank;
  e_person dotp[2];
  MPI_Status status;

  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  if ( myrank <= NR_COMBS ) {
    MPI_Recv( c, SIZE_ROW, MPI_INT, 0, MPI_ANY_TAG,
	      MPI_COMM_WORLD, &status );
    while ( status.MPI_TAG > 0 ) {
      int score_16 = 0;
      for (int i = 0; i < 16; i += 2) {
	if (c[i] == HRJO[i]) {
	  score_16 += 10;
	} else if (c[i] == HRJO[i+1]) {
	  score_16 += 7;
	}
	if (c[i+1] == HRJO[i+1]) {
	  score_16 += 10;
	} else if (c[i+1] == HRJO[i]) {
	  score_16 += 7;
	}
      }
      int score_8 = 0;
      for (int i = 16; i < (16+8); ++i) {
	if (c[i] == HRJO[16] || c[i] == HRJO[17]
	    || c[i] == HRJO[18] || c[i] == HRJO[19]
	    || c[i] == HRJO[20] || c[i] == HRJO[21]
	    || c[i] == HRJO[22] || c[i] == HRJO[23])
	  score_8 += 15;
      }
      int score_4 = 0;
      for (int i = 24; i < (24+4); ++i) {
	if (c[i] == HRJO[24] || c[i] == HRJO[25]
	    || c[i] == HRJO[26] || c[i] == HRJO[27])
	  score_4 += 25; // Rätt semifinallag
      }
      int score_2 = 0;
      for (int i = 28; i < (28+2); ++i) {
	if (c[i] == HRJO[28] || c[i] == HRJO[29])
	  score_2 += 35; // Rätt finallag
      }
      int score_30 = 0;
      if (c[30] == HRJO[30])
	  score_30 = 20; // Rätt bronsvinnare
      int score_50 = 0;
      if (c[31] == HRJO[31])
	  score_50 = 50; // Rätt världsmästare
      const int score = score_16 + score_8 + score_4 + score_2 + score_30 + score_50;
      int tag = status.MPI_TAG;
      dotp[0] = sthrjo;
      MPI_Send( &dotp, 1, MPI_INT, 0, tag, MPI_COMM_WORLD );
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

