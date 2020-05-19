#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <vector>

class Index{
private:

public:
    Index(int& num_rows,vector<int>& key,vector<int>& value);
    ~Index();
    void key_query(vector<int>& query_keys);
    void range_query(vector<pair<int, int>>& query_pairs);
    void clear_index();

    void insert(Index *T, int key, int value);
    int split_child(Index *T, int i);
    int search(Index *T, int key);
};
struct Node{
    bool IS_LEAF;
    int key;
}

#endif