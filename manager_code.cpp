#include <mpi.h>
#include <iostream>
#include <cassert>
#define MIN( x, y ) ((x) < (y) ? x : y)
enum e_team {rus, alg, eng, irn};
enum e_person {sthrjo, stanny};
#define SIZE_ROW 3
// Must be 2^SIZE_ROW
#define NR_COMBS 8
// semi1: rus - alg
// semi2: eng - irn
// final: rus/alg - eng/irn
e_team game_result[SIZE_ROW] = {rus, eng, rus};

void manager_code( int numprocs )
{
    int i, sender, row, numsent = 0;
    e_person dotp;
    MPI_Status status;

    for ( i = 1; i < MIN( numprocs, NR_COMBS ); i++ ) {
        MPI_Send( game_result, SIZE_ROW, MPI_INT, i, i, MPI_COMM_WORLD );
        numsent++;
        game_result[0] = (numsent % 2 == 0) ? rus : alg;
        game_result[1] = ((numsent % 4)/2 == 0) ? eng : irn;
        game_result[2] = ((numsent % 8)/4 == 0) ? game_result[0] : game_result[1];
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
            MPI_Send( game_result, SIZE_ROW, MPI_INT, sender,
                      numsent + 1, MPI_COMM_WORLD );
            numsent++;
        game_result[0] = (numsent % 2 == 0) ? rus : alg;
        game_result[1] = ((numsent % 4)/2 == 0) ? eng : irn;
        game_result[2] = ((numsent % 8)/4 == 0) ? game_result[0] : game_result[1];
        }
        else                    /* no more work */
            MPI_Send( MPI_BOTTOM, 0, MPI_INT, sender, 0,
                       MPI_COMM_WORLD );
    }
    assert(numsent == NR_COMBS);
}
