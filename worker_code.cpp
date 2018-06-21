#include <mpi.h>
#include <iostream>
#include <cassert>
#include "manager_code.h"
void worker_code( void )
{
  e_team c[SIZE_ROW];
  int i, myrank;
  e_person dotp;
  MPI_Status status;

  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  if ( myrank <= NR_COMBS ) {
    MPI_Recv( c, SIZE_ROW, MPI_INT, 0, MPI_ANY_TAG,
	      MPI_COMM_WORLD, &status );
    while ( status.MPI_TAG > 0 ) {
#if 0
      std::cout << c[0]<< ' ' << c[1] << ' ' << c[2] << ' ';
      std::cout << c[3]<< ' ' << c[4] << ' ' << c[5] << ' ';
      std::cout << c[6]<< ' ' << c[7] << ' ' << c[8] << ' ';
      std::cout << c[9]<< ' ' << c[10] << ' ' << c[11] << ' ';
      std::cout << c[12]<< ' ' << c[13] << ' ' << c[14] << ' ';
      std::cout << std::endl;
#endif
      int tag = status.MPI_TAG;
      dotp = sthrjo;
      MPI_Send( &dotp, 1, MPI_INT, 0, tag, MPI_COMM_WORLD );
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

