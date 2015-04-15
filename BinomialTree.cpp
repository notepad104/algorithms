/*
 * C++ Program to Implement Binomial Tree
 */
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
/*
 * Node Declaration
 */
struct Node
{
    double price, time, optionvalue;
};
/*
 * Class Declaration
 */
class BinomialTree
{
    private:
        Node **tree;
        int n;
        double S, volatility, upfactor, tfin, tstep;
        double getValue(int level, int node, double K, double R);
        void initNode (int level, int node);
    public:
        BinomialTree(double S, double volatility, int n, double tstep);
        double getValue(double K, double R);
        void print();
};
/*
 * Constructor
 */
BinomialTree::BinomialTree(double price , double vol, int _n, double _tstep)
{
    n = _n;
    S = price;
    volatility = vol;
    tstep = _tstep;
    tfin = n * tstep;
    upfactor = exp (volatility * sqrt (tstep));
    tree = new Node * [n];
    for (int i = 0; i < n; i++)
        tree[i] = new Node [i+1] ;
    tree[0][0].price = S;
    tree[0][0].time = 0.0;
    double currtime = 0.0;
    for (int i = 1; i < n; i++)
    {
        Node * currnode = tree[i];
        currtime += tstep;
        for (int j = 0; j <= i; j++, currnode++)
        {
            if (!j)
            {
                currnode->price = tree[i-1][j].price / upfactor ;
                currnode->time = currtime;
            }
            else
            {
                currnode->price = tree[i-1][j-1].price * upfactor ;
                currnode->time = currtime;
            }
        }
    }
}
/*
 * Get Value Function
 */
double BinomialTree::getValue(int l, int node, double K, double df)
{
    if (l == (n-1))
    {
        if (K < tree[l][node].price)
            return tree[l][node].optionvalue = tree[l][node].price - K;
        else
            return tree[l][node].optionvalue = 0.0;
    }
   else
   {
      double g1 = getValue(l + 1, node + 1, K, df);
      double g2 = getValue(l + 1, node, K, df);
      return tree[l][node].optionvalue = 0.5 * df * (g1 + g2);
   }
}

/*
 * Get Value Function
 */
double BinomialTree::getValue(double K, double R)
{
    double discountfactor = exp (-R * tstep);
    return getValue(0, 0, K, discountfactor);
}
/*
 * Display optimal values
 */
void BinomialTree::print()
{
    for (int i = 0; i < n; i++)
    {
        for( int j = 0; j <= i; j++ )
        {
            cout<< "[" << tree[i][j].price << "," << tree[i][j].time << ",";
            cout<< tree[i][j].optionvalue << "]\t";
        }
        cout <<endl;
   }
}
/*
 * Main Contains Menu
 */
int main()
{
    double S, V, K, T, R, N;
    cout<<"Enter Security Price: ";
    cin>>S;
    cout<<"Enter Volatility: ";
    cin>>V;
    cout<<"Enter Call Strike Price: ";
    cin>>K;
    cout<<"Enter Time To Expiry: ";
    cin>>T;
    cout<<"Enter Risk Free Rate: ";
    cin>>R;
    cout<<"Enter levels: ";
    cin>>N;
    BinomialTree bt(S, V, N, T / N);
    double value = bt.getValue(K, R);
    bt.print();
    cout<< "OPTION VALUE = " << value <<endl;
    return 0;
}

/*
Enter Security Price: 10
Enter Volatility: 0.5
Enter Call Strike Price: 100
Enter Time To Expiry: 5
Enter Risk Free Rate: 0.6
Enter levels: 3
[10,0,0]
[5.24402,1.66667,0]     [19.0693,1.66667,0]
[2.74997,3.33333,0]     [10,3.33333,0]  [36.364,3.33333,0]
OPTION VALUE = 0

Process returned 0 (0x0)   execution time : 14.829 s
Press any key to continue.

 */
