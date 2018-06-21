#include <mpi.h>
#include <iostream>
#include <cassert>
#define MIN( x, y ) ((x) < (y) ? x : y)
enum e_team {rus, ksa, egy, uru,
             mar, irn, por, esp,
             fra, aus, per, den,
             arg, isl, cro, nga};
enum e_person {sthrjo, stanny};
#define SIZE_ROW 7
#define NR_COMBS 4*3*4*3*2*2
typedef e_team cupResult_t[SIZE_ROW];
e_team game_result[SIZE_ROW];
void construct_row(int numsent, cupResult_t* vals);

void manager_code( int numprocs )
{
  int i, sender, row;
  int numsent = 0;
  e_person dotp;
  MPI_Status status;

  for ( i = 1; i < MIN( numprocs, NR_COMBS ); i++ ) {
    construct_row(numsent, &game_result);
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
void construct_row(int numsent, cupResult_t* vals)
{
  switch (numsent % 4) {
  case 0:
    (*vals)[0] = rus;
    (*vals)[1] = ((numsent/4) % 3 == 0) ? ksa : ((numsent/4 % 3) == 1) ? egy : uru;
    break;
  case 1:
    (*vals)[0] = ksa;
    (*vals)[1] = ((numsent/4) % 3 == 0) ? rus : ((numsent/4 % 3) == 1) ? egy : uru;
    break;
  case 2:
    (*vals)[0] = egy;
    (*vals)[1] = ((numsent/4) % 3 == 0) ? rus : ((numsent/4 % 3) == 1) ? ksa : uru;
    break;
  case 3:
    (*vals)[0] = uru;
    (*vals)[1] = ((numsent/4) % 3 == 0) ? rus : ((numsent/4 % 3) == 1) ? ksa : egy;
    break;
  }
  assert((*vals)[0] != (*vals)[1]);
  switch ((numsent/(4*3)) % 4) {
  case 0:
    (*vals)[2] = mar;
    (*vals)[3] = ((numsent/(4*3*4) % 3) == 0) ? irn : ((numsent/(4*3*4) % 3) == 1) ? por : esp;
    break;
  case 1:
    (*vals)[2] = irn;
    (*vals)[3] = ((numsent/(4*3*4) % 3) == 0) ? mar : ((numsent/(4*3*4) % 3) == 1) ? por : esp;
    break;
  case 2:
    (*vals)[2] = por;
    (*vals)[3] = ((numsent/(4*3*4) % 3) == 0) ? mar : ((numsent/(4*3*4) % 3) == 1) ? irn : esp;
    break;
  case 3:
    (*vals)[2] = esp;
    (*vals)[3] = ((numsent/(4*3*4) % 3) == 0) ? mar : ((numsent/(4*3*4) % 3) == 1) ? irn : por;
    break;
  }
  assert((*vals)[2] != (*vals)[3]);
  (*vals)[4] = ((numsent/(4*3*4*3) % 2) == 0) ? (*vals)[0] : (*vals)[1];
  (*vals)[5] = ((numsent/(4*3*4*3*2) % 2) == 0) ? (*vals)[2] : (*vals)[3];
  assert((*vals)[4] != (*vals)[5]);
  (*vals)[6] = ((numsent/(4*3*4*3*2*2) % 2) == 0) ? (*vals)[4] : (*vals)[5];
}
