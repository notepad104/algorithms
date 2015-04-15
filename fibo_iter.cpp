/* 
 * C++ Program to Find Fibonnaci Numbers using Iteration
 */
#include <cstring>
#include <iostream>
#include <cstdlib>
#define ll long long
using namespace std;

ll fibo_iter(int n)
{
    int previous = 1;
    int current = 1;
    int next = 1;
    for (int i = 3; i <= n; ++i) 
    {
        next = current + previous;
        previous = current;
        current = next;
    }
    return next;
}
//Main
int main()
{
    int n;
    while (1)
    {
        cout<<"Enter the integer n to find nth fibonnaci no.(0 to exit): ";
        cin>>n;
        if (n == 0)
            break;
        cout<<fibo_iter(n)<<endl;
    }
    return 0;
}
