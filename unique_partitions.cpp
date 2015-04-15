/* 
 * C++ Program to Generate All Unique Partitions of an Integer 
 */
#include<iostream>
using namespace std;
 
// print an array p[] of size 'n'
void printArray(int p[], int n)
{
    for (int i = 0; i < n; i++)
       cout << p[i] << " ";
    cout << endl;
}
 
void printAllUniqueParts(int n)
{
    int p[n];
    int k = 0;
    p[k] = n;
    while (true)
    {
        printArray(p, k + 1);
        int rem_val = 0;
        while (k >= 0 && p[k] == 1)
        {
            rem_val += p[k];
            k--;
        }
        if (k < 0)  
            return;
        p[k]--;
        rem_val++;
        while (rem_val > p[k])
        {
            p[k+1] = p[k];
            rem_val = rem_val - p[k];
            k++;
        }
        p[k+1] = rem_val;
        k++;
    }
}
 
// Main
int main()
{
    int value;
    while(1)
    {
        cout<<"Enter an Integer(0 to exit): ";
        cin>>value;
        if (value == 0)
           break;
        cout << "All Unique Partitions of "<<value<<endl;
        printAllUniqueParts(value);
        cout<<endl;
    }
    return 0;
}
