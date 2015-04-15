#include <iostream>
using namespace std;

int main()
{
    int a[100010], co[100010],t,n,m,c,x,i,j,lo,hi,mid;
    cin>>t;
    while(t--){
        cin>>n>>m>>c;
        for(i = 1 ;i <= m; i++){
            cin>>a[i];
        }
        lo = 1;
        hi = n;
        while(lo< hi){
            mid = (lo + hi)/2;
            for(i = 0; i<= m;i++){
                co[a[i]] = 0;
            }
            j = 1;
            x = 0;
            for(i = 1; i <= m;i++){
                if (co[a[i]] == 0){
                    co[a[i]] = 1;
                    x++;
                    if(x > mid){
                        co[a[j]] = 0;
                        j++;
                    }
                }
            }
            if (x <= c)
                hi = mid;
            else
                lo = mid + 1;
            if (lo == hi)
                break;
        }
        mid = (lo + hi)/2;
        if (mid > c)
            cout<<"-1"<<endl;
        else
            cout<<mid<<endl;
    }
    
}
