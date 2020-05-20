#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <vector>
using namespace std;
#define MAX_DEGREE 6
//一個節點最多有 MAX_DEGREE - 1

class Index
{
private:
    int

public:

    Index(int& num_rows,vector<int>& key,vector<int>& value)
    {
        for (int i = 0; i < num_rows; i++)
        {
            insert(key[i], value[i]);
        } 
    }
    ~Index();
    void key_query(vector<int>& query_keys);
    void range_query(vector<pair<int, int>>& query_pairs);
    void clear_index();
};


#endif