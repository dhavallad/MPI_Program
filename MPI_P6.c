/* Simple MPI_program to MPI_ISend & MPI_IRecv with even number of tasks.  */
/* Author : Dhaval Lad */

#include <stdio.h>
#include "mpi.h"
main (int argc, char *argv[]){
	
	int i,numtasks, rank, next, partnerId, buf [2], tag=1, tag2=2;
	
	MPI_Init (&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Request reqs[2];
	MPI_Status stats[2];
	
	if (rank == 0) printf("Number of task is %d\n",numtasks);
	
	if(rank < numtasks/2){
		partnerId = numtasks/2+rank;
		// printf("%d:%d",rank,partnerId);	
	}
	else{
		partnerId = rank - numtasks/2;
		// printf("%d:%d",rank,partnerId);
	}
	MPI_Irecv(&partnerId,1,MPI_INT,partnerId,tag,MPI_COMM_WORLD,&reqs[0]);
	MPI_Isend(&rank,1,MPI_INT,partnerId,tag,MPI_COMM_WORLD,&reqs[1]);
	//do some work
	MPI_Waitall (2, reqs, stats);

	printf("Task#:%d is partner with Task#%d - Task(%d)->Task(%d)\n",rank,partnerId,rank,partnerId);
	// for(i=0;i<1;i++){
	// 2 sends
	// printf("Task %d: Received from task %d with tag %d \n",
	// rank, stats[i].MPI_SOURCE, stats[i].MPI_TAG);
	// }
	MPI_Finalize();
}