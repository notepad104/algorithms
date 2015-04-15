#include <iostream>
#include <cstdio>
using namespace std;
int sum_digits(long long int a){
    int sum = 0;
    while(a > 0){
        sum = sum + (a % 10);
        a = a / 10;
    }
    return sum;
}
int main(){
    int t;
    long long int a;
    scanf("%d",&t);
    while(t--){
        scanf("%lld",&a);
        while (a % sum_digits(a) != 0){
            a++;
        }
        cout<<a<<endl;
    }
}
