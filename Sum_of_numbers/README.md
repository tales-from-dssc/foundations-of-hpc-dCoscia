# Sum of N numbers
Here is a directory with three different codes that perform the sum of the first N integers is parall using MPI.

`Nnumbers.c` : Define an array between all the processors, compute local sums in each processor and then use  `MPI_Ssend()` - `MPI_Recv()` routines to exchage the local sum and compute the total sum. Walltime is printed for each processor.

`Numbers_reduction_no_arr.c` : Define an array between all the processors, compute local sums in each processor and then use `MPI_Reduce()` routines to compute the sum of all of the local sums. Walltime is printed for each processor.

`Numbers_reduction.c` : Compute local sums in different processors without allocating any array and then use  `MPI_Reduce()` routines to compute the sum of all of the local sums. Walltime is printed only for master processor.
