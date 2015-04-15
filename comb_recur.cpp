/* 
 * C++ Program to Compute Combinations using Recurrence Relation for nCr
 */
#include<iostream>
#include<vector>
#define ll long long
using namespace std;

ll C(int n, int r)
{
    vector< vector<ll> > C(2,vector<ll> (r + 1,0));
 
    for (int i = 0; i <= n; i++)
    {
        for (int k = 0; k <= r && k <= i; k++)
            if (k == 0 || k == i)
                C[i&1][k] = 1;
            else
                C[i & 1][k] = (C[(i - 1) & 1][k - 1] + C[(i - 1) & 1][k]);
    }
    return C[n & 1][r];
}
//Main 
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
        cout<<"Number of Combinations: "<<C(n, min(r, n - r))<<endl;
    }
}
