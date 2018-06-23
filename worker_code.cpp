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
      for (e_team i = (e_team)0; i < (e_team)16; ++i, ++i) {
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
#if 0
	std::cout << c[i]<< ' ' << HRJO[i] << ' ';
	std::cout << c[i+1]<< ' ' << HRJO[i+1] << ',';
#endif
      }
#if 0
      std::cout << score_16 <<std::endl;
#endif
      int score_8 = 0;
      for (e_team i = (e_team)16; i < (e_team)(16+8); ++i) {
	if (c[i] == HRJO[(e_team)16] || c[i] == HRJO[(e_team)17]
	    || c[i] == HRJO[(e_team)18] || c[i] == HRJO[(e_team)19]
	    || c[i] == HRJO[(e_team)20] || c[i] == HRJO[(e_team)21]
	    || c[i] == HRJO[(e_team)22] || c[i] == HRJO[(e_team)23])
	  score_8 += 15;
#if 0
	std::cout << c[i]<< ' ' << HRJO[i] << ',';
#endif
      }
#if 0
      std::cout << score_8 <<std::endl;
#endif
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

