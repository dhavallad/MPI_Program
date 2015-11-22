/* LAB 9 */
#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

#define SENDREV_NUMS_TAG 0

int main (int argc, char **argv){
	
	MPI_Init (NULL,NULL);
	
	int comm_size;
	MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
	
	if(comm_size != 2){
		fprintf(stderr,"Must use two processes for this example\n");
		MPI_Abort(MPI_COMM_WORLD,1);
	}
	
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int numbersToSend;
	if(rank == 0){
		const int MAX_NUMBERS = 100;
		int numbers[MAX_NUMBERS];
		srand(time(NULL));
		numbersToSend = (rand() / (float)RAND_MAX * MAX_NUMBERS);
		MPI_Send(numbers,numbersToSend,MPI_INT,1,SENDREV_NUMS_TAG,MPI_COMM_WORLD);
		printf(") sent %d numbers to 1\n",numbersToSend);
	}
	else if(rank == 1){
		MPI_Status status;
		MPI_Probe(0,0,MPI_COMM_WORLD,&status);
		MPI_Get_count(&status,MPI_INT,&numbersToSend);
		int * number_buf = (int*)malloc(sizeof(int)*numbersToSend);
		MPI_Recv(number_buf,numbersToSend,MPI_INT,0,SENDREV_NUMS_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("1 dynamically recievved %d numbers from 0\n",numbersToSend);
		free(number_buf);
			
	}
	MPI_Finalize();
}
