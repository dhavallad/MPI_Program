/* Simple MPI program to understand Reduce Operation. */
/* Author : Dhaval Lad */
#include "mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]){
	int numTasks, rank,i;
	// Initilizae MPI enivronment.
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numTasks);
	int sendBuf[] = {-1,-2};
	
	sendBuf[0] = rank + 100;
	sendBuf[1] = rank + 10;
	
	int receiveBufSize = 2;
	int receiveBuf[receiveBufSize];

	for(i=0;i<receiveBufSize;i++){
		receiveBuf[i] = 0;
	}
	
	// Master node receive all interger send by other process.
	MPI_Reduce(sendBuf,receiveBuf,receiveBufSize,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	
	// Master node print sum.
	if(rank == 0){
		printf("\nAfter Reduce operation at processor#%d",rank);
		for(i=0;i<receiveBufSize;i++){
			printf("\nReceived Buffer[%d] = %d",i,receiveBuf[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
}