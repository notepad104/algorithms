/*
 * C++ Program to Implement Fermat's Little Theorem
 */
#include <iostream>
using namespace std;

/* calculates (a^b)%MOD */
int pow(int a, int b, int MOD) 
{
    int x = 1, y = a;
    while (b > 0) 
    {
        if (b % 2 == 1) 
        {
            x = (x * y);
            if (x > MOD) 
                x %= MOD;
        }
        y = (y * y);
        if (y > MOD) 
            y %= MOD;
        b /= 2;
    }
    return x;
}
 
int modInverse(int a, int m) {
    return pow(a,m-2,m);
}
//Main
int main()
{
    int a, m;
    cout<<"Enter number to find modular multiplicative inverse: ";
    cin>>a;
    cout<<"Enter Modular Value: ";
    cin>>m;
    cout<<modInverse(a, m)<<endl;
}
