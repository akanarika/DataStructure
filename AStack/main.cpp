//AStack
//2016.1.16
//by Dandan Du
//

#include <fstream>
#include <iostream>
using namespace std;

#define DEFAULTSIZE 100

template <typename type>
class Stack{
	private:
		void operator =(const Stack&) {}
		Stack(const Stack&) {}
	public:
		Stack() {}
		virtual ~Stack(){}

		//Reinitialize the stack. The user is responsible for
		//reclaiming the storage used by the stack elements.
		virtual void clear() = 0;

		//Push an element onto the top of the stack.
		virtual void push(const type&) = 0;
		
		//Remove and return the element at the top of the stack.
		virtual type pop() = 0;

		//Return a copy of the top element.
		virtual const type& topValue() const = 0;

		//Return the number of elements in the stack.
		virtual int length() const = 0;
};

class OutOfBound{};

template <typename type>
class AStack:public Stack<type>{
	private:
		int maxSize;
		int top;
   		type* listArray;
	public:
		AStack(int size = DEFAULTSIZE){
			maxSize = size; 
			top = 0;
			listArray = new type[size];
		}
		~AStack(){ delete[] listArray;}
		void clear(){ top = 0;};
		void push(const type&);
		type pop();
		const type& topValue() const;
		int length() const;
};

template <typename type>
void AStack<type>::push(const type& it){
	if(top >= maxSize) throw OutOfBound();
	listArray[top++] = it;
}

template <typename type>
type AStack<type>::pop(){
	type it = listArray[--top];
	return it;
}

template <typename type>
const type& AStack<type>::topValue() const{
	return listArray[top-1];
}

template <typename type>
int AStack<type>::length() const{
	return top;
}

template <typename type>
void process(type t){
	AStack<type> aStack;
	int size;
	cin >> size;
	type data;
	for(int i=0; i<size; i++){
		cin >> data;
		aStack.push(data);
		cout << aStack.topValue() << endl;
	}
	cout << "Pop: " << aStack.pop() << endl;
	cout << "Length: " << aStack.length() << endl;
	aStack.push(88);
	cout << "TopValue: " << aStack.topValue() << endl;
	cout << "Pop: " << aStack.pop() << endl;
	cout << "Length: " << aStack.length() << endl;
	cout << "Pop: " << aStack.pop() << endl;
	cout << "Length: " << aStack.length() << endl;
	aStack.clear();
	cout << "Length: " << aStack.length() << endl;
}

int main(){
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
