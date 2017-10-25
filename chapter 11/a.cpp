#include <iostream>
#include "a1.h"
using namespace std;

int main()
{
    Vec<int> myvec;
    
    for(int i=0; i<10; i++)
        myvec.push_back(i+1);

    for(auto it = myvec.begin(); it != myvec.end(); it++)
        cout << *it << endl;

    return 0;
}