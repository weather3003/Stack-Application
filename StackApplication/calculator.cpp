#include<iostream>
#include<string>
#include<sstream> 
#include<fstream> 
#include"Stack.h"
using namespace std;

void main()
{
	Stack infixExpressions;
	ifstream infix("infix.txt");
	while (!infix.eof())
	{
		string expression;
		getline(infix, expression);
		infixExpressions.push(expression);
	}
}