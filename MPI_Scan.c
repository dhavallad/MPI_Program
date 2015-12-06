/* Simple MPI program to understand Scan Operation. */
/* Author : Dhaval Lad */
#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
	int input,output,rank;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	// For fibonaaci series calcualtion set master input 1.
	if(rank == 0)
		input = 1; 
	else
		input = rank;
	MPI_Scan (&input,&output,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	printf("Process#%d: Fibonaaci Sum %d\n",rank,output);
	MPI_Finalize();
}