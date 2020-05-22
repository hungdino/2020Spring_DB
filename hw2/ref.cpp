#include"index.h"
#include<fstream>
#include<string>
#include<cstdlib>
 
Index ::Index(int& num_rows, vector<int>& key, vector<int> & value){
    for(int i=0;i<num_rows;i++){
        insert(key[i],value[i]);
    }
} 
void Index::insert(int &key, int& value){
    if(root == NULL){
        root = new(node);
        root->isleaf=1;
        root->right=0;
        root->left=0;
        root->key_val_v.push_back({key,value});
        return;
    }
    node* pt = root;
    while(1){
        int i=0;
        for(i=0;i<pt->key_val_v.size() && key >= pt->key_val_v[i].first;i++);
        if(pt->isleaf==1){ 
            if(pt->key_val_v[i-1].first == key){
                cout<<"This key has been use.\n";
                return;
            }else{ 
                if(i==pt->key_val_v.size()) pt->key_val_v.push_back({key,value}); 
                else                        pt->key_val_v.insert(pt->key_val_v.begin() + i,{key,value});
                if(pt->key_val_v.size()>2*ORDER){
                    overflow_handle(pt);return;
                }
                //cout<<"root->pt_v "<<root->pt_v.size()<<endl;
                return;
            }
        }else if(pt->isleaf==0){       
            pt = pt->pt_v[i];
        }
    }
}
 
void Index ::overflow_handle(node * pt){
    node * node_l = new(node);
    node * node_r = new(node);
    node_l->isleaf = node_r->isleaf = pt->isleaf;
    node_l->right = node_r;
    node_r->right = pt->right;
    node_l->left = pt->left;
    node_r->left = node_l;
    if(pt->right!=0)pt->right->left = node_r;
    if(pt->left!=0)pt->left->right = node_l;
    if(pt==root){
        height++;
        root = new(node);
        node_r->parent = node_l->parent = root;
        root->parent = 0;
        root->left = root->right = 0;
        root->isleaf=0;
        //cout<<"h="<<height<<endl;
        root->key_val_v.push_back(pt->key_val_v[ORDER]);//pt mid 給 root
        if(pt->isleaf==1){//leaf才要r多一
            node_r->key_val_v.push_back(pt->key_val_v[ORDER]);
        }
        for(int i=0;i<ORDER;i++){//non-leaf不用r多一
            node_l->key_val_v.push_back(pt->key_val_v[i]);
            node_r->key_val_v.push_back(pt->key_val_v[ORDER+1+i]);
        }
        
        if(pt->isleaf==0){//non-leaf才有pt_v
            for(int i=0;i<ORDER+1;i++){
                node_l->pt_v.push_back(pt->pt_v[i]);
                node_r->pt_v.push_back(pt->pt_v[ORDER+1+i]);
            }
           
            for(int i=0;i<node_l->pt_v.size();i++){
                node_l->pt_v[i]->parent = node_l;
                node_r->pt_v[i]->parent = node_r;
                //for(int j=0;j<node_r->pt_v[i]->key_val_v.size();j++)cout<<node_r->pt_v[i]->key_val_v[j].first<<" ";
                //cout<<endl;
                
            }
            
        }
        
        //node_r->key_val_v.push_back(pt->key_val_v[2*ORDER]);//r會多一個
        root->pt_v.push_back(node_l);//root->pt_v最左
        root->pt_v.push_back(node_r);//root->pt_v第二
        node_l->parent = node_r->parent = root;//新root為node_l , node_r的parent
        delete(pt);//pt沒用了
    }else{
        
        pair<int,int> mid = pt->key_val_v[ORDER];
        
        node * p = pt->parent;
        node_l->parent = node_r->parent = pt->parent;//left,right的parent 指向原parent
        //cout<<"p->key_val_v[0].first"<<p->key_val_v[0].first<<endl;
        //cout<<"pt->isleaf?"<<pt->isleaf<<endl;
        
        int i;//index
        if(pt->isleaf==1){
            node_r->key_val_v.push_back(pt->key_val_v[ORDER]);
        }
        for(i=0;i<ORDER;i++){
            node_l->key_val_v.push_back(pt->key_val_v[i]);
            node_r->key_val_v.push_back(pt->key_val_v[ORDER+1+i]);
        }
        
        //cout<<"node_l->right "<<node_l->right->key_val_v[0].first<<endl;
        if(node_r->right==0){
            //cout<<"node_r->right fadfhfkladjhfdakjh"<<node_r->right<<endl;
            //cout<<"node_r->right->key_val_v[0].first "<<node_r->right->key_val_v[0].first<<endl;
        }
        //node_r->key_val_v.push_back(pt->key_val_v[2*ORDER]);//r多一個
        if(pt->isleaf==0){//non-leaf才有pt_v
            //cout<<"handle_non-leaf\n";
            for(i=0;i<ORDER+1;i++){
                node_l->pt_v.push_back(pt->pt_v[i]);
                node_r->pt_v.push_back(pt->pt_v[ORDER+1+i]);
            }
            for(i=0;i<ORDER+1;i++){
                node_l->pt_v[i]->parent = node_l;
                node_r->pt_v[i]->parent = node_r;
            }
            //cout<<"node_l pt_v size "<<node_l->pt_v.size()<<endl;
            //cout<<"node_r pt_v size "<<node_r->pt_v.size()<<endl;
        }
       
        for(i=0 ; i<p->key_val_v.size() && mid.first >= p -> key_val_v[i].first ; i++);
        
        //cout<<"p->isleaf"<<p->isleaf<<endl;
        
        if(i==p->key_val_v.size()){
            p->key_val_v.push_back(mid);
            p->pt_v.pop_back();
            p->pt_v.push_back(node_l);
            p->pt_v.push_back(node_r);
            if(p->key_val_v.size()!=p->pt_v.size()-1){
                
            }
        }else if(i==0){
            p->key_val_v.insert(p->key_val_v.begin(),mid);
            p->pt_v[0]=node_l;
            p->pt_v.insert(p->pt_v.begin()+1,node_r);
            
        }else{
            
            p->key_val_v.insert(p->key_val_v.begin()+i,mid);
           //cout<<"here?\n";
            p->pt_v[i] = node_l;
            p->pt_v.insert(p->pt_v.begin()+i+1,node_r);
        }
        delete(pt);
        if(p->key_val_v.size()>2*ORDER){
            overflow_handle(p);
        }
    }
    return;
}
 
void Index ::del(int key){
}
 
void Index ::key_query(vector<int> key){
    
    ofstream file;
    file.open("key_query_out.txt",std::ios_base::app);
    for(int k=0;k<key.size();k++){
        node * pt = root;
        int KEY=key[k];
        //cout<<"now query "<<KEY<<endl;
        while(pt->isleaf==0){
            int i=0;
            //cout<<"到底在哪";
            //cout<<KEY<<endl;
            //cout<<pt->key_val_v[pt->key_val_v.size()-1].first<<endl;
            if(KEY<pt->key_val_v[0].first){
                i=0;
            }else if(KEY>=pt->key_val_v[pt->key_val_v.size()-1].first){
                i=pt->key_val_v.size();
            }else{
                i=0;
                for(i=0;i<pt->key_val_v.size() && KEY >= pt->key_val_v[i].first;i++);
            
                /*int l=0,r=pt->key_val_v.size();
                int m;
                for(m=(l+r)/2;!(key >= pt->key_val_v[m-1].first && key<pt->key_val_v[m].first) ;){
                    if(key > pt->key_val_v[m].first)l=m;
                    else if(key < pt->key_val_v[m].first)r=m;
                    else if(key == pt->key_val_v[m].first)break;
                    m=(l+r)/2;
                }
                i    = m;*/
            }     
            pt = pt->pt_v[i];
        }
        /*for(int i=0;i<pt->key_val_v.size();i++){
            cout<<pt->key_val_v[i].first<<" ";
        }*/
        if(KEY<pt->key_val_v[0].first || KEY>pt->key_val_v[pt->key_val_v.size()-1].first){
            file <<"-1\n";continue;
        }
        int i=0;
        for(i=0;i<pt->key_val_v.size() && KEY>=pt->key_val_v[i].first;i++){
            if(KEY==pt->key_val_v[i].first){file<<pt->key_val_v[i].second<<endl;goto end;}
        }
        file<<"-1\n";continue;
        /*for(int m=(l+r)/2;pt->key_val_v[m].first!=key;){
            if(key>pt->key_val_v[m].first)l=m;
            else if(key<pt->key_val_v[m].first)r=m;
            else if(key==pt->key_val_v[m].first){
                file << pt->key_val_v[m].second<< endl;
            }
            if(r==l+1){
                file<<"-1\n"<<endl;return;
            }
        }*/
        end:;
    }
    file.close();
}


void Index ::range_query(vector<pair<int,int> >  v){
    ofstream file;
    //cout<<v.size()<<endl;
    file.open("range_query_out.txt",std::ios_base::app);
    for(int r=0;r<v.size();r++){
        //cout<<"r="<<r<<endl;
        int KEY1 = v[r].first;
        //cout<<"KEY1 "<<KEY1<<endl;
        
        int KEY2 = v[r].second;
        //cout<<"KEY2 "<<KEY2<<endl;
        node* pt = root;
        int i;
        while(pt->isleaf==0){
            for(i=0;i<pt->key_val_v.size() && KEY1>=pt->key_val_v[i].first;i++);
            //cout<<"key_val_v.size() "<<pt->key_val_v.size()<<endl;
            //cout<<"pt_v.size() "<<pt->pt_v.size()<<endl;
            /*if(pt->right!=0){
                for(int j=0;j<pt->right->key_val_v.size();j++){
                    cout<<pt->right->key_val_v[j].first<<" ";
                    cout<<endl;
                }
                cout<<endl;
            }*/
            pt=pt->pt_v[i];
        }
        //if(pt->right!=0)cout<<"leaf pt->right"<<pt->right->key_val_v[0].first<<endl;
        
        for(i=0;i<pt->key_val_v.size() && KEY1>pt->key_val_v[i].first;i++);
        if(i==pt->key_val_v.size() &&pt->right!=0){
            i=0;
            pt=pt->right;
        }
        if(i==pt->key_val_v.size() &&pt->right==0){
            //cout<<"no answer\n"<<endl;
        }
        int max=-999999999;
        while(pt->key_val_v[i].first<=KEY2){
            //cout<<"compare to"<<pt->key_val_v[i].first<<" value: "<<pt->key_val_v[i].second<<endl;
            //cout<<"i="<<i<<endl;
            if(max<pt->key_val_v[i].second)max=pt->key_val_v[i].second;
            i++;
          
            if(i>=pt->key_val_v.size()){
                if(pt->right!=0){
                    pt = pt->right;
                   // cout<<"pt->isleaf "<<pt->isleaf<<endl; 
                    i=0;
                }
                else break;
            }
            //cout<<"next compare to"<<pt->key_val_v[i].first<<" value: "<<pt->key_val_v[i].second<<endl;
        }
        if(max==-999999999){file << "no answer" <<endl;}
        else {file << max <<endl;}
        
    }
    file.close();
    
}
 
void Index ::clear_index(){
    do_clear(root);
}
void Index::do_clear(node *pt){
    if(pt->isleaf==1){
        delete(pt);
        return;
    }else{
        for(int i=0;i<pt->pt_v.size();i++){
            do_clear(pt->pt_v[i]);
        }
    }
    delete pt;
}