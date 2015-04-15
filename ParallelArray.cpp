#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
 
int main()
{
    int i = 0, h = 0, saved = 0; 
    int g[ ] = {87, 99, 70, 75, 77, 91, 95};
    string s [ ]= {"S1", "S2", "S3", "S4", "S5", "S6", "S7"};
    for(i = 0; i < sizeof(g)/sizeof(g[0]); i++)
    {
        if (g[i] > h)
        {
            h = g[i];
            saved = i;
        }
    }
    cout << "Highest marks:" << h << " of Student: " << s[saved]<<endl;
    return 0;
}
