#include <iostream>
using namespace std;

class DataNode{
private:
    bool ExLock;//exclusive lock a.k.a Write-lock
    bool ShLock;//shared lock a.k.a Read-lock
    int Data;
public:
    bool isExLocked(){
        return ExLock;
    }
    bool isShLocked(){
        return ShLock;
    }
    int getData(){
        return Data;
    }
    bool LockEx(){
        if (ExLock == true || ShLock == true)
        {
            cout << "Try to setExLocked, but already ExLocked or ShLocked, operation failed" << endl;
            return false;
        }else{ExLock = true;}
        return true;
    }
    bool LockSh(){
        if (ExLock == true)
        {
            cout << "Try to setShLocked, but already ExLocked, operation failed" << endl;
            return false;
        }else{ShLock = true;}
        return true;
    }
    bool unLockEx(){
        if (ExLock == false){
            cout << "Try to unLockEx, but not ExLocked, operation failed" << endl;
            return false;
       }else{ExLock = false;}
       return true;
        
    }
    bool unLockSh(){
        if (ShLock == false){
            cout << "Try to unLockSh, but not ShLocked, operation failed" << endl;
            return false;
       }else{ShLock = false;}
       return true;    }
    DataNode(){
        ExLock = false;
        ShLock = false;
        Data = -1;
    }
    void updateData(int d){
        Data = d;
    }
};

DataNode * init(int input_data){
    DataNode * newNode;
    newNode = new DataNode;
    newNode->updateData(input_data);
    return newNode;
}

int main(){
    DataNode * Anode = init(87);
    cout << Anode->getData() << endl;
    return 0;
}