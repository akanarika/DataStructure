//2016.Jan.14
//Linked List
//by Dandan Du

#include <iostream>
#include <fstream>
using namespace std;

#define DEFAULTSIZE 100

template <class type>
class List{
	private:
		void operator =(const List&) {}
		List(const List&) {}
	public:
		List() {}	//Default constructor
		virtual ~List() {}	//Base deconstructor
		
		//Reinitialize the list. The client is respensible for
		//reclaiming the storage used by the list elements.
		virtual void clear() = 0;

		//Insert an element at the front of the right partition.
		//Return true if the insert was successful, false otherwise.
		virtual void insert(const type&) = 0;

		//Append an element at the end of the right partition.
		//Return true if the append was successful, false otherwise.
		virtual void append(const type&) = 0;

		//Remove and return the first element of the right partition.
		virtual type remove() = 0;

		//Place fence at list start, making left partition empty.
		virtual void movetoStart() = 0;

		//Place fence at list end, making right partition empty.
		virtual void movetoEnd() = 0;

		//Move fence one step left; no change if at beginning.
		virtual void prev() = 0;

		//Move fence one step right; no change if already at end.
		virtual void next() = 0;

		//Return length of left or right partition, respectively.
		virtual int leftLength() const  = 0;
		virtual int rightLength() const = 0;

		//Set fence so that left partition has "pos" elements.
		virtual void movetoPos(int pos) = 0;

		//Return the first element of the right partition.
		virtual const type& getValue() const = 0;

		virtual void traverse() = 0;
};

template <class type>
class Link{
	public:
		Link* next;
		type data;
		
		Link(const type& dataval, Link* nextval = NULL){
			data = dataval;
			next = nextval;
		}
		Link(Link* nextval = NULL){
			next = nextval;
		}
};

template <class type>
class LList : public List<type>{
	private:
		Link<type>* head;
		Link<type>* tail;
		Link<type>* fence;
		int leftcnt;
		int rightcnt;
		void init(){
			head = new Link<type>;
			tail = new Link<type>;
			fence = new Link<type>;
			head = tail = fence;
			leftcnt = rightcnt = 0;
		}
		void removeall(){
			while(head != NULL){
				fence = head;
				head = head->next;
				delete fence;			
			}
		}
	public:
		LList(int size = DEFAULTSIZE) { init();}
		~LList(){ removeall();}
		void clear() { removeall(); init();}
		void insert(const type& it);
		void append(const type& it);
		type remove();
		void movetoStart();
		void movetoEnd();
		void prev();
		void next();
		int leftLength() const;
		int rightLength() const;
		void movetoPos(int pos);
	   	const type& getValue() const;	
		void traverse();
};


class OutOfBound{};

template <class type>
void LList<type>::insert(const type& it){
	fence->next = new Link<type>(it, fence->next);
	if(fence == tail) tail = fence->next;
	++rightcnt;	
}

template <class type>
void LList<type>::append(const type& it){
	tail = tail->next = new Link<type>(it, NULL);
	//tail = tail->next;
	++rightcnt;
}

template <class type>
type LList<type>::remove(){
	if(fence == tail) throw OutOfBound();
	type it = fence->next->data;
	Link<type>* tmp = fence->next;
   	if(fence->next == tail) tail = fence;
	fence->next = fence->next->next;
	delete tmp;
	--rightcnt;
	return it;
}

template <class type>
void LList<type>::movetoStart(){
	fence = head;
	rightcnt += leftcnt;
	leftcnt = 0;
}

template <class type>
void LList<type>::movetoEnd(){
	fence = tail;
	leftcnt += rightcnt;
	rightcnt = 0;
}

template <class type>
void LList<type>::prev(){
	if(fence == head) return;
	Link<type>* tmp = head;
	while(tmp->next!=fence) tmp = tmp->next;
	fence = tmp;
	//delete tmp;
	--leftcnt;
	++rightcnt;
}

template <class type>
void LList<type>::next(){
	if(fence == tail) return;
	fence = fence->next;
	++leftcnt;
	--rightcnt;
}

template <class type>
int LList<type>::leftLength() const{
	return leftcnt;
}

template <class type>
int LList<type>::rightLength() const{
	return rightcnt;
}

template <class type>
void LList<type>::movetoPos(int pos){
	if(pos >= leftcnt+rightcnt || pos < 0) throw OutOfBound();
	fence = head;
	for(int i=0; i<pos; i++){
		fence = fence->next;
	}
	rightcnt = leftcnt + rightcnt - pos;
	leftcnt = pos;
}

template <class type>
const type& LList<type>::getValue() const{
	if(rightLength() <= 0) throw OutOfBound();
	return fence->next->data;
}

template <class type>
void LList<type>::traverse(){
	Link<type>* tmp = head;
	while(tmp != tail){
		cout << tmp->next->data << ",";
		tmp = tmp->next;
	}
	cout << "The size is " << leftcnt + rightcnt << endl;

}

template <class type>
void process(type T_type){
	int size;
	cin >> size;
	LList<type> lList(size);
	type data;
	for(int i=0; i<size; i++){			
		cin >> data;
		lList.append(data);
	}
	lList.traverse();
	cout << lList.remove();
	lList.traverse();
	cout << "Move to End;" << endl;
	lList.movetoEnd();
	cout << "Move to prev;" << endl;
	lList.prev();
	lList.traverse();
	cout << "Insert 100" << endl;
	lList.insert(100);
	lList.traverse();
	cout << "Move to pos 4;" << endl;
	lList.movetoPos(4);
	cout << "Insert 200" << endl;
	lList.insert(200);
	lList.traverse();
	cout << "Move to next" << endl;
	lList.next();
	cout << lList.getValue() << endl;
	cout << "leftLength: " << lList.leftLength() << endl;
	cout << "rightLength: " << lList.rightLength() << endl;
	cout << "Move to start" << endl;
	lList.movetoStart();
	cout << lList.getValue() << endl;
	cout << "leftLength: " << lList.leftLength() << endl;
	cout << "rightLength: " << lList.rightLength() << endl;
	lList.movetoEnd();
	cout << "leftLength: " << lList.leftLength() << endl;
	cout << "rightLength: " << lList.rightLength() << endl;
	lList.traverse();
	lList.prev();
	cout << "leftLength: " << lList.leftLength() << endl;
	cout << "rightLength: " << lList.rightLength() << endl;
	lList.traverse();
	lList.remove();
	lList.traverse();
	lList.clear();
	lList.traverse();
}

int main(){
	ifstream fin("list.in");
	ofstream fout("list.out");
	cin.rdbuf(fin.rdbuf());
	cout.rdbuf(fout.rdbuf());
	char type[8];
	cin >> type;
	switch(type[0]){
		case('i'):
			int T_int;
			process(T_int);
			break;
		case ('c'):
			char T_char;
			process(T_char);
		   	break;
		case('d'):
			double T_double;
			process(T_double);
			break;	
	}
	fin.close();
	fout.close();
	return 0;
}

