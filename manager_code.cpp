#include <mpi.h>
#include <iostream>
#define MIN( x, y ) ((x) < (y) ? x : y)
enum e_team {rus, alg, eng, irn};
enum e_person {sthrjo, stanny};
#define SIZE 3
e_team game_result[SIZE] = {rus, alg, eng};

void manager_code( int numprocs )
{
    double a[SIZE][SIZE], c[SIZE];

    int i, sender, row, numsent = 0;
    e_person dotp;
    MPI_Status status;

    for ( i = 1; i < MIN( numprocs, SIZE ); i++ ) {
        MPI_Send( game_result, SIZE, MPI_INT, i, i, MPI_COMM_WORLD );
        numsent++;
    }
    if (SIZE < numprocs) {
      for ( i = SIZE; i < numprocs; i++ ) {
            MPI_Send( MPI_BOTTOM, 0, MPI_INT, i, 0,
                       MPI_COMM_WORLD );
      }
    }
    /* receive X back from workers */
    for ( i = 0; i < SIZE; i++ ) {
        MPI_Recv( &dotp, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
                  MPI_COMM_WORLD, &status );
        sender = status.MPI_SOURCE;
        row    = status.MPI_TAG - 1;
        /* send another Y back to this worker if there is one */
        if ( numsent < SIZE ) {
            MPI_Send( game_result, SIZE, MPI_INT, sender,
                      numsent + 1, MPI_COMM_WORLD );
            numsent++;
        }
        else                    /* no more work */
            MPI_Send( MPI_BOTTOM, 0, MPI_INT, sender, 0,
                       MPI_COMM_WORLD );
    }
}
