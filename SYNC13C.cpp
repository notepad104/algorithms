#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int main(){
    int t, n, a, b,c, i;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&a);
        scanf("%d",&b);
        if (a%2 != 0 && b%2 != 0){
            cout<<"Ramesh"<<endl;
        }
        else
            cout<<"Suresh"<<endl;
    }
    return 0;   
}
