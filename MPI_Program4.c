/* LAB 10 */
#include <stdio.h>
#include "mpi.h"

int main (int argc, char *argv[]){
	
	int numtasks,rank;
	
	MPI_Init (&argc,&argv);	
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
	
	int sendBuf[] = {-1,-2};
	sendBuf[0] = rnak + 100;
	sendBuf[1] = rnak + 10;
	
	
	
	int receiveBufSize = numtasks*2;
	int i,receiveBuf[receiveBufSize];
	for(i=0;i<receiveBufSize;i++){
		receiveBuf[i] = 0;
	}
	MPI_Allgather(sendBuf,2,MPI_INT,receiveBuf,2,MPI_INT,MPI_COMM_WORLD);
	
	if(rank == 1`){
		printf("\nAt processor %d\n",rank);
		for(i=0;i<receiveBufSize;i++){
			printf("\n Received buf[%d] = %d \n",i,receiveBuf[i]);
		}
	}

	MPI_Finalize();
}
