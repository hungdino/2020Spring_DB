#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
#define MAX_DEGREE 6
//一個節點最多有 MAX_DEGREE - 1


class Index
{
private:
    struct Node
    {
        bool isLeaf;
        vector<pair<int,int>> key_value;
        vector

    };
public:
    int *d;
    Index **child_ptr;
    bool l;
    int n;
    Index(int& num_rows,vector<int>& key,vector<int>& value);
    ~Index();
    void key_query(vector<int>& query_keys);
    void range_query(vector<pair<int, int>>& query_pairs);
    void clear_index();



};

#endif