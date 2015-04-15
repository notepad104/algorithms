#include <iostream>
#include <cstdio>
#include <cstring>
#include <sodium.h>
#include <set>
#include <map>
#include <hash_map>
#include <cstdlib>
using namespace std;
template<int, bool[]>
class HashMap
{
    int key;
    bool value[];
};
class MinHash
{
    private:
        int *hash;
        int numHash;
    public:
        static int Hash(int x, int a, int b, int c)
        {
            int hashValue = (int)((a * (x >> 4) + b * x + c) & 131071);
            return abs(hashValue);
        }

        MinHash(int numHash)
        {
            this->numHash = numHash;
            hash = new int[numHash];
            int a = rand() % 11 + 1;
            int b = rand() % 11 + 1;
            int c = rand() % 11 + 1;
            for (int i = 0; i < numHash; i++)
            {
                int x = Hash(a * b * c, a, b, c);
                hash[i] = x;
            }
        }
        map<int, bool[]> buildBitMap(set<int> set1, set<int> set2)
        {
            map<int, bool[]> bitArray = new HashMap<int, bool[]>();

		for(T t : set1){
			bitArray.put(t, new boolean[]{true,false});
		}

		for(T t : set2){
			if(bitArray.containsKey(t)){
				// item is not present in set1
				bitArray.put(t, new boolean[]{true,true});
			}else if(!bitArray.containsKey(t)){
				// item is not present in set1
				bitArray.put(t, new boolean[]{false,true});
			}
		}


		return bitArray;
	}
        double similarity(set<int> set1, set<int> set2)
        {
            int numSets = 2;
            map<int, bool []> bitMap = buildBitMap(set1, set2);
        }
};
