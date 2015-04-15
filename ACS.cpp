#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
int main(){
    int x,y,z,i,flagr,flagc,cx,cy;
    map<int, int> r, c;
    map<int, int>::iterator it,it1;
    for(i = 0 ; i < 5680; i++){
        if (i < 1236){
            r.insert(make_pair(i,i));
        }
        c.insert(make_pair(i,i));
    }
    char a;
    while(scanf("%c",&a) != EOF){
        flagr = 0,flagc = 0;
        if (a == 'R'){
            scanf("%d",&x);
            scanf("%d",&y);
            swap(r[x], r[y]);
            
        }
        
        else if(a == 'C'){
            scanf("%d",&x);
            scanf("%d",&y);
            swap(c[x], c[y]);
        }
        else if (a == 'Q'){
            scanf("%d",&x);
            scanf("%d",&y);
            cx = x;
            cy = y;
            while(c[y] != cx && c[y] != cy){
                y = c[y];
                flagc  = 1;
            }
            while(r[x] != cy && r[x] != cx){
                x = r[x];
                flagr = 1;
            }
            if (flagr == 0)
                x = r[x];
            if (flagc == 0)
                y = c[y];
                
            x = y + 5678 * (x - 1);
            cout<<x<<endl;
        }
        else if(a == 'W'){
            scanf("%d",&z);
            y = 1;
            flagr = 0;
            flagc = 0;
            while ((z - y) % 5678 != 0){
                y++;
            }
            x = (z - y)/ 5678;
            x = x + 1;
            cx = x;
            cy = y;
            while(c[y] != cx && c[y] != cy){
                y = c[y];
                flagc = 1;
            }
            while(r[x] != cy && r[x] != cx){
                x = r[x];
                flagr = 1;
            }
            if (flagr == 0)
                x = r[x];
            if (flagc == 0)
                y = c[y];
            cout<<x<<" "<<y<<endl;
        }
    }
}
