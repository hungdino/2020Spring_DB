#include <iostream>
#include <math.h>
using namespace std;
#define M 6 // the order of b plus tree, could be large to optimize b plus tree
#define Middle 3

struct Node
{
    int *data;//元素
    Node **child_ptr;//指向子樹
    bool leaf;//是否為子葉
    int n;//元素長度
}*root = NULL, *np = NULL, *x = NULL;

Node *init(){//初始化一個 node
    int i;
    np = new Node;
    np -> data = new int [M-1];
    np -> child_ptr = new Node *[M];
    np -> leaf = true;
    np -> n = 0;
    for (i = 0; i < M; i++)
    {
        np -> child_ptr[i] = NULL;
    }
    return np;
    
}

int main(){
    Node *n;
    n = init();
    n -> data[0] = 15;
    cout << n->data[0] << endl;
    


    return 0;
}