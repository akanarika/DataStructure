//
//  main.cpp
//  AList
//
//  Created by dandandu on 2016/1/12.
//  Copyright © 2016年 Dandan Du. All rights reserved.
//

#define DEFAULTSIZE 10

#include <iostream>
#include <fstream>
using namespace std;

template <class type>
class List{
public:
    virtual void insert(int index, type data) = 0;
    virtual void append(type data) = 0;
    virtual type remove(int index) = 0;
    virtual type visit(int index) = 0;
    virtual void traverse() = 0;
    virtual void doubleSpace() = 0;
    virtual void clear() = 0;
    virtual ~List() {};
};

class OutOfBound{};
class IllegalSize{};

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
    void insert(int index, type data);
    void append(type data);
    type remove(int index);
    type visit(int index);
    void traverse();
    void doubleSpace();
    void clear();
};

template <class type>
void AList<type>::insert(int index, type data){
    if(index < 0 || index >= listSize) throw OutOfBound();
    if(listSize == maxSize) doubleSpace();
    for(int i=listSize-1; i>index; i--){
        arrayList[i] = arrayList[i-1];
    }
    arrayList[index] = data;
    ++listSize;
}

template <class type>
void AList<type>::append(type data){
    if(listSize == maxSize) doubleSpace();
    arrayList[listSize] = data;
    ++listSize;
}

template <class type>
type AList<type>::remove(int index){
    if(index<0 && index>=listSize) throw OutOfBound();
    type elem = arrayList[index];
    for(int i=index; i<listSize-1; i++){
        arrayList[i] = arrayList[i+1];
    }
    --listSize;
    return elem;    
}

template <class type>
type AList<type>::visit(int index){
    if(index <0 || index >= listSize) throw OutOfBound();
    return arrayList[index];
}

template <class type>
void AList<type>::traverse(){
    for(int i=0; i<listSize; i++){
        cout << arrayList[i] << ",";
    }
    cout << "The size is " << listSize << endl;
}

template <class type>
void AList<type>::doubleSpace(){
    type *tmp = arrayList;
    maxSize *= 2;
    arrayList = new type[maxSize];
    for(int i=0; i<listSize; i++){
        arrayList[i] = tmp[i];
    }
    delete[] tmp;
}

template <class type>
void AList<type>::clear(){
    delete[] arrayList;
    listSize = 0;
    arrayList = new type[maxSize];
}

template <class type>
void process(type t){
    AList<type> alist;
    type data;
    int size;
    cin >> size;
    for(int i=0; i<size; i++){
        cin >> data;
        alist.append(data);
    }
    alist.traverse();
    alist.insert(1,100);
    alist.traverse();
    alist.remove(6);
    alist.traverse();
    alist.append(88);
    alist.traverse();
    alist.append(90);
    alist.traverse();
    alist.clear();
    alist.traverse();
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
