/* Simple MPI_program to MPI_ISend & MPI_IRecv with even number of tasks.  */
/* Author : Dhaval Lad */

#include <stdio.h>
#include "mpi.h"
main (int argc, char *argv[]){
	
	int i,numtasks, rank, next, partner, buf [2], tag1=1, tag2=2;
	
	MPI_Init (&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Request reqs[numtasks];
	MPI_Status stats[numtasks];
	
	if (rank == 0){
		printf("Number of task is %d\n",numtasks);
	} 
	
	if(rank < numtasks/2)
	partner = numtasks/2+rank;
	else
	partner = rank - numtasks/2;
	
	for(i=0;i<numtasks;i++){
		MPI_Isend (&i,1,MPI_INT,partner,tag1,MPI_COMM_WORLD,&reqs[i]);
		MPI_Irecv(&i,1,MPI_INT,partner,tag1,MPI_COMM_WORLD,&reqs[i]);
	}
	//do some work
	MPI_Waitall (4, reqs, stats);
	for(i=0;i<1;i++){
		// 2 sends
		printf("Task %d: Received from task %d with tag %d \n",
		rank, stats[i].MPI_SOURCE, stats[i].MPI_TAG);
	}
	MPI_Finalize();
}