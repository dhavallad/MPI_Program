/* Simple MPI program to understand how MPI works.  */
/* Author : Dhaval Lad */

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	int numTasks,rank,pName,isDone;
	char hostname[MPI_MAX_PROCESSOR_NAME];
	
	isDone = MPI_Init(&argc,&argv);
	if(isDone != MPI_SUCCESS){
		printf("Error!!!!!! MPI environment not setup....");
		MPI_Abort(MPI_COMM_WORLD,isDone);
	}
	MPI_Comm_size(MPI_COMM_WORLD,&numTasks);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Get_processor_name(hostname,&pName);
	printf("Number of task = %d. My rank is %d running on %s(hostname) \n",numTasks,rank,hostname);
	MPI_Finalize();
}
