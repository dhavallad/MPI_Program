/* Lab 11 - Simple MPI_program to understand Non-blocking MPI_ISend & MPI_IRecv with [partner]  */
/* Author : Dhaval Lad */

#include <stdio.h>
#include "mpi.h"
main (int argc, char *argv[]){
	
	int i,numTasks, taskId, partnerId,tag=1;
	
	MPI_Init (&argc,&argv);

	MPI_Request request[2];
	MPI_Status status[2];
	
	MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskId);
	if (numTasks % 2 != 0) { //If number of processor is odd then.
		fprintf(stderr,"Number of tasks must be even.\n");
		MPI_Abort(MPI_COMM_WORLD,1);
	}
	// Master print total number of task.
	if (taskId == 0) printf("Total number of task is %d\n",numTasks);
	
	// Assigning partner.
	if(taskId < numTasks/2){
		partnerId = numTasks/2+taskId;
		// printf("%d:%d",taskId,partnerId);	
	}
	else{
		partnerId = taskId - numTasks/2;
		// printf("%d:%d",taskId,partnerId);
	}
	MPI_Irecv(&partnerId,1,MPI_INT,partnerId,tag,MPI_COMM_WORLD,&request[0]);
	MPI_Isend(&taskId,1,MPI_INT,partnerId,tag,MPI_COMM_WORLD,&request[1]);
	//do some work
	MPI_Waitall (2, request, status);

	printf("Task#%d is partner with Task#%d\n",taskId,partnerId);
	// for(i=0;i<1;i++){
	// 2 sends
	// printf("Task %d: Received from task %d with tag %d \n",
	// taskId, status[i].MPI_SOURCE, status[i].MPI_TAG);
	// }
	MPI_Finalize();
}