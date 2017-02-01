#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <python3.5/Python.h>
#include <string.h>
#include <time.h>

/***************************/
/* argv[1] : <nom_photo>   */
/***************************/

int main(int argc, char**argv){

	FILE *fp;
	char subject_list[1035],result[1035];
	char number[5];
	char cmd[1024];
	int cpt=0;
	time_t start_t, end_t;
   	double diff_t;

   	if (argc != 2) {
		printf("Usage: %s <nom_photo>\n",argv[0]);
		exit(1);
	}

   	// On liste les répertoires des sujets et enregistre dans subject_list
	fp = popen("ls photos/ | tr \"\n\" \" \"", "r");
	if (fp == NULL) {
		printf("Echec de la commande\n" );
		exit(1);
	}

	assert(fgets(subject_list, sizeof(subject_list)-1, fp) != NULL);

	pclose(fp);

	//On récupère le nombre de répertoires et enregistre dans cpt
	fp = popen("ls photos| wc -l", "r");

	if (fp == NULL) {
		printf("Echec de la commande\n" );
		exit(1);
	}

	assert(fgets(number, sizeof(number)-1, fp) != NULL);
	cpt = atoi(number);
	
	pclose(fp);

	//Creation de la commande pour lancer le programme en MPI
	sprintf(cmd,"mpirun -np %d ./imageComp %s %s",cpt,argv[1],subject_list);
	
	//On lance le timer
	time(&start_t);	

	//On execute la commande mpirun
	fp = popen(cmd, "r");

	if (fp == NULL) {
		printf("Echec de la commande\n" );
		exit(1);
	}
	//On récupère les résultats de imageComp
	while (fgets(result, sizeof(result)-1, fp) != NULL) {
		printf("%s", result);
	}
	//On arrête le timer
	time(&end_t);
	//On récupère la différence de temps
	diff_t = difftime(end_t, start_t);
	//Affichage du temps d'exécution
	printf("=>Temps d'exécution (Algo Distribué): %.2f secondes\n/******************************************/\n",diff_t);
	

	return 0;
}