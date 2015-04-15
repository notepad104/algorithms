#include <iostream>
#include <string>
#include <functional>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;
class node
{
    public:
        node *lft, *rgt;
        int hgt;
        int lbl;
        int *val;
};
class tree
{
    friend class map;
    public:
        tree();
        tree(int (*cmp)(const int &, const int &));
        ~tree();
};

class map
{
    private:
        tree **tbl;
        double lbf;
        int sze, cur;
        void lfb(node *&ptr, int l);
        int (*cmp)(const int &, const int &);
    public:
        map(int (*cmp)(const int &, const int &));
        ~map();
        int *get(const int &lbl);
        int *operator[](const int &lbl);
        bool ins(const int &lbl, const int &val);
        bool del(const int &lbl);
        int cnt(const int &lbl);
        void clr();
};

map::map(int (*cmp)(const int &, const int &))
{
    sze = 1, cur = 0, lbf = 0;
    this->cmp = cmp;
    tbl = new tree *[sze];
    for (int i = 0; i < sze; ++i)
        tbl[i] = new tree(cmp);
}

map::~map()
{
    for (int i = 0; i < sze; ++i)
        delete tbl[i];
    delete[] tbl;
}


bool map::ins(const int &lbl, const int &val)
{
    lbf = cur / sze;
    if (lbf >= 1)
    {
        int t = sze;
        sze *= 10;
        tbl = (tree**)realloc(tbl, sizeof(tree)*sze);
        if (!tbl)
            return 2;
        for (int i = t; i < sze; ++i)
        {
            tbl[i] = new tree(cmp);
        }
        for (int i = 0; i < t; ++i)
            lfb(tbl[i]->rt, i);
    }
    int h = lbl / sze;
    h = lbl - (sze * h);
    bool r = tbl[h]->ins(lbl, val);
    cur += r;
    return r;
}


void map::lfb(node *&ptr, int l)
{
    if (!ptr)
        return;
    if (ptr->lft)
        lfb(ptr->lft, l);
    if (ptr->rgt)
        lfb(ptr->rgt, l);
    int &lbl = ptr->lbl;
    int &val = *ptr->val;
    int h = lbl % sze;
    if (h != l)
    {
        tbl[h]->ins(lbl, val);
        tbl[l]->del(lbl);
    }
}
bool htree::map::del(const int &lbl)
{
    int h = lbl % sze;
    if (!tbl[h]->rt)
        return 0;
    bool r = tbl[h]->del(lbl);
    cur -= r;
    return r;
}

int htree::map::cnt(const int &lbl)
{
    int h = lbl % sze;
    if (!tbl[h]->rt)
        return 0;
    return tbl[h]->cnt(lbl);
}

int *htree::map::get(const int &lbl)
{
    int h = lbl % sze;
    if (!tbl[h]->rt)
        return 0;
    return tbl[h]->get(lbl);
}

int *htree::map::operator[](const int &lbl)
{
    return get(lbl);
}

void htree::map::clr()
{
    for (int i = 0; i < sze; ++i)
        tbl[i]->clr();
}

int cmp(const string &a, const string &b)
{
    return b.compare(a);
}

class foo
{
    public:
        int id;
        double mass;
};

int icmp(const int &a, const int &b)
{
    return a < b ? -1 : a == b ? 0 : 1;
}

int main()
{
    htree::map ht(cmp);
    if (ht.ins(100, 1) == 1)
        cout<<"successful insertion"<<endl;
    ht.ins(200, 2);
    ht.ins(300, 3);
    printf("%d\n", ht.cnt(100));
    printf("%d\n", *ht.get(100));
    if (ht.ins(100, 6) == 2);
    printf("%d\n", *ht.get(100));
    printf("%d\n", *ht[200]);
    printf("\n\n\n%d\n\n\n", ht.del(100));
    printf("%d\n", ht.cnt("Hello"));
    ht.clr(); // prune items
    if (ht.get("Test"))
    printf("%d\n", *ht["Test"]);
    htree::map<std::string, foo> fct(cmp);
    foo a, b, c, d;
    a.id = 0;
    b.id = 1;
    c.id = 2;
    c.mass = 2.3;
    d.id = 3;
    fct.ins("Test", a);
    fct.ins("Hi", b);
    fct.ins("Foo", c);
    fct.ins("Foobar", d);
    printf("%f\n", fct.get("Foo")->mass);
    fct.ins("Test", c);
    printf("%f\n", fct.get("Test")->mass);
    htree::map<int, std::string> ict(icmp);
    ict.ins(0, "a");
    ict.ins(2, "b");
    ict.ins(4, "c");
    printf("%s\n", ict.get(2)->c_str());
    return 0;
}
