#include <iomanip>
#include <typeinfo>
#include <math.h>
#include "index.h"

Node* Index::init()
{
    int i;
    *pp_np = new Node;
    /*
    cout << "pp_np is    " << setw(20) << pp_np << endl;
    cout << "*pp_np is   " << setw(20) << *pp_np << endl;
    */
    (*pp_np) -> key = new int[MAX_DEGREE - 1];
    (*pp_np) -> value = new int [MAX_DEGREE - 1];
    (*pp_np) -> child_ptr = new Node* [MAX_DEGREE];
    (*pp_np) -> isLeaf = true;  
    (*pp_np) -> n = 0;
    for (int i = 0; i < MAX_DEGREE; i++)
    {
        (*pp_np) -> child_ptr[i] = NULL;
    }
    /*
    cout << "(*pp_np) -> key is    " << setw(20) << (*pp_np) -> key << endl;
    cout << "(*pp_np) -> value is  " << setw(20) << (*pp_np) -> value << endl;
    */
    return *pp_np;
}

Index::Index(int num, vector<int> &key, vector<int> &value)
{
    
    for (int i = 0; i < num; i++)
    {
        insert(key[i], value[i]);
    }
}
void Index::insert(int k, int val)
{
    cout << "insert key: " << setw(3) << k << endl;
    cout << "with value: " << setw(3) << val << endl;
    /*
    cout << "pp_root is  " << setw(20) << pp_root << endl;
    cout << "*pp_root is " << setw(20) << *pp_root << endl;
    cout << "pp_np is    " << setw(20) << pp_np << endl;
    cout << "*pp_np is   " << setw(20) << *pp_np << endl;
    cout << "pp_x is     " << setw(20) << pp_x << endl;
    cout << "*pp_x is    " << setw(20) << *pp_x << endl;
    */
    int i, temp;// 用於 iter
    *pp_x = *pp_root;
    cout << "pp_x is     " << setw(20) << pp_x << endl;
    cout << "*pp_x is    " << setw(20) << *pp_x << endl;
    if (*pp_x == NULL)//整個 B+ Tree 還是空的
    {
        *pp_root = init();//創建 root node
        *pp_x = *pp_root;
    }
    else//Root 已經有東西了
    {
        //cout << (*pp_x) -> n <<endl;
        if ( (*pp_x) -> isLeaf == true && (*pp_x) -> n == MAX_DEGREE - 1 )//Node 是滿的
        {
            temp = split_child( (*pp_x), -1);
            *pp_x = *pp_root;
            for (i = 0; i < ( (*pp_x) -> n ); i++)
            {
                if ( (k > (*pp_x) -> key[i]) && (k < (*pp_x) -> key[i+1]) ){
                    i++;
                    break;
                }else if( k < (*pp_x) -> key[0]){
                    break;
                }else{
                    continue;
                }
            }
            *pp_x = (*pp_x) -> child_ptr[i];
        }
        else// Node 還有空間或是不是子葉
        {
            while( (*pp_x) -> isLeaf == false)
            {
                for (i = 0; i < ( (*pp_x) -> n ); i++)
                {
                    if ( (k > (*pp_x) ->key[i]) && (k < (*pp_x) -> key[i+1] ) ){
                        i++;
                        break;
                    }else if ( k < (*pp_x) -> key[0] ){
                        break;
                    }else{
                        continue;
                    }
                }
                if ( ( (*pp_x) -> child_ptr[i] ) -> n == MAX_DEGREE - 1 )
                {
                    temp = split_child(*pp_x, i);
                    (*pp_x) -> key[(*pp_x)->n] = temp;
                }
                else{
                    *pp_x = (*pp_x)->child_ptr[i];
                }
            }
        }
    }
    (*pp_x) -> key[(*pp_x)->n] = k;
    (*pp_x) -> value[(*pp_x)->n] = val;
    sort( (*pp_x)->key, (*pp_x)->n );
    (*pp_x) -> n++;
}

int Index::split_child(Node *x, int i)// x 為基準，分裂出 npFirst 作為上方節點，下面接 x 和 npMiddle
{
    cout << "split from node " << x << endl;
    int j, mid_k, mid_v;
    Node *npFirst, *npMiddle, *y;
    npMiddle = init();
    npMiddle -> isLeaf = true;
    float temp_float = MAX_DEGREE - 2;
    int temp_int = floor(temp_float/2);//待檢查
    cout << temp_int << endl;
    if (i == -1)
    {
        mid_k = x -> key[temp_int];//暫存 x 中位數的 key
        mid_v = x -> value[temp_int];//暫存 x 中位數的 value
        x -> key[temp_int] = 0;
        x -> value[temp_int] = 0;
        x -> n--;
        npFirst = init();
        npFirst -> isLeaf = false;//上方的節點
        x -> isLeaf = true;
        for (j = temp_int + 1; j < MAX_DEGREE - 1; j++)//右半邊的元素搬到 npMiddle
        {
            npMiddle -> key[j - temp_int - 1] = x -> key[j];//繼承 key
            npMiddle -> value[j - temp_int - 1] = x -> value[j];//繼承 value
            npMiddle -> child_ptr[j - temp_int - 1] = x -> child_ptr[j];//繼承右半邊的 child_ptr
            (npMiddle -> n)++;
            x -> key[j] = 0;//清空
            x -> value[j] = 0;//清空
            (x -> n)--;
        }
        for (j = 0; j < MAX_DEGREE - 1; j++)//清空 child_ptr，應該是到 MAX_DEGREE 為止，因為 child_ptr 數量較多
        {
            x -> child_ptr[j] = NULL;
        }
        npFirst -> key[0] = mid_k;
        npFirst -> value[0] = mid_v;//非子葉應該是不需要給 value
        npFirst -> child_ptr[npFirst -> n] = x;
        npFirst -> child_ptr[ (npFirst -> n) + 1] = npMiddle;
        (npFirst -> n) ++;
        *pp_root = npFirst;
    }
    else
    {
        y = x -> child_ptr[i];
        mid_k = y -> key[temp_int];
        mid_v = y -> value[temp_int];
        y -> key[temp_int] = 0;
        (y -> n)--;
        for (j = temp_int + 1; j < MAX_DEGREE - 1; j++)
        {
            npMiddle -> key [j - temp_int - 1] = y -> key[j];
            npMiddle -> value [j - temp_int - 1] = y -> value[i];
            (npMiddle -> n)++;
        }
        x -> child_ptr[i + 1] = y;
        x -> child_ptr[i + 1] = npMiddle;
    }
    (*pp_x) -> value[(*pp_x)->n] = mid_v;
    return mid_k;
}
void Index:: sort(int *p, int n)
{//sort the tree
   int i, j, t_k, t_v;
   for (i = 0; i < n; i++) {
      for (j = i; j <= n; j++) {
         if (p[i] >p[j]) {
            t_k = p[i];
            t_v = ((*pp_x) -> value)[i];
            p[i] = p[j];
            ((*pp_x) -> value)[i] =  ((*pp_x) -> value)[j];
            p[j] = t_k;
             ((*pp_x) -> value)[j] = t_v;
         }
      }
   }
}

void Index::traverse(Node *p)
{
   cout << endl;
   int i;
   for (i = 0; i < p->n; i++) {
      if (p->isLeaf == false) {
         traverse(p->child_ptr[i]);
      }
      cout << " " << p->key[i];
   }
   if (p->isLeaf == false) {
      traverse(p->child_ptr[i]);
   }
   cout<<endl;
}
void Index::debug()
{
    this->traverse(*(this->pp_root));
}
Index::~Index()
{

}
