#include <mpi.h>
#include <iostream>
#include <cassert>
#define SIZE_ROW 3
// Must be 2^SIZE_ROW
#define NR_COMBS 8
enum e_team {rus, alg, eng, irn};
enum e_person {sthrjo, stanny};
void worker_code( void )
{
    e_team c[SIZE_ROW];
    int i, row, myrank;
    e_person dotp;
    MPI_Status status;

    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    if ( myrank <= NR_COMBS ) {
        MPI_Recv( c, SIZE_ROW, MPI_INT, 0, MPI_ANY_TAG,
                  MPI_COMM_WORLD, &status );
        while ( status.MPI_TAG > 0 ) {
#if 0
std::cout << c[0]<< ' ' << c[1] << ' ' << c[2] << std::endl;
#endif
            row = status.MPI_TAG - 1;
            dotp = sthrjo;
            MPI_Send( &dotp, 1, MPI_INT, 0, row + 1,
                      MPI_COMM_WORLD );
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

