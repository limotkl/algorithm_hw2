#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Matrii_Multipl(int *A, int *B, int *C) { 
     
    *C = *A * *B;
}  


void add(int n, int *A, int *B, int *R)
{ 
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            R[i * n + j] = A[i * n + j]+B[i * n + j];
}


void sub(int n, int *A, int *B, int *R)
{ 
    int i,j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            R[i * n + j] = A[i * n + j] - B[i * n + j];
}


void strassen(int n, int *A, int *B, int *C)
{
 
    if(n == 1) {
        Matrii_Multipl(A, B, C);
    } 
    else {

        int i, j;
        int N = n/2;

        int * A11 = (int *)malloc(sizeof(int) * N * N);
        int *A12 = (int *)malloc(sizeof(int) * N * N);
        int *A21 = (int *)malloc(sizeof(int) * N * N);
        int *A22 = (int *)malloc(sizeof(int) * N * N);

        int *B11 = (int *)malloc(sizeof(int) * N * N);
        int *B12 = (int *)malloc(sizeof(int) * N * N);
        int *B21 = (int *)malloc(sizeof(int) * N * N);
        int *B22 = (int *)malloc(sizeof(int) * N * N);

        int *C11 = (int *)malloc(sizeof(int) * N * N);
        int *C12 = (int *)malloc(sizeof(int) * N * N);
        int *C21 = (int *)malloc(sizeof(int) * N * N);
        int *C22 = (int *)malloc(sizeof(int) * N * N);

        int *AA = (int *)malloc(sizeof(int) * N * N);
        int *BB = (int *)malloc(sizeof(int) * N * N);

        int *M1 = (int *)malloc(sizeof(int) * N * N); 
        int *M2 = (int *)malloc(sizeof(int) * N * N);
        int *M3 = (int *)malloc(sizeof(int) * N * N);
        int *M4 = (int *)malloc(sizeof(int) * N * N);
        int *M5 = (int *)malloc(sizeof(int) * N * N);
        int *M6 = (int *)malloc(sizeof(int) * N * N);
        int *M7 = (int *)malloc(sizeof(int) * N * N);  

        for(i = 0; i < n / 2; i++) {
            for(j = 0; j < n / 2; j++) {
                A11[i * n/2 + j] = A[i * n + j];
                A12[i * n/2 + j] = A[i * n + j + n / 2];
                A21[i * n/2 + j] = A[(i + n / 2) * n + j];
                A22[i * n/2 + j] = A[(i + n / 2) * n + (j + n / 2)];

                B11[i * n/2 + j] = B[i * n + j];
                B12[i * n/2 + j] = B[i * n + j + n / 2];
                B21[i * n/2 + j] = B[(i + n / 2) * n + j];
                B22[i * n/2 + j] = B[(i + n / 2) * n +(j + n / 2)];

            }
        }

        //M1
        add(n/2, A11, A22, AA);
        add(n/2, B11, B22, BB);
        strassen(n/2, AA, BB, M1);
        //M2
        add(n/2, A21, A22, AA);
        strassen(n/2, AA, B11, M2);
        //M3
        sub(n/2, B12, B22, BB);
        strassen(n/2, A11, BB, M3);
        //M4
        sub(n/2, B21, B11, BB);
        strassen(n / 2, A22, BB, M4);
        //M5
        add(n/2, A11, A12, AA);
        //add(n/2, B11, B22, BB);
        strassen(n/2, AA, B22, M5);
        //M6
        sub(n/2, A21, A11, AA);
        add(n/2, B11, B12, BB);
        strassen(n/2, AA, BB, M6);
        //M7
        sub(n/2, A12, A22, AA);
        add(n/2, B21, B22, BB);
        strassen(n/2, AA, BB, M7);

        //C11 = M5 + M4 - M2 + M6
        add(n/2, M1, M4, AA);
        sub(n/2, M7, M5, BB);
        add(n/2, AA, BB, C11);

        //C12 = M1 + M2
        add(n/2, M3, M5, C12);

        //C21 = M3 + M4
        add(n/2, M2, M4, C21);

        //C22 = M5 + M1 - M3 - M7
        add(n/2, M1, M3, AA);
        sub(n/2, M6, M2, BB);
        add(n/2, AA, BB, C22);

         for(i = 0; i < n/2; i++) {  // conquer to one big C
           for(j = 0; j < n/2; j++) {  
            C[i * n + j] = C11[i * n/2 + j];
            C[i * n + (j + n/2)] = C12[i * n/2 + j];
            C[(i+n/2)*n + j] = C21[i * n/2 + j];
            C[(i + n/2)*n + j + n/2] = C22[i * n/2 + j];        
           }
         
        }
        free(A11);
        free(A12);
        free(A21);
        free(A22);
        free(B11);
        free(B12);
        free(B21);
        free(B22);
        free(AA);
        free(BB);
        free(M1);
        free(M2);
        free(M3);
        free(M4);
        free(M5);
        free(M6);
        free(M7); 

    }

}

int main(int argc, char const *argv[])
{
	int i,j,n,count;
    n= atoi(argv[1]);
    int *A,*B,*C;

    A = (int *)malloc(sizeof(int) * n * n); 
    B = (int *)malloc(sizeof(int) * n * n);
    C = (int *)malloc(sizeof(int) * n * n);
    // int A[n][n], B[n][n], C[n][n];
    srand(time(NULL));

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            
            A[i*n+j]=rand()%10+1;
            B[i*n+j]=rand()%10+1;
            C[i*n+j]=0;
        }
    }

printf("matrii A:%d*%d \n",n,n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",A[i*n+j]);
        }
        printf("\n");
    }

    printf("\nmatrii B:%d*%d \n",n,n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",B[i*n+j]);
        }
        printf("\n");
    }

for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            for(count=0;count<n;count++)
            {
                C[i*n+j] = C[i*n+j] + A[i*n+count] * B[count*n+j];
            }
            
        }
    }
    //count=0;
    printf("\n====Standard=====\nmatrix C:%d*%d \n",n,n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",C[i*n+j]);
            //count=count+1;
        }
        printf("\n");
    }
    //printf("\n %d elements\n",count);

    strassen(n, A, B, C);

    printf("\n====Strassen=====\nmatrix C:%d*%d \n",n,n);
    //count=0;
    for(int i = 0; i < n; i++)    {
        for(int j = 0; j < n; j++) {
            printf("%d ", C[i*n+j]);
            //count=count+1;
        }
        printf("\n");
    }
    //printf("\n %d elements\n",count);
    free(A);
    free(B);
    free(C);
    return 0;
}

