#include<iostream>
#include<vector>
using namespace std;

int modInverse(int a, int m) 
{
    a %= m;
    for(int x = 1; x < m; x++) 
    {
        if((a*x) % m == 1) 
            return x;
    }
}

int main()
{
    int a, m;
    cout<<"Enter number to find modular multiplicative inverse: ";
    cin>>a;
    cout<<"Enter Modular Value: ";
    cin>>m;
    cout<<modInverse(a, m)<<endl;
}
