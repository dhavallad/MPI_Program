/* Simple MPI program to understand AllGather Operation. */
/* Author : Dhaval Lad */
#include "mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]){
	int numTasks, rank;
	
	// Initilizae MPI enivronment.
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numTasks);
	int sendBuf[] = {-1,-2};
	
	sendBuf[0] = rank + 100;
	sendBuf[1] = rank + 10;
	
	int receiveBufSize = numTasks*2;// Each Process sends 2 interger.
	int receiveBuf[receiveBufSize];
	int i=0;
	
	// Initialize the receive buffer.
	for(i=0;i<receiveBufSize;i++){
		receiveBuf[i] = 0;
	}
	
	// After gathering all will get same buffer.
	MPI_Allgather(sendBuf,2,MPI_INT,receiveBuf,2,MPI_INT,MPI_COMM_WORLD);
	
	// Any node will received same values...
	if(rank == 1){
		printf("\nAfter Allgather oper at processor#%d ...",rank);
		for(i=0;i<receiveBufSize;i++){
			printf("\nReceived Buffer[%d] = %d.",i,receiveBuf[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
}