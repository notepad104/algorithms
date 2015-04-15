#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int main(){
    int t,l,i,flag;
    char a[100010],b;
    scanf("%d",&t);
    vector<char> v;
    while(t--){
        flag = 0;
        v.clear();
        scanf("%s",a);
        l = strlen(a);
        b = a[0];
        i = 1;
        v.push_back(b);
        while(i < l){
            if (b == a[i]){
                i++;
            }       
            else{
                b = a[i];
                i++;
                v.push_back(b);
            }     
        }
        l = v.size();
        for(i = 0; i < l / 2; i++){
            if (v[i] != v[l - i - 1]){
                cout<<"NO"<<endl;
                flag = 1;
                break;
            }
        }
        if(flag == 0)
            cout<<"YES"<<endl;
    }
    
}
