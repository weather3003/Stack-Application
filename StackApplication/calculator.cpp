#include<iostream>
#include<string>
#include<sstream> 
#include<fstream> 
#include<queue>
#include"Stack.h"
using namespace std;

void main()
{
	char operators[6] = { '(', ')', '-', '+', '/', '*' };
	queue<string> infixExpressions;

	ifstream infix("infix.txt");
	while (!infix.eof())
	{
		//sets expression and expressionStreamto a string and stringstream of the expression
		string expression;
		getline(infix, expression);
		istringstream expressionStream;
		expressionStream.str(expression);

		infixExpressions.push(expression);

		Stack operatorStack;
		stringstream postfixExpression;
		while (!expressionStream.eof())
		{
			char peek = expressionStream.peek();
			while (isspace(peek))
			{	//ignore whitespace
				expressionStream.ignore();
				peek = expressionStream.peek();
			}


			if (isdigit(peek))
			{
				int operand;
				expressionStream >> operand;
				postfixExpression << operand << " ";
			}
			else if (find(operators, operators + 6, peek) - (operators + 6) ) //if an operator
			{
				string op;
				expressionStream >> op;
				
				if (operatorStack.getCount() > 0 && op != "(") // if operator stack is not empty
				{
					char * stackPrecedence = find(operators, operators + 6, peek);
					char * precedence = find(operators, operators + 6, op[0]);
					while (stackPrecedence > precedence) // while the stack has a greater precedence
					{
						string stackOp = "";
						operatorStack.pop(stackOp);
						postfixExpression << stackOp << " ";
						stackPrecedence = find(operators, operators + 6, expressionStream.peek());
					}
				}
				operatorStack.push(op);
			}
			else
			{
				postfixExpression.str("invalid");
			}
		}
		string stackOp = "";
		while (operatorStack.getCount() > 0)
		{
			operatorStack.pop(stackOp);
			postfixExpression << stackOp << " ";
		}
		cout << postfixExpression.str() << endl;
	}
//	while (!infixExpressions.empty())
//	{
//		cout << infixExpressions.front() << endl;
//		infixExpressions.pop();
//	}
}