/* 
 * C++ Program to Implement Euler Theorem
 */
#include <iostream>
#include <vector>
using namespace std;

vector<int> inverseArray(int n, int m) 
{
    vector<int> modInverse(n + 1, 0);
    modInverse[1] = 1;
    for(int i = 2; i <= n; i++) {
        modInverse[i] = (-(m/i) * modInverse[m % i]) % m + m;
    }
    return modInverse;
}
//Main
int main()
{
    vector<int>::iterator it;
    int a, m;
    cout<<"Enter number to find modular multiplicative inverse: ";
    cin>>a;
    cout<<"Enter Modular Value: ";
    cin>>m;
    cout<<inverseArray(a, m)[a]<<endl;
}
