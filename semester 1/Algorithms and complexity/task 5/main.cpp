#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#define n 4

using namespace std;

int strassen(int (&A)[n][n],int (&B)[n][n],int (&C)[n][n],int half);
int multi(int (&MA)[n][n],int (&MB)[n][n],int (&MC)[n][n]);
int add(int (&AM)[n][n],int (&BM)[n][n],int (&CM)[n][n],int segment);
int sub(int (&AM1)[n][n],int (&BM1)[n][n],int (&CM1)[n][n],int seg);
void create_random (int (&matr)[n][n]);
void create_0 (int (&matr)[n][n]);
void show (int (&matr)[n][n]);
void strassen_func (int (&A)[n][n],int (&B)[n][n],int (&C)[n][n]);

int strassen(int (&A)[n][n],int (&B)[n][n],int (&C)[n][n],int half)
{
    half=half/2;
    if (half!=1)
    {
        int full = half*2;
        int A11[n][n],A12[n][n],A21[n][n],A22[n][n],B11[n][n],B12[n][n],B21[n][n],B22[n][n],C11[n][n],C12[n][n],C21[n][n],C22[n][n],P1[n][n],P2[n][n],P3[n][n],P4[n][n],P5[n][n],P6[n][n],P7[n][n],Result1[n][n],Result2[n][n],i,j;
        for (i=0;i<half;i++)
        {
            for(j=0;j<full;j++)
            {
                A11[i][j] = A[i][j];
            }
        }

        for (i=0;i<half;i++)
        {
            for(j=half;j<full;j++)
            {
                A12[i][j-half] = A[i][j];
            }
        }

        for (i=half;i<full;i++)
        {
            for(j=0;j<half;j++)
            {
                A21[i-half][j] = A[i][j];
            }
        }

        for (i=half;i<full;i++)
        {
            for(j=half;j<full;j++)
            {
                A22[i-half][j-half] = A[i][j];
            }
        }
        for (i=0;i<half;i++)
        {
            for(j=0;j<half;j++)
            {
                B11[i][j] = B[i][j];
            }
        }
        for (i=0;i<half;i++)
        {
            for(j=half;j<full;j++)
            {
                B12[i][j-half] = B[i][j];
            }
        }
        for (i=half;i<full;i++)
        {
            for(j=0;j<half;j++)
            {
                B21[i-half][j] = A[i][j];
            }
        }
        for (i=half;i<full;i++)
        {
            for(j=half;j<full;j++)
            {
                B22[i-half][j-half] = B[i][j];
            }
        }
        for (i=0;i<half;i++)
        {
            for(j=0;j<half;j++)
            {
                C11[i][j] = C[i][j];
            }
        }
        for (i=0;i<half;i++)
        {
            for(j=half;j<full;j++)
            {
                C12[i][j-half] = C[i][j];
            }
        }
        for (i=half;i<full;i++)
        {
            for(j=0;j<half;j++)
            {
                C21[i-half][j] = C[i][j];
            }
        }
        for (i=half;i<full;i++)
        {
            for(j=half;j<full;j++)
            {
                C22[i-half][j-half] = C[i][j];
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sub(B12,B22,Result1,half);
        multi(A11,Result1,P1);
        //////////////////////////////
        add(A11,A12,Result1,half);
        strassen(Result1,B22,P2,half);
        //////////////////////////////
        add(A21,A22,Result1,half);
        strassen(Result1,B11,P3,half);
        //////////////////////////////
        sub(B21,B11,Result1,half);
        strassen(A22,Result1,P4,half);
        //////////////////////////////
        add(A11,A22,Result1,half);
        add(B11,B22,Result2,half);
        strassen(Result1,Result2,P5,half);
        //////////////////////////////
        sub(A12,A22,Result1,half);
        add(B21,B22,Result2,half);
        strassen(Result1,Result2,P6,half);
        //////////////////////////////
        sub(A21,A11,Result1,half);
        add(B11,B12,Result2,half);
        strassen(Result1,Result2,P7,half);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        add(P1,P2,C12,half);
        /////////////////////
        add(P3,P4,C21,half);
        /////////////////////
        add(P5,P6,Result1,half);
        sub(P4,P2,Result2,half);
        add(Result1,Result2,C11,half);
        ////////////////////
        sub(P1,P3,Result1,half);
        add(P5,P7,Result2,half);
        add(Result1,Result2,C22,half);
        ///////////////////
        for (i=0;i<half;i++)
        {
            for(j=0;j<half;j++)
            {
                C[i][j] = C11[i][j];
            }
        }
        for (i=0;i<half;i++)
        {
            for(j=half;j<n;j++)
            {
                C[i][j] = C12[i][j-half];
            }
        }
        for (i=half;i<n;i++)
        {
            for(j=0;j<half;j++)
            {
                C[i][j] = C21[i-half][j];
            }
        }
        for (i=half;i<n;i++)
        {
            for(j=half;j<n;j++)
            {
                C[i][j] = C22[i-half][j-half];
            }
        }
    }
    else
    {
        multi(A,B,C);
    }
    return 0;
}
int multi(int (&MA)[n][n],int (&MB)[n][n],int (&MC)[n][n])
{
    int p1 = (MA[0][0]+MA[1][1])*(MB[0][0]+MB[1][1]);
    int p2 = (MA[1][0]+MA[1][1])*MB[0][0];
    int p3 = MA[0][0]*(MB[0][1]-MB[1][1]);
    int p4 = MA[1][1]*(MB[1][0]-MB[0][0]);
    int p5 = (MA[0][0]+MA[0][1])*MB[1][1];
    int p6 = (MA[0][1]-MA[0][0])*(MB[0][0]+MB[0][1]);
    int p7 = (MA[0][1]-MA[0][0])*(MB[1][0]+MB[1][1]);
    MC[0][0] = p1+p4-p5+p7;
    MC[0][1] = p2+p4;
    MC[1][0] = p3+p5;
    MC[1][1] = p1-p2+p3+p6;
    return 0;
}
int add(int (&AM)[n][n],int (&BM)[n][n],int (&CM)[n][n],int segment)
{
    int i,j;
    for (i=0;i<segment;i++)
    {
        for (j=0;j<segment;j++)
        {
            CM[i][j] = AM[i][j] + BM[i][j];
        }
    }
    return 0;
}
int sub(int (&AM1)[n][n],int (&BM1)[n][n],int (&CM1)[n][n],int seg)
{
    int i,j;
    for (i=0;i<seg;i++)
    {
        for (j=0;j<seg;j++)
        {
            CM1[i][j] = AM1[i][j] - BM1[i][j];
        }
    }
    return 0;
}

void create_random (int (&matr)[n][n])
{
    int i,j;
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            matr[i][j] = rand() % 10 + 1;
        }
    }
}

void create_0 (int (&matr)[n][n])
{
    int i,j;
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            matr[i][j] = 0;
        }
    }
}

void show (int (&matr)[n][n])
{
    int i,j;
    for (i=0;i<n;i++)
    {
        cout << "| ";
        for (j=0;j<n;j++)
        {
            cout << matr[i][j] << " ";
        }
        cout << " |";
        cout << endl;
    }
    cout << endl;
}

void strassen_func (int (&a)[n][n],int (&b)[n][n],int (&c)[n][n])
{
    strassen(a,b,c,n);
}

void copy_matr (int (&New)[n][n],int (&Old)[n][n])
{
    int i,j;
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            New[i][j] = Old[i][j];
        }
    }
}

void simple_func (int (&a)[n][n],int (&b)[n][n],int (&c)[n][n])
{
    int i, l, j;
    double s = 0;

    for(i=0; i<n; i++) {
        for(l=0; l<n; l++) {
            s = 0;
            for(j=0; j<n; j++) {
                s += a[i][j]*b[j][l];
            }
            c[i][l] = s;
        }
    }
}

int main()
{
        int a[n][n], b[n][n], c[n][n];

        create_random(a);
        create_random(b);
        create_0(c);

        cout << " A = " <<endl;
        show(a);

        cout << " B = " <<endl;
        show(b);


        int A[n][n], B[n][n], C[n][n];

        copy_matr(A, a);
        copy_matr(B, b);
        copy_matr(C, c);

        cout << " strassen_func " << endl;
        clock_t start = clock();
        strassen_func(a, b, c);
        clock_t end = clock();
        cout << " C = " <<endl;
        show(c);
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        printf("time: %f seconds\n", seconds);
        cout << endl;


        cout << " simple_func " << endl;
        start = clock();
        simple_func(A, B, C);
        end = clock();
        cout << " C = " <<endl;
        show(c);
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        printf("time: %f seconds\n", seconds);
        cout << endl;


    return 0;
}
