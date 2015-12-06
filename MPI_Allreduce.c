/* Simple MPI program to understand AllReduce Operation. */
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
	
	int receiveBufSize = 2;
	int receiveBuf[receiveBufSize];
	int i=0;
	
	
	for(i=0;i<receiveBufSize;i++){
		receiveBuf[i] = 0;
	}
	//All processors contain the reduced result.
	MPI_Allreduce(sendBuf,receiveBuf,receiveBufSize,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	
	// Any node can print as they receive same values.
	if(rank == 2){
		printf("\nAt processor %d",rank);
		for(i=0;i<receiveBufSize;i++){
			printf("\nReceived Buffer[%d] = %d",i,receiveBuf[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
}