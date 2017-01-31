#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <python3.5/Python.h>
#include <string.h>

int main(int argc,char** argv){

    FILE *fp;
    char cmd[100];
	char path[1035];
	int rank,size,i,d=0;
	double maxglob=-1,max; 
	time_t t;

	// Command to launch the python script

	for(i=0;i<argc-2;i++){
	
		sprintf(cmd,"python imageComp.py %s %s\n",argv[1],argv[i+2]);
	
		fp = popen(cmd, "r");
		if (fp == NULL) {
			printf("Failed to run command\n" );
			exit(1);
		}

		while (fgets(path, sizeof(path)-1, fp) != NULL) {
			
		}
		pclose(fp);

		max = atof(path);

		if(maxglob<max || maxglob ==-1){
			maxglob = max;
			d=i;
		}
	}

	
	printf("valeur max: %f from subject%2d\n",maxglob,d+1);
	



	

	
	return 0;
}
