//
//  main.cpp
//  AList
//
//  Created by dandandu on 2016/1/12.
//  Copyright © 2016年 Dandan Du. All rights reserved.
//

#define DEFAULTSIZE 10000

#include <iostream>
#include <fstream>
using namespace std;

template <class type>
class List{
public:
    virtual bool insert(int index, type data) = 0;
    virtual bool append(type data) = 0;
    virtual type remove(int index) = 0;
    virtual void clear() = 0;
    virtual ~List();
};

template <class type>
class AList : public List<type>{
private:
    type *arrayList;
    int maxSize;
    int listSize;
    int fence;
public:
    AList(int size = DEFAULTSIZE){
        arrayList = new type[size];
        maxSize = size;
        listSize = fence = 0;
    }
    ~AList(){ delete[] arrayList;}
    bool insert(int index, type data);
    bool append(type data);
    type remove(int index);
    void clear();
};

template <class type>
bool AList<type>::insert(int index, type data){
    if(index >= 0 && index <= listSize && listSize <= maxSize){
        for(int i=listSize-1; i>index; i--){
            arrayList[i] = arrayList[i-1];
        }
        arrayList[index] = data;
        listSize++;
        return true;
    }else{
        cerr << "Can't insert element!" << endl;
        return false;
    }
    
}

template <class type>
bool AList<type>::append(type data){
    if(listSize <= maxSize){
        arrayList[listSize] = data;
        listSize++;
        return true;
    }else{
        cerr << "The list is full!" << endl;
        return false;
    }
}

template <class type>
type AList<type>::remove(int index){
    if(index >=0 && index < listSize){
        type elem = arrayList[index];
        for(int i=index; i<listSize-1; i++){
            arrayList[i] = arrayList[i+1];
        }
        return elem;
    }else{
        return NULL;
    }
}

template <class type>
void process(type t){
    
}

int main(int argc, const char * argv[]) {
    
    ifstream fin("list.in");
    ofstream fout("list.out");
    
    cin.rdbuf(fin.rdbuf());
    cout.rdbuf(fout.rdbuf());
    char type[8];
    cin >> type;
    switch(type[0]){
            case ('i'):
                int T_int;
                process(T_int);
                break;
            case ('c'):
                char T_char;
                process(T_char);
                break;
            case ('d'):
                double T_double;
                process(T_double);
                break;
    }
    fin.close();
    fout.close();
    return 0;
}
