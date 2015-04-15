/*
 * C++ Program to Convert a Decimal Base to Any Base
 */
#include<iostream>
#include <cstdio>
using namespace std;

//Decima to base conversion 
void convert10tob(int N, int b)
{
     if (N == 0)
        return;
     int x = N % b;
     N /= b;
     if (x < 0)
        N += 1; 
     convert10tob(N, b);
     cout<<x < 0 ? x + (b*-1) : x;
     return;
}
 
//Main
int main()
{
    int N,b;
    cout<<"Enter the integer to convert(N): ";
    cin>>N;
    cout<<"Enter the base <= N: ";
    cin>>b;
    if (N != 0)
    {
        convert10tob(N, b);
        cout<<endl;
    }
    else
        cout<<"0"<<endl;
    return 0;
}
