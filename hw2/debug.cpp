#include <iostream>
#include "index.h"
int main(){
    cout << "Run debug.cpp" << endl;
    int num = 5;
    vector<int> key = {10, 20, 30, 40, 50, 60};
    vector<int> value = {1, 2, 3, 4, 5, 6};
    Index myIndex(num ,key, value);
    //cout << myIndex.debug() << endl;
    
    return 0;
}