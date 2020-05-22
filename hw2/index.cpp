#include <iomanip>
#include <typeinfo>
#include <math.h>
#include <fstream>
#include "index.h"


Index::Index(int num, vector<int> &key, vector<int> &value)
{
    for (int i = 0; i < num; i++)
    {
        insert(key[i], value[i]);
    }
}
/*
Index::Node* init()
{
    Node * 
}
*/

void Index::insert(int & k, int & val)
{
    /*
    cout << "insert key: " << setw(3) << k << endl;
    cout << "with value: " << setw(3) << val << endl;
    cout << endl;
    */
    if (root == NULL)//整個 B+ Tree 還是空的
    {
        root = new(Node);
        root -> isLeaf = 1;
        root -> right = NULL;
        root -> left = NULL;
        root -> key_value_pair.push_back({k, val});
    }
    Node *ptr = root;
    while (true)
    {
        int i = 0;
        for ( i = 0; i < ptr->key_value_pair.size() && k >= ptr->key_value_pair[i].first; i++);
        if(ptr->isLeaf == true)
        {
            if(ptr->key_value_pair[i-1].first == k){
                cout << "The inserted key is used." << endl;
                return;
            }
            else
            {
                if (i == ptr -> key_value_pair.size()){
                    ptr -> key_value_pair.push_back({k, val});
                }else{
                    ptr -> key_value_pair.insert(ptr->key_value_pair.begin() + i, {k, val});
                }
                if (ptr -> key_value_pair.size() > 2*ORDER)
                {
                    split_child(ptr);
                    return;
                }
                return;
                
            }
        }else if (ptr->isLeaf == false)
        {
            ptr = ptr -> ptr_v[i];
        }
    }
}

void Index::split_child(Node *ptr)// x 為基準，分裂出 npFirst 作為上方節點，下面接 x 和 npMiddle
{
    cout << "split from node " << ptr << endl;
    Node * node_left = new(Node);
    Node * node_right = new(Node);

    node_left -> isLeaf = ptr -> isLeaf;
    node_right -> isLeaf = ptr -> isLeaf;

    node_left -> right = node_right;
    node_right -> right = ptr -> right;
    node_left -> left = ptr -> left;
    node_right -> left = node_left;
    if (ptr -> right != NULL){
        ptr -> right -> left = node_right;
    }
    if (ptr -> left != NULL)
    {
        ptr -> left -> right = node_left;
    }
    if (ptr == root)
    {
        height ++;
        root = new(Node);
        node_right -> parent = node_left -> parent = root;
        root -> parent = NULL;
        root -> left = root -> right = NULL;
        root -> isLeaf = false;
        root -> key_value_pair.push_back(ptr->key_value_pair[ORDER]);
        if (ptr -> isLeaf == true)
        {
            node_right -> key_value_pair.push_back(ptr->key_value_pair[ORDER]);
        }
        for (int i = 0; i < ORDER; i++)
        {
            node_left -> key_value_pair.push_back(ptr->key_value_pair[i]);
            node_right -> key_value_pair.push_back(ptr->key_value_pair[ORDER+1+i]);
        }
        if(ptr->isLeaf == false){
            for (int i = 0; i < ORDER+1; i++)
            {
                node_left -> ptr_v.push_back(ptr->ptr_v[i]);
                node_right -> ptr_v.push_back(ptr->ptr_v[ORDER+1+i]);
            }
            for (int i = 0; i < node_left->ptr_v.size(); i++)
            {//連接左右節點和對應子節點
                node_left -> ptr_v[i] -> parent = node_left;
                node_right -> ptr_v[i] -> parent = node_right;
            }
        }
        root -> ptr_v.push_back(node_left);
        root -> ptr_v.push_back(node_right);
        node_left -> parent = node_right -> parent = root;
        delete(ptr);
    }else{
        pair<int,int> mid = ptr -> key_value_pair[ORDER];
        Node *p = ptr -> parent;
        node_left -> parent = node_right -> parent = ptr -> parent;
        int i;
        if (ptr -> isLeaf == true)
        {
            node_right -> key_value_pair.push_back( ptr -> key_value_pair[ORDER]);
        }
        for ( i = 0; i < ORDER; i++)
        {
            node_left->key_value_pair.push_back(ptr->key_value_pair[i]);
            node_right->key_value_pair.push_back(ptr->key_value_pair[ORDER+1+i]);
        }
        if ( ptr->isLeaf == false){
            for ( i = 0; i < ORDER+1; i++)
            {
                node_left -> ptr_v.push_back(ptr -> ptr_v[i]);
                node_right -> ptr_v.push_back(ptr -> ptr_v[ORDER+1+i]);
            }
            for ( i = 0; i < ORDER+1; i++)
            {
                node_left -> ptr_v[i] -> parent = node_left;
                node_right -> ptr_v[i] -> parent = node_right;
            }
        }
        for ( i = 0; i < p -> key_value_pair.size() && mid.first >= p -> key_value_pair[i].first; i++);
        if (i==p->key_value_pair.size())
        {
            p->key_value_pair.push_back(mid);
            p->ptr_v.pop_back();
            p->ptr_v.push_back(node_left);
            p->ptr_v.push_back(node_right);
        }else if( i == 0 ){
            p->key_value_pair.insert(p->key_value_pair.begin(), mid);
            p->ptr_v[0] = node_left;
            p->ptr_v.insert(p->ptr_v.begin()+1, node_right);
        }else{
            p->key_value_pair.insert(p->key_value_pair.begin()+i, mid);
            p->ptr_v[i] = node_left;
            p->ptr_v.insert(p->ptr_v.begin()+i+1, node_right);
        }
        delete(ptr);
        if (p->key_value_pair.size() > 2*ORDER)
        {
            split_child(p);
        }
    }
    return;    
}
void Index::key_query(vector<int> &keys)
{
    ofstream file;
    file.open("key_query_out.txt", ios::out | ios::app);
    for (int j = 0; j < keys.size(); j++)
    {
        Node * ptr = root;
        int k = keys[j];
        while (ptr->isLeaf == false)
        {
            int i = 0;
            if (k < ptr->key_value_pair[0].first){
                i = 0;
            }else if (k >= ptr->key_value_pair[ptr->key_value_pair.size()-1].first){
                i = ptr->key_value_pair.size();
            }else{
                for ( i = 0; i < ptr->key_value_pair.size() && k >= ptr->key_value_pair[i].first; i++);
            }
        ptr = ptr -> ptr_v[i];
       }
        if (k < ptr -> key_value_pair[0].first || k > ptr-> key_value_pair[ptr->key_value_pair.size()-1].first)
        {//Not found
            file << "-1" << endl;
            continue;
        }
        for (int i = 0; i < ptr->key_value_pair.size() && k >= ptr->key_value_pair[i].first; i++)
        {
            if (k == ptr->key_value_pair[i].first)
            {
                file << ptr->key_value_pair[i].second << endl;
                goto end;
            }
        }
        file << "-1" << endl;
        continue;
        end:;
    }
    file.close();
}
void Index::range_query(vector< pair<int,int> > &key_pair_v)
{
    ofstream file;
    file.open("range_query_out.txt", ios::out | ios::app);
    for (int j = 0; j < key_pair_v.size(); j++)
    {
        int k1 = key_pair_v[j].first;
        int k2 = key_pair_v[j].second;
        Node * ptr = root;
        int i;
        while (ptr-> isLeaf == false)
        {
            for ( i = 0; i < ptr->key_value_pair.size() && k1 >= ptr->key_value_pair[i].first; i++);
            ptr = ptr -> ptr_v[i];
        }
        for ( i = 0; i < ptr -> key_value_pair.size() && k1 > ptr->key_value_pair[i].first; i++);
        if (i == ptr->key_value_pair.size() && ptr->right != NULL)
        {
            i = 0;
            ptr = ptr->right;
        }
        if(i==ptr->key_value_pair.size() && ptr->right==NULL){
            cout << "key range not found" << endl;
        }
        int max = -1000000000;
        while (ptr->key_value_pair[i].first <= k2)
        {
            if (max < ptr->key_value_pair[i].second){
                max = ptr -> key_value_pair[i].second;
            }
            i++;
            if (i >= ptr->key_value_pair.size())
            {
                if (ptr -> right != NULL)
                {
                    ptr = ptr -> right;
                    i = 0;
                }
                else
                {
                    break;
                }
            }
        }
        if (max == -1000000000)
        {
            file << "No value found" << endl;
        }
        else{
            file << max << endl;
        }
    }
    file.close();
}
void Index::clear_index()
{
    release(root);
}
void Index::release(Node *ptr)
{
    if (ptr -> isLeaf == true)
    {
        delete(ptr);
        return;
    }else{
        for (int i = 0; i < ptr->ptr_v.size(); i++)
        {
            release(ptr->ptr_v[i]);
        }
    }
    delete ptr;
}
