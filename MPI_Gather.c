/* Simple MPI program to understand Gather Operation. */
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
	
	int receiveBufSize = numTasks*2; // Each Process sends 2 interger.
	int receiveBuf[receiveBufSize];
	int i=0;
	
	// Initialize the receive buffer.
	for(i=0;i<receiveBufSize;i++){
		receiveBuf[i] = 0;
	}
	
	MPI_Gather(sendBuf,2,MPI_INT,//Sending 2 INT,
				receiveBuf,2,MPI_INT, // Gathering 2 INT from each.
				0,MPI_COMM_WORLD); // Master will do gathering.
	
	// Master node will print out Received Buffer.
	if(rank == 0){
		printf("\nAfter Received 2 INT from each process...");
		for(i=0;i<receiveBufSize;i++){
			printf("\nReceived Buffer[%d] = %d",i,receiveBuf[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
}