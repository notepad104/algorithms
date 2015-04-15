#include<iostream>
#include<cstdio>
#include <cmath>
#include <map>
using namespace std;
int main(){
    map< int, pair<long long int, int> >a;
    map< int, pair<long long int, int> >::iterator it, it1;
    a.clear();
    a.insert(make_pair(1, make_pair(1, 0)));
    int q;
    for(int i = 1; i < 500005; i++){
        it = a.find(i);
        if(it->second.second == 0){
            a.insert(make_pair(2 * i, make_pair((it->second.first) * 2, 1)));
            a.insert(make_pair(2 * i + 1, make_pair((it->second.first) * 4, 0)));    
        }
        else{
            a.insert(make_pair(2 * i, make_pair((it->second.first) * 2, 1)));
            a.insert(make_pair(2 * i + 1, make_pair((it->second.first) * 2, 0)));
        }
    }
    int t,i,x,y,w;
    scanf("%d",&t);
    double ans;
    while(t--){
        scanf("%d",&x);
        scanf("%d",&y);
        scanf("%d",&w);
        it = a.find(x);
        it1= a.find(y);
        ans = (double)w * (it->second.first)/ (double)it1->second.first; 
        printf("%.6lf\n",ans);
    }
}
