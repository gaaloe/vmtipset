#include <mpi.h>
#include <iostream>
#include <cassert>
#define MIN( x, y ) ((x) < (y) ? x : y)
enum e_team {rus, ksa, egy, uru,
             mar, irn, por, esp};
enum e_person {sthrjo, stanny};
#define SIZE_ROW 7
#define NR_COMBS 4*3*4*3*2*2
e_team game_result[SIZE_ROW] = {rus, ksa, mar, irn, rus, ksa, rus};

void manager_code( int numprocs )
{
    int i, sender, row, numsent = 0;
    e_person dotp;
    MPI_Status status;

    for ( i = 1; i < MIN( numprocs, NR_COMBS ); i++ ) {
#if 1
        switch (numsent % 4) {
         case 0:
           game_result[0] = rus;
           game_result[1] = ((numsent/4) % 3 == 0) ? ksa : ((numsent/4 % 3) == 1) ? egy : uru;
           break;
         case 1:
           game_result[0] = ksa;
           game_result[1] = ((numsent/4) % 3 == 0) ? rus : ((numsent/4 % 3) == 1) ? egy : uru;
           break;
         case 2:
           game_result[0] = egy;
           game_result[1] = ((numsent/4) % 3 == 0) ? rus : ((numsent/4 % 3) == 1) ? ksa : uru;
           break;
         case 3:
           game_result[0] = uru;
           game_result[1] = ((numsent/4) % 3 == 0) ? rus : ((numsent/4 % 3) == 1) ? ksa : egy;
           break;
        }
        assert(game_result[0] != game_result[1]);
        switch ((numsent/(4*3)) % 4) {
         case 0:
           game_result[2] = mar;
           game_result[3] = ((numsent/(4*3*4) % 3) == 0) ? irn : ((numsent/(4*3*4) % 3) == 1) ? por : esp;
           break;
         case 1:
           game_result[2] = irn;
           game_result[3] = ((numsent/(4*3*4) % 3) == 0) ? mar : ((numsent/(4*3*4) % 3) == 1) ? por : esp;
           break;
         case 2:
           game_result[2] = por;
           game_result[3] = ((numsent/(4*3*4) % 3) == 0) ? mar : ((numsent/(4*3*4) % 3) == 1) ? irn : esp;
           break;
         case 3:
           game_result[2] = esp;
           game_result[3] = ((numsent/(4*3*4) % 3) == 0) ? mar : ((numsent/(4*3*4) % 3) == 1) ? irn : por;
           break;
        }
        assert(game_result[2] != game_result[3]);
        game_result[4] = ((numsent/(4*3*4*3) % 2) == 0) ? game_result[0] : game_result[1];
        game_result[5] = ((numsent/(4*3*4*3*2) % 2) == 0) ? game_result[2] : game_result[3];
        assert(game_result[4] != game_result[5]);
        game_result[6] = ((numsent/(4*3*4*3*2*2) % 2) == 0) ? game_result[4] : game_result[5];
#endif
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
#if 1
        switch (numsent % 4) {
         case 0:
           game_result[0] = rus;
           game_result[1] = ((numsent/4) % 3 == 0) ? ksa : ((numsent/4 % 3) == 1) ? egy : uru;
           break;
         case 1:
           game_result[0] = ksa;
           game_result[1] = ((numsent/4) % 3 == 0) ? rus : ((numsent/4 % 3) == 1) ? egy : uru;
           break;
         case 2:
           game_result[0] = egy;
           game_result[1] = ((numsent/4) % 3 == 0) ? rus : ((numsent/4 % 3) == 1) ? ksa : uru;
           break;
         case 3:
           game_result[0] = uru;
           game_result[1] = ((numsent/4) % 3 == 0) ? rus : ((numsent/4 % 3) == 1) ? ksa : egy;
           break;
        }
        assert(game_result[0] != game_result[1]);
        switch ((numsent/(4*3)) % 4) {
         case 0:
           game_result[2] = mar;
           game_result[3] = ((numsent/(4*3*4) % 3) == 0) ? irn : ((numsent/(4*3*4) % 3) == 1) ? por : esp;
           break;
         case 1:
           game_result[2] = irn;
           game_result[3] = ((numsent/(4*3*4) % 3) == 0) ? mar : ((numsent/(4*3*4) % 3) == 1) ? por : esp;
           break;
         case 2:
           game_result[2] = por;
           game_result[3] = ((numsent/(4*3*4) % 3) == 0) ? mar : ((numsent/(4*3*4) % 3) == 1) ? irn : esp;
           break;
         case 3:
           game_result[2] = esp;
           game_result[3] = ((numsent/(4*3*4) % 3) == 0) ? mar : ((numsent/(4*3*4) % 3) == 1) ? irn : por;
           break;
        }
        assert(game_result[2] != game_result[3]);
        game_result[4] = ((numsent/(4*3*4*3) % 2) == 0) ? game_result[0] : game_result[1];
        game_result[5] = ((numsent/(4*3*4*3*2) % 2) == 0) ? game_result[2] : game_result[3];
        assert(game_result[4] != game_result[5]);
        game_result[6] = ((numsent/(4*3*4*3*2*2) % 2) == 0) ? game_result[4] : game_result[5];
#endif
            MPI_Send( game_result, SIZE_ROW, MPI_INT, sender,
                      numsent + 1, MPI_COMM_WORLD );
            numsent++;
        }
        else                    /* no more work */
            MPI_Send( MPI_BOTTOM, 0, MPI_INT, sender, 0,
                       MPI_COMM_WORLD );
    }
    assert(numsent == NR_COMBS);
}
