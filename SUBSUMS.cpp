#include <iostream>
#include <cstdio>
using namespace std;
int isSubsetSum(int set[], int n,int a, int sum){
    bool subset[sum + 1][n + 1];
    for(int i = 0; i<= n; i++){
        subset[0][i] = true;
    }
    for(int i = 0; i<= sum; i++){
        subset[i][0] = false;
    }
    for (int i = 1; i <= sum; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            subset[i][j] = subset[i][j-1];
            if (i >= set[j-1])
                subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
        }
    }
    int c = 0;
    for (int i = a; i <= sum; i++)
    {
           if (subset[i][n] == true)
                c++;       
    }
    return c;
}
int main(){
    int n,a,b,i,s[35],mins = 0, min = 20000001,maxs =0 ,max = -20000001;
    scanf("%d %d %d",&n,&a,&b);
    for(i = 0; i < n; i++){
        scanf("%d",&s[i]);
        if (s[i] > 0)
            maxs += s[i];
        if (s[i] > max)
            max = s[i];
        if (s[i] < min)
            min = s[i];
        if (s[i] < 0)
            mins += s[i];
    }
    if (mins == 0)
        mins = min;
    if (maxs == 0)
        maxs = max;
    if (a < mins && b > mins)
        a = mins;
    if (b > maxs && a < maxs)
        b = maxs;
    cout<<a<<" "<<b<<endl;
    if (b < mins || a > maxs)
        cout<<"1"<<endl;
    else
        cout<<isSubsetSum(s, n, a, b) + 1<<endl; 
}
