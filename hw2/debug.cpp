#include <iostream>
#include "index.h"
int main(){
    cout << "Run debug.cpp" << endl;
    int num = 20;
    vector<int> key = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    vector<int> value = {1, 2, 3, 4, 5, 6, 7, 8, 9, -2};
    Index myIndex(num ,key, value);
    myIndex.debug();
    //cout << myIndex.debug() << endl;
    
    return 0;
}