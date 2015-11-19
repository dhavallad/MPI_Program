#include <stdio.h>
#include "mpi.h"

int main (int argc, char *argv[]){
	
	int numTasks, rank, dest, source, iS, count, tag=1;
	char inmsg, outmsg="x"';
	MPI_Status Stat;
	MPI_Init (&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numTasks)'
	MPI_Comm_rank(MPI_COMM_WORLD, &rank)
	if(rank == 0){
		dest = 1;
		source = 1;
		iS = MPI_Send(&outmsg,1,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
		iS = MPI_Recv(&inmsg,1,MPI_CHAR,source,tag,MPI_COMM_WORLD,&Stat);
	}
	
	else if(rank == 1){
		dest = 0;
		source = 0;
		iS = MPI_Recv(&inmsg,1,MPI_CHAR,source,tag,MPI_COMM_WORLD,&Stat);
		iS = MPI_Send(&outmsg,1,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
			
	}
	
	iS = MPI_Get_count(&Stat,MPI_CHAR,&count);
	printf("Task %d recievved %d char(s) from the thak %d woth tag %d \n", rank,count,Stat.MPI_SOURCE,Stat.MPI_TAG);
	
	MPI_Finalize();
}
