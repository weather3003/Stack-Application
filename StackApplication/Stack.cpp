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

stackType Stack::getTop()
{
	if (!top)
		return top->data;
	else
		return NULL;
}

int Stack::getCount()
{
	return count;
}