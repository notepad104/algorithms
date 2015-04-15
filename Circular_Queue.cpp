/*
 * C++ Program to Implement Circular Queue
 */
#include <iostream>
#define MAX 5
using namespace std;
/*
 * Class Circular Queue
 */
class Circular_Queue
{
    private:
        int *cqueue_arr;
        int front, rear;
    public:
        Circular_Queue()
        {
            cqueue_arr = new int [MAX];
            rear = front = -1;
        }
        /*
         * Insert into Circular Queue
         */
        void insert(int item)
        {
            if ((front == 0 && rear == MAX-1) || (front == rear+1))
            {
                cout<<"Queue Overflow \n";
                return;
            }
            if (front == -1)
            {
                front = 0;
                rear = 0;
            }
            else
            {
                if (rear == MAX - 1)
                    rear = 0;
                else
                    rear = rear + 1;
            }
            cqueue_arr[rear] = item ;
        }
        /*
         * Delete from Circular Queue
         */
        void del()
        {
            if (front == -1)
            {
                cout<<"Queue Underflow\n";
                return ;
            }
            cout<<"Element deleted from queue is : "<<cqueue_arr[front]<<endl;
            if (front == rear)
            {
                front = -1;
                rear = -1;
            }
            else
            {
                if (front == MAX - 1)
                    front = 0;
                else
                    front = front + 1;
            }
        }
        /*
         * Display Circular Queue
         */
        void display()
        {
            int front_pos = front, rear_pos = rear;
            if (front == -1)
            {
                cout<<"Queue is empty\n";
                return;
            }
            cout<<"Queue elements :\n";
            if (front_pos <= rear_pos)
            {
                while (front_pos <= rear_pos)
                {
                    cout<<cqueue_arr[front_pos]<<"  ";
                    front_pos++;
                }
            }
            else
            {
                while (front_pos <= MAX - 1)
                {
                    cout<<cqueue_arr[front_pos]<<"  ";
                    front_pos++;
                }
                front_pos = 0;
                while (front_pos <= rear_pos)
                {
                    cout<<cqueue_arr[front_pos]<<"  ";
                    front_pos++;
                }
            }
            cout<<endl;
        }
};
/*
 * Main
 */
int main()
{
	int choice, item;
	Circular_Queue cq;
    do
	{
		cout<<"1.Insert\n";
		cout<<"2.Delete\n";
		cout<<"3.Display\n";
		cout<<"4.Quit\n";
		cout<<"Enter your choice : ";
		cin>>choice;
		switch(choice)
		{
		case 1:
            cout<<"Input the element for insertion in queue : ";
            cin>>item;
			cq.insert(item);
			break;
		case 2:
			cq.del();
			break;
		case 3:
			cq.display();
			break;
		case 4:
			break;
		default:
			cout<<"Wrong choice\n";
		}/*End of switch*/
	}
	while(choice != 4);
    return 0;
}
