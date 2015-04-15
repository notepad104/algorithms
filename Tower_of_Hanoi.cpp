#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;
int count;
ofstream outputfile;
void Tower_of_Hanoi(char start, char end, char intermediate, int n)
{
    count++;
    if (n == 1)
        return;
    Tower_of_Hanoi(start, intermediate , end, n - 1);
    Tower_of_Hanoi(intermediate, end , start, n - 1);
}
int main()
{
    int n;
    outputfile.open("output.txt");
    clock_t startTime ;
    clock_t endTime;
    while (1)
    {
        cout<<"Enter number of disks(0 to exit): ";
        cin>>n;
        if(n == 0)
            break;
        count = 0;
        startTime = clock();
        outputfile<<"Steps for n = "<<n<<endl;
        Tower_of_Hanoi('A', 'C', 'B', n);
        endTime = clock();
        cout<<(endTime - startTime)<<" Clocks..";
        cout<< double(endTime - startTime) / CLOCKS_PER_SEC<<" Secs"<<endl;
        outputfile<<endl<<"Number of steps for n = "<<n<<": "<<count<<endl<<endl;
    }
    return 0;
}
