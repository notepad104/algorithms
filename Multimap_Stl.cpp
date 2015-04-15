#include <iostream>
#include <map>
#include <string>
using namespace std;
int main ()
{
    multimap<char, int> mymm;
    multimap<char, int>::iterator it;
    mymm.insert (pair<char, int>('x',100));
    mymm.insert (pair<char, int>('y',200));
    mymm.insert (pair<char, int>('y',300));
    mymm.insert (pair<char, int>('y',400));
    mymm.insert (pair<char, int>('z',500));
    mymm.insert (pair<char, int>('z',500));
    cout<<"Size of the multimap: "<<mymm.size()<<endl;
    cout << "Multimap contains:\n";
    for (it = mymm.begin(); it!=mymm.end(); ++it)
        cout << (*it).first << " => " << (*it).second << '\n';
    for (char c='x'; c<='z'; c++)
    {
        cout << "There are " << mymm.count(c) << " elements with key " << c << ":";
        multimap<char, int>::iterator it;
        for (it = mymm.equal_range(c).first; it!=mymm.equal_range(c).second; ++it)
            cout << ' ' << (*it).second;
        cout << endl;
    }
    it = mymm.find('x');
    mymm.erase (it);
    cout<<"Size of the multimap: "<<mymm.size()<<endl;
    // showing contents:
    cout << "Multimap contains:\n";
    for (it = mymm.begin(); it!=mymm.end(); ++it)
        cout << (*it).first << " => " << (*it).second << '\n';
  return 0;
}
