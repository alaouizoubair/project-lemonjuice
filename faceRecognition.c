#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <python3.5/Python.h>
#include <string.h>

int main(int argc, char**argv){

	FILE *fp;
	char subject_list[1035],result[1035];
	char number[5];
	char cmd[1024];
	int cpt=0,i,j,m;

	fp = popen("ls photos/ | tr \"\n\" \" \"", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	while (fgets(subject_list, sizeof(subject_list)-1, fp) != NULL) {

	}
	pclose(fp);

	fp = popen("ls photos| wc -l", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	while (fgets(number, sizeof(number)-1, fp) != NULL) {}
	cpt = atoi(number);
	
	pclose(fp);



	sprintf(cmd,"mpirun -np %d ./imageComp %s %s",cpt,argv[1],subject_list);
	
	

	
	//popen("mpicc imageComp.c -o imageComp", "r");
	fp = popen(cmd, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	while (fgets(result, sizeof(result)-1, fp) != NULL) {
		printf("%s", result);
	}
	

	return 0;
}