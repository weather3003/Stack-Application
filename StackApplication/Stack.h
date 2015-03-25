/* This header contains the data type definitions for a user-defined
Stack ADT that will be implemented as a dynamic, single linked list.
*/

#include<string>
using std::string;

//the stack will hold strings
typedef string stackType;

struct Node
{
	stackType data;
	Node * next;
};

class Stack
{
public:
	Stack();
	~Stack();
	
	bool push(stackType);	//push a stackType onto the top of the stack
	bool pop(stackType &);	//pop the top of the stack into a stackType reference
	stackType getTop();		//return the value of the top of the stack (no removal)
	int getCount();			//return how many elements are on the top of the stack

private:
	Node * top;
	int count;
};