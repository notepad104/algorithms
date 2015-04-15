/* 
 * C++ Program to Find Fibonnaci Numbers using Dynamic Programming
 */
#include <cstring>
#include <iostream>
#include <cstdlib>
#define ll long long
using namespace std;

ll fib[1000] = {0};

ll fibo_dp(int n)
{
    fib[1] = 1;
    fib[2] = 1;
    if (fib[n] == 0)
    {
        for (int j = 3; j <= n; ++j)
        {
            if (fib[n] == 0)
                fib[j] = fib[j - 1] + fib[j - 2];
            else
                continue;
        }
    }
    return fib[n];
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
        cout<<fibo_dp(n)<<endl;
    }
    return 0;
}
