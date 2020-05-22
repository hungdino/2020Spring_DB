#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <vector>
using namespace std;
#define ORDER 100
//一個節點最多有 MAX_DEGREE - 1

struct Node
{
    Node *parent;
    Node *right;
    Node *left;
    vector<Node *> ptr_v;
    vector< pair<int,int> > key_value_pair;
    bool isLeaf;
};


class Index
{
private:
    int height = 1;
    Node * root = NULL;
public:
    Index(int num, vector<int> &key, vector<int> &value);
    void key_query(vector<int>& keys);
    void range_query(vector< pair<int,int> >& query_pairs);
    void clear_index();
    
    void insert(int &k, int &val);
    void split_child(Node *ptr);
    Node* init();
    void release(Node *ptr);
};
#endif