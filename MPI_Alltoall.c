/* Simple MPI program to understand Alltoall Operation. */
/* Author : Dhaval Lad */
#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int size, rank,i ,n;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	// Array size must be equal to #processer.
	int sendBuf[size];
	int receiveBuf[size];
	int whoPrints = 1;

	for(i=0;i<size;i++){
		sendBuf[i] = 1+ 4*rank + i;
	}
	// Comment only if condition to print all processor buffer.
	if(rank == whoPrints){
		printf("\nAt Process#%d  ",rank);
		for(i=0;i<size;i++){
			printf("%d ",sendBuf[i]);
		}
		// printf("\n");
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Alltoall(sendBuf,1,MPI_INT,receiveBuf,1,MPI_INT,MPI_COMM_WORLD);
	
	if(rank == 1) printf("\nAfter Calling MPI_Alltoall function...");
	
	// Comment only if condition to print all processor buffer.
	if(rank == whoPrints){
		printf("\nAt Process#%d  ",rank);
		for(i=0;i<size;i++){
			printf("%d ",receiveBuf[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
}