#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main ()
{
    int f[] = {5,10,15,20,25};
    int s[] = {50,40,30,20,10};
    vector<int> v(10);
    vector<int>::iterator it;
    sort (f, f + 5);
    sort (s, s + 5);
    it = set_symmetric_difference(f, f + 5, s, s + 5, v.begin());
    v.resize(it - v.begin());
    cout<<"The symmetric difference has "<< (v.size())<< " elements: "<<endl;
    for (it = v.begin(); it != v.end(); ++it)
        cout<< *it<<"  ";
    cout <<endl;
    return 0;
}
