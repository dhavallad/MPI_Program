/* Lab 9 - Simple MPI_program to understand MPI_Send & MPI_Recv.  */
/* Author : Dhaval Lad */

#include <stdio.h>
#include "mpi.h"
main (int argc, char *argv[]){
	
	int i,numtasks, rank, next, prev, buf [2], tag1=1, tag2=2;
	MPI_Request reqs[4];
	MPI_Status stats[4];

	MPI_Init (&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	prev = rank-1;
	next = rank+1;
	if (rank == 0) prev=numtasks-1;
	if (rank == (numtasks-1)) next=0;

	MPI_Irecv(&buf[0],1,MPI_INT,prev,tag1,MPI_COMM_WORLD,&reqs[0]);
	MPI_Irecv(&buf[1],1,MPI_INT,next,tag2,MPI_COMM_WORLD,&reqs[1]);

	MPI_Isend (&rank,1,MPI_INT,prev,tag2,MPI_COMM_WORLD,&reqs[2]);
	MPI_Isend (&rank,1,MPI_INT,next,tag1,MPI_COMM_WORLD,&reqs[3]);
	//do some work
	MPI_Waitall (4, reqs, stats);
	for(i=0;i<2;i++){
		// 2 sends
		printf("Task %d: Received from task %d with tag %d \n",
		rank, stats[i].MPI_SOURCE, stats[i].MPI_TAG);
	}
	MPI_Finalize();
}