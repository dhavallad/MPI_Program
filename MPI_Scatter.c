/* Simple MPI program to understand Scatter Operation. */
/* Author : Dhaval Lad */
#include "mpi.h"
#include<stdio.h>
#define SIZE 4

int main(int argc, char *argv[]){
	int numTasks, rank, sendCount, recvCount, source;
	// Array which distributed over processes.
	float sendBuf[SIZE][SIZE] = {{1.0,2.0,3.0,4.0},{5.0,6.0,7.0,8.0},{9.0,10.0,11.0,12.0},{13.0,14.0,15.0,16.0}};
	float recvBuf[SIZE];
	
	// Initilizae MPI enivronment.
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numTasks);
	
	// Must Specify the #of proc is 4
	if(numTasks == SIZE){
		source = 1;
		sendCount = SIZE;
		recvCount = SIZE;
		// Scattering array amoung the processes.
		MPI_Scatter(sendBuf,sendCount,MPI_FLOAT,recvBuf,recvCount,MPI_FLOAT,source,MPI_COMM_WORLD);
		printf("Process#%d Results: %f %f %f %f \n",rank,recvBuf[0],recvBuf[1],recvBuf[2],recvBuf[3]);
	}
	else{
		printf("Must specify %d processors. Terminating \n",SIZE);
	}
	MPI_Finalize();
}