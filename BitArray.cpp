/*
 * C++ Program to Implement Bit Array
 */
#include <iostream>
#include <string>
using namespace std;
#define BIT_ARRAY_LENGTH 4

typedef struct 
{
    unsigned int bit : 1;
} Bit;

/*
 * Bit Array Class 
 */
class BitArray
{
    private:
        Bit **bitValues;
    public:
        BitArray()
        {
            bitValues =  new Bit* [BIT_ARRAY_LENGTH];
        }
        /*
         * Return Bit at a position
         */
        Bit *getBit(int value,int position)
        {
            Bit *singleBit = new Bit;
            singleBit->bit = 0;
            if(position == 0) 
            {
                singleBit->bit = value & 1;
            }
            else 
            {
                singleBit->bit = ( value & (1 << position ) ) >> position;
            }
            return singleBit;
        }
        /*
         * Set Bit at a position
         */
        BitArray *setBit(BitArray *bt,Bit *bit,int position)
        {
            bt->bitValues[position] = bit;
            return bt;
        }
        /*
         * Return value of a bit array
         */
        int getValue(BitArray *bitArray)
        {
            int value = 0;
            unsigned int bitValue = 0;
            bitValue = bitArray->bitValues[0]->bit;
            value |= bitValue;
            for(int i = 1; i < BIT_ARRAY_LENGTH; i++)
            {
                bitValue = bitArray->bitValues[i]->bit;
                bitValue <<= i;
                value |= bitValue;
            }
            return value; 
        } 
};
/*
 * Main
 */
int main()
{
    int val;
    cout<<"Enter 4 bit integer value(0 - 8): ";
    cin>>val;
    BitArray bt, *samplebt;
    samplebt = new BitArray;
    for (int i = 0; i < BIT_ARRAY_LENGTH; i++)
    {
        samplebt = bt.setBit(samplebt, bt.getBit(val, i), i);
        cout<<"Bit of "<<val<<" at positon "<<i<<": "<<bt.getBit(val, i)->bit<<endl;
    }
    cout<<"The value is: "<<bt.getValue(samplebt)<<endl;
    return 0;
}
