#include "Deque.h"
#include <iostream>
using namespace std;

// Default Constructor (creates a new empty Dequeue)
Deque::Deque(){
	left_p = NULL;							// points to left end node
	right_p = NULL;							// points to right end node
	cursor = NULL;							// points to current node
	current_size = 0;
}

// Copy Constructor (creates a deep copy of a deque)
Deque::Deque(const Deque& dq){
	if(dq.current_size == 0){					// if deque is empty
		Deque();				
		return;
	}
	
	int value;							// data for a node
	current_size = dq.current_size;					// setting size
	node* new_node;							// node that will be a copy from dq
	node* temp = dq.left_p;						// temp gets the values from dq
	value = temp -> data;						// getting data from dq
	new_node = new node(value, NULL, NULL);				// creating new node with left-end node value of dq
	left_p = new_node;						// left-end node is new_node
	
	do{
		if(temp == dq.cursor){					// if left-end node = cursor			
			cursor = new_node;		
		}
		if(temp -> next == NULL){           			// if temp is the only node
        		right_p = new_node;
        		return;
    		}
		temp = temp -> next;
		value = temp -> data;
		new_node -> next = new node(value, new_node, NULL);
		right_p = new_node;					// new_node is right most node
		new_node = new_node -> next;				// moving to the next node
	}while(temp -> next != NULL);					// while next node is not null
}

// Deconstructor
Deque::~Deque(){
	while(left_p != NULL){						// while there are still nodes in the queue
		node* temp = left_p;					// tempoaray pointer to current left-end node
		left_p = left_p -> next;				// set left_p to the next node
		delete temp;						// delete what temp points to (left-end node)
		temp = left_p;
	}
}

// Inserts <item> at left end
void Deque::push_left(int item){
	node* new_node = new node(item, NULL, NULL);			// creating a pointer to a new node
	if(empty()){
		cursor = left_p = right_p = new_node;	// if list empty, the cursor and left/right-end node = new_node
	}	
	else{
		new_node -> next = left_p;				// node next to new_node = previous left-end node (left_p)
		left_p -> prev = new_node;				// previous left-end node now has new_node before it
		left_p = new_node;					// new_node is the new left-end node
	}
	current_size++;	
}

// Inserts <item> at right end
void Deque::push_right(int item){
	node* new_node = new node(item, NULL, NULL);			// creating a pointer to a new node
	if(empty()){
		cursor = left_p = right_p = new_node;			// if list empty, the cursor and left/right-end node = new_node
	}	
	else{
		right_p -> next = new_node;				// node next to previous right-end node = new_node
		new_node -> prev = right_p;				// node before new_node = previous right-end node
		right_p = new_node;					// new_node is the new right-end-node
	}
	current_size++;				
}

// Remove item on left end
int Deque::pop_left(){
	if(cursor == left_p){						// if cursor points to left-end node
		cursor = left_p -> next;				// move cursor to next node
	}
	if(empty()){		
		cout << "Deque Empty." << endl;
		return 0;
	}
	int left_val = left_p -> data;					// value in left-end node
	node* left_node = left_p;					// creating a pointer to current left-end-nod
	if(left_p -> next != NULL){					// if left_p has a node after it
		left_p = left_p -> next;				// new left-end node = node after previous left-end node
		left_p -> prev = NULL;					// node before new left-end node = NULL
	}
	else{
		left_p = NULL;						// if left-end node has no node after it (ie. its the only node)
	}
	current_size--;	
	delete left_node;						// deallocated the object pointed to by left_node
	return left_val;
}

// Remove item on right end
int Deque::pop_right(){
	if(cursor == right_p){						// if cursor points to right-end node
		cursor = right_p -> prev;				// move cursor to previous node
	}
	if(empty()){		
		cout << "Deque Empty." << endl;
		return 0;
	}
	int right_val = right_p -> data;				// value in right-end node
	node* right_node = right_p;					// creating a pointer to current right-end nod
	if(right_p -> prev != NULL){					// if right_p has a node before it
		right_p = right_p -> prev;				// new right-end-node = node before previous right-end node
		right_p -> next = NULL;					// node after new right-end node = NULL
	}
	else{
		right_p = NULL;						// if right-end-node has no node before it (ie. its the only node)
	}
	current_size--;	
	delete right_node;						// deallocate the object pointed to by right_node
	return right_val;
}

// Returns true iff the Deque contains no items
bool Deque::empty(){
	if(current_size == 0){
		return true;
	}
	else{
		return false;
	}
}

// Returns the current number of items in the deque
int Deque::size(){
	return current_size;
}

// Move cursor left
bool Deque::cursor_left(){
	if (cursor -> prev != NULL){					// if the cursor has node before it 
		cursor = cursor -> prev;				// move the cursor to that node
		return true;
	}
	else{
		return false;
	}
}

// Move cursor right
bool Deque::cursor_right(){
	if (cursor -> next != NULL){					// if the cursor has a node after it
		cursor = cursor -> next;				// move the cursor to that node
		return true;
	}
	else{
		return false;
	}
}

// Returns the left-most item without removing it
int Deque::peek_left(){
	return left_p -> data;	
}

// Returns the right-most item without removing it
int Deque::peek_right(){
	return right_p -> data;	
}

// Return value the cursor currently is at
int Deque::get_cursor(){
	return cursor -> data;	
}

// Changes value of cursor data
void Deque::set_cursor(int item){
	if(empty() != true){
		cursor -> data = item;
	}
}

// Prints a depiction of the deque contents to standard output
void Deque::display(){
	if(empty()){
		cout << "[] size=0, cursor=NULL" << endl;
	}
	else{
		node* temp = left_p;
		cout << "[";
		while(temp != NULL){	
			cout << temp -> data << ";";
			temp = temp -> next;
		}	
		cout << "]";
		cout << " size = " << current_size << ",";
		cout << " cursor=" << cursor -> data;
		cout << endl;
	}
}

// Like display, but includes node addresses and pointer values
void Deque::verbose_display(){
	if(empty()){
		cout << "[] size=0, cursor=NULL"  << " " << &cursor << " " << cursor << endl;
	}
	else{
		node* temp = left_p;
		cout << "[";
		while(temp != NULL){	
			cout << temp -> data << " " << &temp << " " << temp << "; ";
			temp = temp -> next;
		}	
		cout << "]";
		cout << " size = " << current_size << ",";
		cout << " cursor=" << cursor -> data << " " << &cursor << " " << cursor;
		cout << endl;
	}
}

