/* Simple MPI program to understand Reduce_Scatter Operation. */
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
	int receiveBuf;
	int receiveCounts[size];

	for(i=0;i<size;i++){
		sendBuf[i] = rank + i;
	}
	
	printf("\nProcess#%d Buffer  ",rank);
	for(i=0;i<size;i++){
		printf("%d ",sendBuf[i]);
	}
	printf("\n");
	
	MPI_Barrier(MPI_COMM_WORLD);
	for(i=0;i<size;i++){
		receiveCounts[i] = 1;
	}
	// First Reduce opeartion perform and result will sactter amoung the processors.
	MPI_Reduce_scatter(sendBuf,&receiveBuf,receiveCounts,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	
	printf("Process#%d Buffer %d\n",rank,receiveBuf);
	MPI_Finalize();
}