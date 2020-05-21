#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <vector>
using namespace std;
#define MAX_DEGREE 6
//一個節點最多有 MAX_DEGREE - 1

struct Node
{
    int *key;
    int *value;
    Node **child_ptr;
    bool isLeaf;
    int n;
};


class Index
{
private:
    Node **pp_root = new Node *;
    Node **pp_np = new Node *;
    Node **pp_x = new Node *;
public:
    Node* init();
    void insert(int k, int val);
    int split_child(Node *x, int i);
    void key_query(vector<int>& query_keys);
    void range_query(vector< pair<int,int> >& query_pairs);
    void clear_index();
    
    Index(int num, vector<int> &key, vector<int> &value);
    ~Index();
    
    void debug();
};
#endif