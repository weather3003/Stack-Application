#include <string>
#include "Stack.h"
using namespace std;

bool push(stackType);
bool pop(stackType &);	//pop the top of the stack into a stackType reference
stackType getTop();		//return the value of the top of the stack (no removal)
int getCount();			//return how many elements are on the top of the stack