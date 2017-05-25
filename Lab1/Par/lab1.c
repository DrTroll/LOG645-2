#include "sys/time.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

typedef struct caseVal {
        int value;
        int col;
        int line;
} cVal;

int main(int argc, char *argv[]){
	//Transform the param in variable
int err; //MPI return value
int problemChoice= atoi(argv[1]); //Identified by c in the lab1 document
int initNumber = atoi(argv[2]); //Identified by p in the lab1 document
int iteration = atoi(argv[3]); //Identified by n in the lab1 document
int ROOT = 0; 
//Le chronometre
double timeStart, timeEnd, Texec;
struct timeval tp;
gettimeofday (&tp, NULL); // Debut du chronometre
timeStart = (double) (tp.tv_sec) + (double) (tp.tv_usec) / 1e6;





err = MPI_Init(&argc, &argv);
int world_rank, world_size, i, j, k, chunkSize, operVal;
err = MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
err = MPI_Comm_size(MPI_COMM_WORLD, &world_size);
int elements_per_proc = (64 / world_size);

int matrix[8][8]; //The 8x8 matric at init
cVal *receive = (cVal *)malloc(world_size*sizeof(cVal));
//cVal receive[elements_per_proc] = (cVal *)malloc(sizeof(cVal) * world_size);
cVal *send = (cVal *)malloc(sizeof(cVal) * world_size);
cVal *final = (cVal *)malloc(sizeof(cVal) * world_size);
if(world_rank == ROOT){


for(int i=0 ; i<8 ; i++){ 
	for(int j=0 ; j<8 ; j++) 
	{ 
		matrix[i][j] = initNumber;
		send[i*8+j].value = i*8+j;
		send[i*8+j].col = j;
		send[i*8+j].line = i;
	} 
}



}



if(world_rank == ROOT){
	printf ("sent Matrix \n");
	for(int i=0 ; i<8 ; i++){ 
	for(int j=0 ; j<8 ; j++) 
	{ 
		printf ("%.2d ", send[i*8+j].value);
		//printf ("%.2d \n", i*8+j);
	} 
	printf ("\n");
	} 
}

/* create a type for struct car */
    const int nitems=2;
    int blocklengths[3] = {1,1,1};
    MPI_Datatype types[3] = {MPI_INT, MPI_INT, MPI_INT};
    MPI_Datatype mpi_cVal;
    MPI_Aint offsets[3];

    offsets[0] = offsetof(cVal, value);
    offsets[1] = offsetof(cVal, col);
    offsets[3] = offsetof(cVal, line);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_cVal);
    MPI_Type_commit(&mpi_cVal);




MPI_Scatter(&send, elements_per_proc, mpi_cVal, &receive, elements_per_proc, mpi_cVal, 0, MPI_COMM_WORLD);
if (problemChoice == 3){
	for(i=0; i<elements_per_proc;i++){
			for(k = 1; k <= iteration; k++){
				usleep(1000);
				receive[i].value = receive[i].value + (receive[i].line + receive[i].col) * k;
			}
		}
}
if(world_rank == ROOT){
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
}
MPI_Gather(&receive, elements_per_proc, mpi_cVal, &final, elements_per_proc, mpi_cVal, 0, MPI_COMM_WORLD);
if(world_rank == ROOT){
	printf ("receive Matrix \n");
	for(int i=0 ; i<8 ; i++){ 
	for(int j=0 ; j<8 ; j++) 
	{ 
		printf ("%.2d ", final[i*8+j].value);
		//printf ("%.2d \n", i*8+j);
	} 
	printf ("\n");
	} 



	printf ("End Matrix seq\n");
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
}

MPI_Finalize();
return 0;
}