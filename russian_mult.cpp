/* 
 * C++ Program to Implement Russian Peasant Multiplication 
 */
#include <iostream>
using namespace std;
 
// multiply two numbers using Russian Peasant method
unsigned int russianPeasant(unsigned int a, unsigned int b)
{
    int res = 0;
    while (b > 0)
    {
         if (b & 1)
             res = res + a;
         a = a << 1;
         b = b >> 1;
     }
     return res;
}
 
// Main
int main()
{
    cout << russianPeasant(15, 5) << endl;
    cout << russianPeasant(13, 6) << endl;
    return 0;
}
