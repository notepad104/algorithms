#include<stdio.h>
#include <iostream>
#define RMAX 20
#define CMAX 20
using namespace std;
void read(int a[][CMAX], int rows, int cols);
void show(int a[][CMAX], int rows, int cols);
void product(int a[][CMAX], int b[][CMAX], int row1, int row2, int col2);

int main()
{
int a[RMAX][CMAX], b[RMAX][CMAX], r1, r2, c1, c2;
printf("array 1");
printf("\nenter current row size:");
scanf("%d", &r1);
printf("\nenter current column size:");
scanf("%d", &c1);

read(a, r1, c1);
show(a, r1, c1);

printf("\narray 2");
printf("\nenter current row size:");
scanf("%d", &r2);
printf("\nenter current column size:");
scanf("%d", &c2);

read(a, r2, c2);
show(a, r2, c2);

if(c1==r2)
{
printf("\ntheir product array is:\n ");
product(a, b, r1, r2, c2);
}
else
{
printf("multiplication is not compatible");
}
return 0;


}

void read(int a[][CMAX], int rows, int cols)
{int i,j;
for(i=0; i<rows; ++i)
{
for(j=0; j<cols; ++j)
{
printf("\nenter element a[%d][%d]", i, j);
scanf("%d", &a[i][j]);
}
}
}

void show(int a[][CMAX], int rows, int cols)
{int i,j;
for(i=0; i<rows; ++i)
{
for(j=0; j<cols; ++j)
{
printf("%d\t", a[i][j]);
}
printf("\n");
}
}

void product(int a[][CMAX], int b[][CMAX], int row1, int row2, int col2)
{
    cout<<a[0][0]<<" "<<b[0][0]<<endl;
int sum,i,j,k,c[row1][col2];
for(i=0; i<row1; ++i)
{
for(k=0; k<col2; ++k)
{
sum= 0;
for(j=0; j<row2; ++j)
{
sum = sum + a[i][j]*b[j][k];

}

c[i][k]=sum;
printf("%d \t",c[i][k]);
}
printf("\n");
}
//show(c,row1,col2);
}

