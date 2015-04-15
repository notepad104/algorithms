/*
 * C++ Program to Implement LRU Cache
 */
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

// A Queue Node (Queue is implemented using Doubly Linked List)
typedef struct QNode
{
    QNode *prev, *next;
    unsigned pageNumber;
} QNode;

// A Queue (A FIFO collection of Queue Nodes)
typedef struct Queue
{
    unsigned count;
    unsigned numberOfFrames;
    QNode *front, *rear;
} Queue;

// A hash (Collection of pointers to Queue Nodes)
typedef struct Hash
{
    int capacity;
    QNode **array;
} Hash;

// A utility function to create a new Queue Node.
QNode* newQNode(unsigned pageNumber)
{
    QNode* temp = new QNode;
    temp->pageNumber = pageNumber;
    temp->prev = temp->next = NULL;
    return temp;
}

// A utility function to create an empty Queue.
Queue* createQueue(int numberOfFrames)
{
    Queue* queue = new Queue;
    queue->count = 0;
    queue->front = queue->rear = NULL;
    queue->numberOfFrames = numberOfFrames;
    return queue;
}

// A utility function to create an empty Hash of given capacity
Hash* createHash(int capacity)
{
    Hash* hash = new Hash;
    hash->capacity = capacity;
    hash->array = new QNode* [hash->capacity];
    int i;
    for(i = 0; i < hash->capacity; ++i)
        hash->array[i] = NULL;
    return hash;
}
void deleteHash(Hash *hash, int capacity, Queue *q)
{
    for(int i = 0; i < hash->capacity; ++i)
        delete hash->array[i];
    delete hash;
    delete q;
}

// A function to check if there is slot available in memory
int AreAllFramesFull(Queue* queue)
{
    return queue->count == queue->numberOfFrames;
}

// A utility function to check if queue is empty
int isQueueEmpty( Queue* queue )
{
    return queue->rear == NULL;
}

// A utility function to delete a frame from queue
void deQueue( Queue* queue )
{
    if (isQueueEmpty(queue))
        return;
    if (queue->front == queue->rear)
        queue->front = NULL;
    QNode* temp = queue->rear;
    queue->rear = queue->rear->prev;
    if (queue->rear)
        queue->rear->next = NULL;
    free(temp);
    queue->count--;
}

// A function to add a page with given 'pageNumber' to both queue and hash
void Enqueue(Queue* queue, Hash* hash, unsigned pageNumber)
{
    if (AreAllFramesFull(queue))
    {
        hash->array[queue->rear->pageNumber] = NULL;
        deQueue(queue);
    }
    QNode* temp = newQNode(pageNumber);
    temp->next = queue->front;
    if (isQueueEmpty(queue))
        queue->rear = queue->front = temp;
    else
    {
        queue->front->prev = temp;
        queue->front = temp;
    }
    hash->array[pageNumber] = temp;
    queue->count++;
}

// This function is called when a page with given 'pageNumber' is referenced
// from cache (or memory).
int ReferencePage(Queue* queue, Hash* hash, unsigned pageNumber)
{
    int c = 0;
    QNode* reqPage = hash->array[pageNumber];
    if (reqPage == NULL)
    {
        c++;
        Enqueue(queue, hash, pageNumber);
    }
    else if (reqPage != queue->front)
    {
        reqPage->prev->next = reqPage->next;
        if (reqPage->next)
           reqPage->next->prev = reqPage->prev;
        if (reqPage == queue->rear)
        {
           queue->rear = reqPage->prev;
           queue->rear->next = NULL;
        }
        reqPage->next = queue->front;
        reqPage->prev = NULL;
        reqPage->next->prev = reqPage;
        queue->front = reqPage;
    }
    return c;
}

// Main
int main()
{
    int n,m,c,t,count, index;
    
    int a[100010];
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>c;
    for(int i =0; i < m ; i++)
    {
        cin>>a[i];
    }
    for(int i = 1; i <= m ; i++)
    {
        count= 0;
        Queue* q = createQueue(i);
        Hash* hash = createHash(n);
        for(int j = 0; j < m ; j++)
        {
            count += ReferencePage(q, hash, a[j]);
        }
        deleteHash(hash, n, q);
        if (count <= c)
        {
            index = i;
            break;
        }
            
    }
    if (count <= c)
    cout<<index<<endl;
    else
    cout<<"-1"<<endl;
    }
    return 0;
}
