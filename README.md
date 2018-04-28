# MPI-Matrix-Multiplication
# Problem Statement
To multiply two matrices, the number of columns of first matrix should be equal to the number of rows to second matrix. This program displays the error until the number of columns of first matrix is equal to the number of rows of second matrix.
# Problem Approach
int main(int argc, char *argv[]) <br />
{<br />
MPI_Init (&argc, &argv);<br />
MPI_Comm_rank(MPI_COMM_WORLD, &me);<br />
MPI_Comm_size(MPI_COMM_WORLD, &p);<br />
/* Data distribution */<br />
/* Computation */<br />
/* Result gathering */<br />
MPI_Finalize();<br />
}<br />
# Basic Flow
Algorithm: Matrix Multiplication using MPI_Send and MPI_Receive functions<br />
Input : Two input files with mxn matrix values<br />
Output : Cartesian product of two Matrices<br />
Flow:<br />
Step 1:<br />
Change the input files and update the rows and columns accordingly<br />
Step 2:<br />
Compile the program using the command mpicc++ mpi -𝑝roject.𝑐pp −𝑜 𝑝1<br />
Step 3:<br />
Run the program with required number of processors<br />

