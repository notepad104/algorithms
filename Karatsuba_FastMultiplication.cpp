#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
using namespace std;

int makeEqualLength(string &str1, string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            str2 = '0' + str2;
    }
    return len1;
}

// The main function that adds two bit sequences and returns the addition
string addBitStrings(string first, string second)
{
    string result;
    int length = makeEqualLength(first, second);
    int carry = 0;
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = first.at(i) - '0';
        int secondBit = second.at(i) - '0';
        int sum = (firstBit ^ secondBit ^ carry)+'0';
        result = (char)sum + result;
        carry = (firstBit&secondBit) | (secondBit&carry) | (firstBit&carry);
    }
    if (carry)
        result = '1' + result;
    return result;
}

// A utility function to multiply single bits of strings a and b
int multiplyiSingleBit(string a, string b)
{
    return (a[0] - '0')*(b[0] - '0');
}

// multiplies two bit strings X and Y and returns result as long integer
long int multiply(string X, string Y)
{
    string s;
    int n = makeEqualLength(X, Y);
    if (n == 0)
        return 0;
    if (n == 1)
        return multiplyiSingleBit(X, Y);
    int fh = n/2;
    int sh = (n - fh);
    string Xl = X.substr(0, fh);
    string Xr = X.substr(fh, sh);
    string Yl = Y.substr(0, fh);
    string Yr = Y.substr(fh, sh);
    long int P1 = multiply(Xl, Yl);
    long int P2 = multiply(Xr, Yr);
    long int P3 = multiply(addBitStrings(Xl, Xr), addBitStrings(Yl, Yr));
    s = itoa(P1*(1<<(2 * sh)) + (P3 - P1 - P2) * (1<<sh) + P2);
    return s;
}

int main()
{
    cout<<multiply("1100", "1010")<<endl;
    cout<<multiply("110", "1010")<<endl;
    cout<<multiply("11", "1010")<<endl;
    cout<<multiply("1", "1010")<<endl;
    cout<<multiply("0", "1010")<<endl;
    cout<<multiply("111", "111")<<endl;
    cout<<multiply("11", "11")<<endl;
}
