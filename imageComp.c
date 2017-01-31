#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <python3.5/Python.h>
#include <string.h>
#include "mpi.h"

int main(int argc,char** argv){

    FILE *fp;
    char cmd[100];
	char path[1035];
	MPI_Status status;
	int rank,size,i,d;
	double max,maxglob; 
	int root=0;
	int taille = 100;
	int data[taille];
	time_t t;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);


	assert(argc-2 == size);

	// Command to launch the python script

	sprintf(cmd,"python imageComp.py %s %s\n",argv[1],argv[rank+2]);
	

	
	fp = popen(cmd, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		
	}
	pclose(fp);

	max = atof(path);
	
	//printf("%f\n",max);



	MPI_Allreduce(&max,&maxglob,1,MPI_DOUBLE,MPI_MAX,MPI_COMM_WORLD);

	if(maxglob == max){
		//printf("winner is me: %d\n",rank);
		MPI_Send(&rank,1,MPI_INT,0,0,MPI_COMM_WORLD);
		
	}


	if(rank==root){
		MPI_Recv(&d,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
		printf("valeur max: %f from subject%2d\n",maxglob,d+1);
	}



	
	MPI_Finalize();
	
	return 0;
}
