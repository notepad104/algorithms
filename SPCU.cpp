#include <iostream>
#include <cstdio>
using namespace std;
int main(){
    int t, n, a[100010],c, i;
    scanf("%d",&t);
    while(t--){
        c = 0;
        scanf("%d",&n);
        for(i = 0 ; i < n; i++){
            scanf("%d",&a[i]);
            if (a[i] > i){
                c++;
            }
        }
        if (c != 0)
            cout<<"NO"<<endl;
        else
            cout<<"YES"<<endl;
    }
    return 0;   
}
