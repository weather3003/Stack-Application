#include <string>
#include "Stack.h"
using namespace std;

Stack::Stack()
{
	top = NULL;
	count = 0;
}
Stack::~Stack()
{
	while (top != NULL)
	{
		Node * deletion = top;
		top = top->next;
		delete deletion;
	}
}

bool Stack::push(stackType newData)
{
	Node * insertion = new Node; if (!insertion) return false;
	insertion->data = newData;
	insertion->next = top;
	top = insertion;
	count++;

	return true;
}

bool Stack::pop(stackType & destination)
{
	if (count == 0)
		return false;
	else
	{
		destination = top->data;
		Node * deletion = top;
		top = top->next;
		delete deletion;
		count--;
		return true;
	}
}

stackType Stack::peek()
{
	//If Google is to be trusted then this should crash program in
	//debug mode (but not give any overhead otherwise) and is a better
	//way of bug checking rather than relying on the compiler
	//and lets users know when they made a mistake easily
	_ASSERT(count > 0);		
	return top->data;
}

int Stack::getCount()
{
	return count;
}