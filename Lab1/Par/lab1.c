#include "sys/time.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>



int main(int argc, char *argv[]){
	//Transform the param in variable
int problemChoice= atoi(argv[1]); //Identified by c in the lab1 document
int initNumber = atoi(argv[2]); //Identified by p in the lab1 document
int iteration = atoi(argv[3]); //Identified by n in the lab1 document
//Le chronometre
double timeStart, timeEnd, Texec;
struct timeval tp;
gettimeofday (&tp, NULL); // Debut du chronometre
timeStart = (double) (tp.tv_sec) + (double) (tp.tv_usec) / 1e6;


int matrix[8][8]; //The 8x8 matric
for(int i=0 ; i<8 ; i++){ 
	for(int j=0 ; j<8 ; j++) 
	{ 
		matrix[i][j] = initNumber;
	} 
}

if (problemChoice == 1){
	for(int k=0 ; k<=iteration ; k++){
		for(int i=0 ; i<8 ; i++){ 
			for(int j=0 ; j<8 ; j++) 
			{ 	
				usleep(1000);
				matrix[i][j] = matrix[i][j]+(i+j)*k;
			} 
		}	
	}
}
else if (problemChoice == 2){
	for(int k=0 ; k<=iteration ; k++){
		for(int i=0 ; i<8 ; i++){ 
			for(int j=0 ; j<8 ; j++) 
			{ 
				usleep(1000);
				if(j != 0){
					matrix[i][j] = matrix[i][j]+(matrix[i][j-1] * k);
				} else {
					matrix[i][j] = matrix[i][j]+(i*k);
				}
				
			} 
		}	
	}
}	

printf ("End Matrix \n");
for(int i=0 ; i<8 ; i++){ 
	for(int j=0 ; j<8 ; j++) 
	{ 
		printf ("%.2d ", matrix[i][j]);
	} 
printf ("\n");
}

gettimeofday (&tp, NULL); // Fin du chronometre
timeEnd = (double) (tp.tv_sec) + (double) (tp.tv_usec) / 1e6;
Texec = timeEnd - timeStart; //Temps d'execution en secondes
printf("Execution time in sec : %f\n",Texec);
MPI_Finalize();
return 0;
}