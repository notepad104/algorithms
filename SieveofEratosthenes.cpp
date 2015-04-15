/* 
 * C++ Program to Implement Sieve of Eratosthenes
 */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// marks all mutiples of 'a' as 1.
void markMultiples(bool arr[], int a, int n)
{
    int i = 2, num;
    while ((num = i*a) <= n)
    {
        arr[num - 1] = 1;
        ++i;
    }
}

// Aprint all prime numbers smaller than n
void SieveOfEratosthenes(int n)
{
    if (n >= 2)
    {
        bool arr[n];
        memset(arr, 0, sizeof(arr));
        for (int i = 1; i < n; ++i)
        {
            if (arr[i] == 0)
            {
                cout<<i + 1<<"  ";
                markMultiples(arr, i + 1, n);
            }
        }
    }
}

// Main
int main()
{
    int n = 30;
    cout<<"Following are the prime numbers below "<<n<<endl;
    SieveOfEratosthenes(n);
    return 0;
}
