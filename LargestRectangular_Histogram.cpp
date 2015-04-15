/* 
 * C++ Program to Find Largest Rectangular Area in a Histogram
 */
#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>
#define max(x, y, z) max(max(x, y) , z)
using namespace std;
 
// get minimum of two numbers in hist[]
int minVal(int *hist, int i, int j)
{
    if (i == -1) 
        return j;
    if (j == -1) 
        return i;
    return (hist[i] < hist[j])? i : j;
}
 
// get the middle index from corner indexes.
int getMid(int s, int e)
{   
    return s + (e -s)/2; 
}
 
/*  get the index of minimum value in a given range of indexes. */
int RMQUtil(int *hist, int *st, int ss, int se, int qs, int qe, int index)
{
    if (qs <= ss && qe >= se)
        return st[index];
    if (se < qs || ss > qe)
        return -1;
    int mid = getMid(ss, se);
    return minVal(hist, RMQUtil(hist, st, ss, mid, qs, qe, 2 * index + 1),
                  RMQUtil(hist, st, mid + 1, se, qs, qe, 2 * index + 2));
}
 
// Return index of minimum element in range from index qs to qe
int RMQ(int *hist, int *st, int n, int qs, int qe)
{
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        cout << "Invalid Input";
        return -1;
    }
    return RMQUtil(hist, st, 0, n-1, qs, qe, 0);
}
 
// constructs Segment Tree for hist[ss..se].
int constructSTUtil(int hist[], int ss, int se, int *st, int si)
{
    if (ss == se)
       return (st[si] = ss);
    int mid = getMid(ss, se);
    st[si] =  minVal(hist, constructSTUtil(hist, ss, mid, st, si * 2 + 1),
                     constructSTUtil(hist, mid + 1, se, st, si * 2 + 2));
    return st[si];
}
 
/* construct segment tree from given array. */
int *constructST(int hist[], int n)
{
    int x = (int)(ceil(log2(n))); 
    int max_size = 2 * (int)pow(2, x) - 1;
    int *st = new int[max_size];
    constructSTUtil(hist, 0, n - 1, st, 0);
    return st;
}
 
//find the maximum rectangular area.
int getMaxAreaRec(int *hist, int *st, int n, int l, int r)
{
    if (l > r) 
        return INT_MIN;
    if (l == r)  
        return hist[l];
    int m = RMQ(hist, st, n, l, r);
    return max(getMaxAreaRec(hist, st, n, l, m - 1), 
                getMaxAreaRec(hist, st, n, m + 1, r), (r - l + 1) * (hist[m]));
}
 
//find max area
int getMaxArea(int hist[], int n)
{
    int *st = constructST(hist, n);
    return getMaxAreaRec(hist, st, n, 0, n - 1);
}
 
// Main
int main()
{
    int hist[] =  {6, 1, 5, 4, 5, 2, 6};
    int n = sizeof(hist)/sizeof(hist[0]);
    cout << "Maximum area is " << getMaxArea(hist, n)<<endl;
    return 0;
}
