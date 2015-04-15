/*
 * C++ Program To Implement Vlist
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
/*
 * Sublist Declaration
 */
struct sublist
{
    struct sublist* next;
    int *buf;
};
/*
 * Vlist Node Declaration
 */
typedef struct vlist_t 
{
    sublist* head;
    int last_size, ofs;
}*vlist;
/*
 * Vlist Class Declaration
 */
class v_list
{
    public:
        sublist *sublist_new(int);
        vlist v_new();
        void v_del(vlist);
        int v_size(vlist);
        int* v_addr(vlist, int);
        int v_elem(vlist, int);
        int* v_unshift(vlist, int);
        int v_shift(vlist);
        v_list()
        {}
};

/*
 * Main:Conatins Menu
 */
int main()
{
    int i, x, choice;
    v_list vl;
    vlist v = vl.v_new();
    while (1)
    {
        cout<<"\n------------------"<<endl;
        cout<<"Operations on Vlist "<<endl;
        cout<<"\n------------------"<<endl;
        cout<<"1.Insert Element to the front of Vlist"<<endl;
        cout<<"2.Compute length of Vlist"<<endl;
        cout<<"3.Find k-th Element"<<endl;
        cout<<"4.Remove Element from Vlist"<<endl; 
        cout<<"5.Display Vlist Elements"<<endl;
        cout<<"6.Quit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        cout<<endl;
        switch(choice)
        {
        case 1:
            cout<<"Enter element to be inserted: ";
            cin>>x;
            vl.v_unshift(v, x);
            break;
        case 2:
            cout<<"Size of Vlist: "; 
            cout<<vl.v_size(v)<<endl;
            break;
        case 3:
            cout<<"Enter position of element to locate: ";
            cin>>x;
            if (x > vl.v_size(v))
                cout<<"Position out of range"<<endl;
            else
			    cout<<"Element at position "<<x<<": "<<vl.v_elem(v, x - 1)<<endl;
            break;
        case 4:
			cout<<"Element Removed: "<<vl.v_shift(v)<<endl;   
			break;
		case 5:
			cout<<"Displaying Elements of Vlist"<<endl;
			for (i = 0;i < vl.v_size(v);i++)
			    cout<<vl.v_elem(v, i)<<" ";
			cout<<endl;
			break;  
        case 6:
            exit(1);
            break;
        default:
            cout<<"Wrong Choice"<<endl;
        }
    }
	vl.v_del(v);
	return 0;
}

/*
 * Creating new sublist
 */
sublist *v_list::sublist_new(int s)
{
    sublist* sub = (sublist *)malloc(sizeof(sublist) + sizeof(int) * s);
    sub->buf = (int*)(sub + 1);
    sub->next = 0;
    return sub;
}
/*
 * Creating Vlist from Sublist
 */
vlist v_list::v_new()
{
    vlist v = new(vlist_t);
    v->head = sublist_new(1);
    v->last_size = 1;
    v->ofs = 0;
    return v;
}

/*
 * Deleting Vlist
 */
void v_list::v_del(vlist v)
{
    sublist *s;
    while (v->head) 
    {
        s = v->head->next;
        free(v->head);
        v->head = s;
    }
    free(v);
}

/*
 * Compute Length of Vlist
 */
int v_list::v_size(vlist v)
{
    return v->last_size * 2 - v->ofs - 2;
}

int *v_list::v_addr(vlist v, int idx)
{
    sublist *s = v->head;
    int top, i;
    top = v->last_size; 
    i = idx + v->ofs;
	if (i + 2 >= (top << 1)) 
    {
        cout<<"!: idx "<<idx<<" out of range"<<endl;
        abort();
    }
    while (s && i >= top) 
    {
        s = s->next;
        i ^= top;
        top >>= 1;
    }
    return s->buf + i;
}

/*
 * Locate Element at any position in the Vlist 
 */
int v_list::v_elem(vlist v, int idx)
{
    return *v_addr(v, idx);
}

/*
 * Add Element in the Vlist 
 */
int *v_list::v_unshift(vlist v, int x)
{
    sublist* s;
    int *p;
    if (!v->ofs) 
    {
        if (!(s = sublist_new(v->last_size << 1))) 
        {
            cout<<"allocation failure"<<endl;
            return 0;
        }
        v->ofs = (v->last_size <<= 1);  
        s->next = v->head;
        v->head = s;
    }
    *(p = v->head->buf + --v->ofs) = x;
    return p;
}

/*
 * Remove Element from the Vlist 
 */
int v_list::v_shift(vlist v)
{
    sublist* s;
    int x;
    if (v->last_size == 1 && v->ofs == 1) 
    {
        cout<<"empty list"<<endl;
        abort();
    }
    x = v->head->buf[v->ofs++];
    if (v->ofs == v->last_size) 
    {
        v->ofs = 0;
        if (v->last_size > 1) 
        {
            s = v->head;
            v->head = s->next;
            v->last_size >>= 1;
            free(s);
        }
    }
    return x;
}
