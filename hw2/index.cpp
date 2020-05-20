#include <iostream>
using namespace std;
#include "index.h"


Node *init(Node *np){//初始化一個 node
    int i;
    np = new Node;
    np -> data = new int [M-1];
    np -> value = new int [M-1];
    np -> child_ptr = new Node *[M];
    np -> leaf = true;
    np -> n = 0;
    for (i = 0; i < M; i++)
    {
        np -> child_ptr[i] = NULL;
    }
    return np;
    
}
Index::Index(int& num_rows,vector<int>& key,vector<int>& value){
    int i;
    for ( i = 0; i < num_rows; i++)
    {
        cout << "insert: " << key[i] << ", " << value[i] << endl;
        this->root = insert(this,this->root, this->np, this->x, key[i], value[i]);
    }
}
Index::~Index(){

}
Node *Index::insert(Index *T,Node *root, Node *np, Node *x, int key, int value){
    //cout << "insert" << endl;
    int i, temp;
    x = root;//從 root 開始
    if (x == NULL){//若 root 是空的
        //cout << "start with root" << endl;
        //cout << "init root" <<endl;
        root = init(this->np);//初始化一個 node 作為 root
        //cout << root << endl;
        x = root;//x 儲存 root 的指標
    }
    else{//已有 root
        //cout << "root existed" << endl;
        if (x->leaf ==true && x->n == M-1)//root 是子葉，且容納元素已滿
        {
            //cout << "capacity full, go to split, *x= " << x << endl;
            temp = split_child(this, this->root,this->np, x, -1);//執行 split
            //cout << "split completed" << endl;
            x = root;
            for (i = 0; i < (x->n); i++){
                if ((key > x->data[i]) && (key < x->data[i + 1])){//
                    i++;
                    break;
                }
                else if ( key < x->data[0] ){
                    break;
                }
                else{
                    continue;
                }
            }
            //問題在這 !!!
            cout << x->n  << endl;
            x = x->child_ptr[i];// x 換成子樹相對應的位置， i < key < i+1
            //cout << x << endl;
        }
        else{//root 不是子葉，
            cout << "just insert in it" << endl;
            while(x->leaf == false){//x 非子葉的情況
                for (i = 0; i < (x->n) ; i++ )
                {
                    if ( (key > x->data[i]) && (key < x->data[i+1]) ){
                        i++;
                        break;
                    }
                    else if (key < x->data[0]){
                        break;
                    }
                    else{
                        continue;
                    }
                }
                if ( (x->child_ptr[i])->n == M-1 ){
                    temp = split_child(this, this->root,this->np, x, i);
                    x -> data[x->n] = temp;
                    x -> n++;
                    continue;
                }
                else{
                    x = x -> child_ptr[i];
                }
            }
        }
    }
    //cout << x << endl;
    x -> data[x->n] = key;
    //cout << "spspsp" << endl;
    x -> value[x->n] = value;
    sort(x->data, x->n);
    x->n++;
    //cout << "insert done" << endl;
    return root;

}
int Index::split_child(Index *T,Node *root, Node *np, Node *x, int i){
    int  j, mid;//iter 和 中位值
    Node *np1, *npMiddle, *y;
    npMiddle = init(this->np);//初始化一個 node
    npMiddle->leaf = true;
    if( i == -1 ){
        //cout << x << endl;
        mid = x->data[Middle-1];//mid 紀錄最右邊的值
        x->data[Middle-1] = 0;//將最右邊歸零
        x->n--;//將儲存值減一
        np1 = init(this->np);//初始化新結點
        np1->leaf = true;
        for (j = Middle; j < M-1 ; j++)//將右半邊舊的資料搬到新結點
        {
            npMiddle->data[j - Middle] = x->data[j];//搬資料
            npMiddle->child_ptr[j - Middle] = x->child_ptr[j];//重新指子樹指標
            npMiddle->n++;//因應新資料，增加已儲存個數
            x->data[j] = 0;6     
            x->n--;
        }
        for ( j = 0; j < M; j++)
        {
            x->child_ptr[j] = NULL;
        }
        np1->data[0] = mid;
        np1->child_ptr[np1->n] = x;
        np1->child_ptr[np1->n + 1] = npMiddle;
        np1->n++;
        root = np1;
    }
    else
    {
        y = x->child_ptr[i];
        mid = y->data[Middle-1];
        y->data[Middle-1] = 0;
        y->n--;
        for ( j = Middle; j < M-1; j++)
        {
            npMiddle->data[j-Middle] = y->data[j];
            npMiddle->n++;
            y->data[j] = 0;
            y->n--;
        }
        x->child_ptr[i+1] = y;
        x->child_ptr[i+1] = npMiddle;
    }
    return mid;
}
void Index::sort(int *p, int n){
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = i; j <= n; j++)
        {
            if (p[i] > p[j])
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
void Index::traverse(Node *p){
    int i;
    for ( i = 0; i < p->n; i++)
    {
        if(p->leaf == false)
        {
            traverse(p->child_ptr[i]);
        }
        cout << "key: " << p->data[i] << "with value: " << p->value[i] << endl;
    }
    if (p->leaf == false)
    {
        traverse(p->child_ptr[i]);
    }
}
void Index::bridge(){
    //cout << "test message" << endl; 
    //cout << this->root <<endl;
}
void Index::key_query(vector<int>& query_keys){
    
}
void Index::range_query(vector<pair<int, int>>& query_pairs){
    
}
void Index::clear_index(){
    
}
