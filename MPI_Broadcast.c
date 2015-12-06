/* Simple MPI program to understand Broadcast Operation. */
/* Author : Dhaval Lad */
#include "mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]){
	int numTasks, rank;
	
	// Initilizae MPI enivronment.
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numTasks);
	
	// Master Node will boracast message to other slaves.
	if(rank == 0){
		int brodcastMsg = 5000;
		MPI_Bcast(&brodcastMsg,1,MPI_INT,rank,MPI_COMM_WORLD);
		printf("\nProcessor#%d: sent message as broadcast (MPI_INT):%d.\n",rank,brodcastMsg);
	}
	//Slaves will receive message from Master.
	else{
		int receiveBroadcastMsg = 0;
		MPI_Bcast(&receiveBroadcastMsg,1,MPI_INT,0,MPI_COMM_WORLD);
		printf("\nProcessor#%d: received message as broadcast (MPI_INT):%d.\n",rank,receiveBroadcastMsg);
	}
	MPI_Finalize();
}