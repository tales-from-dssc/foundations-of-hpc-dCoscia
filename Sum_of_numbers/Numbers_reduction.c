#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#define USE MPI

/* Program that computes in parallel the sum of integers from 1 to N */

int main(int argc, char *argv[ ] ){

 /*------Variables declaration-------*/

    /* numbers to be summed */
    long long int sum = 0, local_sum = 0 ;
    int * arr;
    int s, s0, startIndex, endIndex;

     /* openMPI variable declaration*/
    int myid , numprocs , proc ;
    MPI_Status status;
    MPI_Request request;
    /* times */
    double start_time, end_time;

    /* master process */
    int master = 0;
    int tag = 123;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    if ( argc <=1) {
    fprintf (stderr , " Usage : mpi -np n %s numbers_to_sum \n", argv[0] ) ;
    MPI_Finalize() ;
    exit(-1) ;
    }

    /* allocating dynamical pointer memory */
    arr = (int*)malloc(atoi(argv[1])*sizeof(int));  

    /* filling the array */
    int i;
    for(i = 0; i < atoi(argv[1]); i++){
        arr[i] = i + 1;
    }

    
    s = (int) floor(atoi(argv[1])/numprocs);           /* amount of numbers slave will process */
    s0 = s + atoi(argv[1])%numprocs;                  /* amount of numbers master will process */
      

    /* Definition of start-end index for slave processes */
    startIndex = s0 + (myid - 1)*s;
    endIndex = startIndex + s;

    /* Parallel implementation */

    start_time = MPI_Wtime();

    if(myid == master){                      /* Master processor makes the total sum */
        int i;
        for(i = 0; i < s0; i++){
            local_sum += arr[i];
        }
    }
    else{
        int i;
        for(i = startIndex; i < endIndex; i++){
            local_sum += arr[i];
        }
    }

    MPI_Reduce(&local_sum,&sum,1,MPI_LONG_LONG,MPI_SUM,master,MPI_COMM_WORLD) ; /* receiving message */
    end_time = MPI_Wtime();

    if(myid == master){
        printf("\n The sum of the first N numbers is %llu \n",sum);
        printf ( "\n # walltime on master processor : %10.8f \n", end_time - start_time ) ;
    }

    MPI_Finalize() ;
}
