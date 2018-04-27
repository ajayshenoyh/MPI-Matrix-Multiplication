#include <iostream>
#include <fstream>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define m1 4
#define n1 4
#define m2 4
#define n2 4
#define ROOT 0 //Master
int ROOT_TAG=1; //Master Tag: Multiplication
int WORKER_TAG=2; //Worker Tag :Multiplication
void print_matrix(int m[m1][n2])
{
    printf("*****************************************************************\n");
    printf("Resulted Matrix Multiplication:");
    for (int i=0; i<m1; i++)
    {
        printf("\n\t| ");
        for (int j=0; j<n2; j++)
            printf("%2d ", m[i][j]);
        printf("|");
    }
    printf("\n****************************************************************\n");
}
int main (int argc, char *argv[])
{
    int size,rank,noworkers,src,tag,rows,avg,rem,iStart,err;
    int a[m1][n1],b[n1][n2],c[m1][n2];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status stat;
    if(n1!=m2)
    {
        printf("n1!=m2, Multiplication condition voided [A(m1xn1)XB(m2xn2)]\n");
        MPI_Abort(MPI_COMM_WORLD,err);
        exit(1);
    }
    if (size < 2 )
    {
        printf("Select atleast 2 processes for computation\n");
        MPI_Abort(MPI_COMM_WORLD,err);
        exit(1);
    }
    noworkers = size-1;
    if (rank==ROOT)  //Master computations
    {
        printf("Available workers :%d processes\n",size);
        printf("**************************FILE INPUT****************************\n");
        printf("Grabbing input from files\n A: mpi_project_input1 \t B: mpi_project_input2 \n");
        ifstream inputStream1("mpi_project_input1.txt");
        ifstream inputStream2("mpi_project_input2.txt");
        if (!(inputStream1.is_open()&&inputStream2.is_open())) return -1;
        for (int i=0; i<m1; i++)
            for (int j=0; j<n1; j++)
                inputStream1>>a[i][j];
        for (int i=0; i<m2; i++)
            for (int j=0; j<n2; j++)
                inputStream2>>b[i][j];
        printf("**************************DATA DISTRIBUTION****************************\n");
        avg = m1/noworkers;
        rem = m1%noworkers;
        iStart = 0;
        tag= ROOT_TAG;
        for (int i=1; i<=noworkers; i++)
        {
            rows = (i <= rem) ? avg+1 : avg;
            printf("Computing slice %d (from row %d to %d)\n",i,iStart,(iStart+rows));
            MPI_Send(&iStart, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Send(&a[iStart][0], rows*n1, MPI_INT, i, tag,MPI_COMM_WORLD);
            MPI_Send(&b, n1*n2, MPI_INT, i, tag, MPI_COMM_WORLD);
            iStart = iStart + rows;
        }

        printf("**************************RESULT GATHERING****************************\n");
        tag = WORKER_TAG;
        for (int i=1; i<=noworkers; i++)
        {
            src = i;
            MPI_Recv(&iStart, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &stat);
            MPI_Recv(&rows, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &stat);
            MPI_Recv(&c[iStart][0], rows*n2, MPI_INT, src, tag,MPI_COMM_WORLD, &stat);
            printf("Received results from slice %d\n",src);
        }
        print_matrix(c);
    }


    if (rank > ROOT)
    {
        tag = ROOT_TAG;
        MPI_Recv(&iStart, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &stat);
        MPI_Recv(&rows, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &stat);
        MPI_Recv(&a, rows*n1, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &stat);
        MPI_Recv(&b, n1*n2, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &stat);
        for (int k=0; k<n2; k++)
            for (int i=0; i<rows; i++)
            {
                c[i][k] = 0.0;
                for (int j=0; j<n1; j++)
                    c[i][k] = c[i][k] + a[i][j] * b[j][k];
            }
        tag = WORKER_TAG;
        MPI_Send(&iStart, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD);
        MPI_Send(&c, rows*n2, MPI_INT, ROOT, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

