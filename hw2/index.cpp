#include <iostream>
using namespace std;
#include "index.h"


Node *init(){//初始化一個 node
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
        insert(this,this->root, key[i], value[i]);
    }
    
}
Index::~Index(){

}
void Index::insert(Index *T,Node *root, int key, int value){
    int i, temp;
    x = root;//從 root 開始
    if (x == NULL){//若 root 是空的
        root = init();//初始化一個 node 作為 root
        x = root;//x 儲存 root 的指標
    }
    else{//已有 root
        if (x->leaf ==true && x->n == M-1)//root 是子葉，且容納元素已滿
        {
            temp = split_child(this, this->root, x, -1);//執行 split
            x = root;
            for (i = 0; i < (x->n); i++){//
                if ((key > x->data[i]) && (key < x->data[i + 1])){//
                    i++;
                    break;
                }
                else if ( key < x->data[0]){
                    break;
                }
                else{
                    continue;
                }
            }
            x = x->child_ptr[i];// x 換成子樹中位數的指標
        }
        else{//root 不是子葉，
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
                    temp = split_child(this,this->root, x, i);
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
    x -> data[x->n] = key;
    x -> value[x->n] = value;
    sort(x->data, x->n);
    x->n++;

}
int Index::split_child(Index *T,Node* root, Node *x, int i){
    int  j, mid;//iter 和 中位值
    Node *np1, *npMiddle, *y;
    npMiddle = init();//初始化一個 node
    npMiddle->leaf = true;
    if( i == -1 ){//
        mid = x->data[Middle-1];//mid 紀錄最右邊的值
        x->data[Middle-1] = 0;//將最右邊歸零
        x->n--;//將儲存值減一
        np1 = init();//初始化新結點
        np1->leaf = true;
        for (j = Middle; j < M-1 ; j++)//將舊的資料搬到新結點
        {
            npMiddle->data[j - Middle] = x->data[j];//搬資料
            npMiddle->child_ptr[j - Middle] = x->child_ptr[j];//重新指子樹指標
            npMiddle->n++;//因應新資料，增加已儲存個數
            x->data[j] = 0;
            x->n--;
        }
        for ( j = 0; i < M; j++)
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

void Index::key_query(vector<int>& query_keys){

}
void Index::range_query(vector<pair<int, int>>& query_pairs){
    
}
void Index::clear_index(){
    
}
