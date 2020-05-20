#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
#define M 6 // the order of b plus tree, could be large to optimize b plus tree
#define Middle 3
//    float M_float = M;
//    int Middle = ceil(M_float/2);

struct Node
{
    int *data;//key
    int *value;//value
    Node **child_ptr;//指向子樹
    bool leaf;//是否為子葉
    int n;//已儲存之元素個數
}*np = NULL, *x = NULL;
    Node *init();

class Index{
private:
    Node *root = NULL;
public:
    Index(int& num_rows,vector<int>& key,vector<int>& value);
    ~Index();
    void insert(Index *T,Node *root, int key, int value);
    int split_child(Index *T,Node *root, Node *x, int i);
    void sort(int *p, int n);


    void key_query(vector<int>& query_keys);
    void range_query(vector<pair<int, int>>& query_pairs);
    void clear_index();


};

#endif