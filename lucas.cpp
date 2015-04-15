#include<iostream>
using namespace std;
#include<vector>
 
long long SmallC(int n, int r, int MOD)
{
    vector< vector<long long> > C(2,vector<long long> (r+1,0));
 
    for (int i=0; i<=n; i++)
    {
        for (int k=0; k<=r && k<=i; k++)
            if (k==0 || k==i)
                C[i&1][k] = 1;
            else
                C[i&1][k] = (C[(i-1)&1][k-1] + C[(i-1)&1][k])%MOD;
    }
    return C[n&1][r];
}
 
long long Lucas(int n, int m, int p)
{
    if (n==0 && m==0) return 1;
    int ni = n % p;
    int mi = m % p;
    if (mi>ni) return 0;
    return Lucas(n/p, m/p, p) * SmallC(ni, mi, p);
}
 
long long C(int n, int r, int MOD)
{
    return Lucas(n, r, MOD);
}
 

int main()
{
    int n,r,m;
    while (1)
    {
        cout<<"Enter total number of objects:(0 to exit) ";
        cin>>n;
        if (n == 0)
            break;
        cout<<"Enter number of objects to be chosen: ";
        cin>>r;
        cout<<"Enter modular value: ";
        cin>>m;
        cout<<C(n, min(r,n - r), m)<<endl;
    }
}
