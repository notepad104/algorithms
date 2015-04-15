#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
using namespace std;

bool mycomp (char c1, char c2)
{
    return tolower(c1) < tolower(c2);
}

int main ()
{
    int flen, blen;
    char foo[] = "Apple";
    char bar[] = "apartment";
    flen = strlen(foo);
    blen = strlen(bar);
    cout << boolalpha;
    cout << "Comparing foo and bar lexicographically (foo < bar): "<<endl;
    cout << "Using default comparison (operator <): ";
    cout << lexicographical_compare(foo, foo + flen, bar, bar + blen);
    cout <<endl;
    cout << "Using mycomp as comparison object: ";
    cout << lexicographical_compare(foo, foo + flen, bar, bar + blen, mycomp);
    cout <<endl;
    return 0;
}
