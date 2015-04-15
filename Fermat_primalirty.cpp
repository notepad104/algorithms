/* 
 * C++ Program to Implement Fermat Primality Test
 */
#include <cstring>
#include <iostream>
#include <cstdlib>
#define ll long long
using namespace std;

ll modulo(ll base,ll exponent,ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

/* Fermat's test for checking primality */
bool Fermat(ll p, int iterations)
{
    if (p == 1)
    {
        return false;
    }
    for (int i = 0; i < iterations; i++)
    {
        ll a = rand() % (p - 1) + 1; 
        if (modulo(a, p - 1, p) != 1)
        { 
            return false;
        }
    }
    return true;
}

int main()
{
    int iteration = 1000000;
    ll num;
    cout<<"Enter integer to test primality: ";
    cin>>num;
    if (Fermat(num, iteration))
        cout<<num<<" is prime"<<endl;
    else
        cout<<num<<" is not prime"<<endl;
    return 0;
}
