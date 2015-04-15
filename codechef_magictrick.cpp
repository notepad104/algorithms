#include <iostream>
#include <set>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <cstring>
using namespace std;
long long modmup(long long a, long long b, long long m )
{
    if (a > m)
        a = a % m;
    if (b > m)
        b = b % m;
    long long ret = 0;
    if (a < b)
        swap(a, b);
    while (b)
    {
        while (a < m)
        {
            if(b & 1)
                ret += a;
            a <<= 1;
            b >>= 1;
        }
        a -= m;
        while (ret >= m)
            ret -= m;
        if (a < b)
            swap(a, b);
    }
    return ret;
}
int main() {
	int t,n,i,k,j;
	long long a,b,c, l[1010],temp;
	string s;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(i = 0; i< n;i++){
			scanf("%lld",&l[i]);
		}
		scanf("%lld",&a);
		scanf("%lld",&b);
		scanf("%lld",&c);
		cin>>s;
		for(i = 0; i< n; i++){
			if(s[i] == 'M')
				for(j = i; j < n; j++){
					l[j] = modmup(l[j], b , c);
				}
			else if(s[i] == 'A'){
				for(j = i; j < n; j++){
					l[j] = (l[j] % c + a % c) % c;
				}
			}
			else if(s[i] == 'R'){
				k = 1;
				for(j = i; j <= (n + i)/2; j++){
					temp = l[j] % c;
					l[j] = l[n - k] % c;
					l[n - k] = temp;
					k++;
				}
			}
		}
		for(i = 0; i< n - 1; i++)
			cout<<l[i] % c<<" ";
		cout<<l[n -1] % c<<endl;
	}
	return 0;
}
