# MPI-Matrix-Multiplication
# Problem Statement
To multiply two matrices, the number of columns of first matrix should be equal to the number of rows to second matrix. This program displays the error until the number of columns of first matrix is equal to the number of rows of second matrix.
# Problem Approach
int main(int argc, char *argv[])
{
MPI_Init (&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &me);
MPI_Comm_size(MPI_COMM_WORLD, &p);
/* Data distribution */
/* Computation */
/* Result gathering */
MPI_Finalize();
}
# Basic Flow
Algorithm: Matrix Multiplication using MPI_Send and MPI_Receive functions
Input : Two input files with mxn matrix values
Output : Cartesian product of two Matrices
Flow:
Step 1:
Change the input files and update the rows and columns accordingly
Step 2:
Compile the program using the command mpicc++ mpi -𝑝roject.𝑐pp −𝑜 𝑝1
Step 3:
Run the program with required number of processors

