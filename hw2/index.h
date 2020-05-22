#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <vector>
using namespace std;
#define ORDER 6
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
    void insert(int &k, int &val);
    void split_child(Node *ptr);

    void key_query(vector<int>& keys);
    void range_query(vector< pair<int,int> >& query_pairs);
    void clear_index();
    void sort(int *p, int n);
    
    Index(int num, vector<int> &key, vector<int> &value);
    void release(Node *ptr);
    void debug();
};
#endif