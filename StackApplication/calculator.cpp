#include<iostream>
#include<string>
#include<sstream> 
#include<fstream> 
#include<queue>
#include"Stack.h"
using namespace std;

//Matches an operator with it's precedence
struct Operator{
	string name;
	int precedence;
};

//Called to fill an Operator [6] array with the list of operators
void defineOperators(Operator * operators)
{
	//0 reserved for failure aka false aka not an operator
	operators[0].name = "("; operators[0].precedence = 1;
	operators[1].name = "-"; operators[1].precedence = 3;
	operators[2].name = "+"; operators[2].precedence = 3;
	operators[3].name = "*"; operators[3].precedence = 4;
	operators[4].name = "/"; operators[4].precedence = 4;
	operators[5].name = ")"; operators[5].precedence = 2; //Will keep popping until '(' is found
}

//Returns the precedence of an operator; returns zero if failed
int getPrecedence(string op)
{
	Operator operators[6]; defineOperators(operators);
	for (int i = 0; i < 6; i++)
	{
		if (operators[i].name[0] == op[0])	return operators[i].precedence;
	}
	return 0;
}

//tells if a string is a negative number
bool isnegative(string token)
{
	if (token.length() > 1 && token[0] == '-')
		return true;
	else
		return false;
}

//Takes a string expression and returns it's postfix version
string postfix(string expression)
{
	Operator operators[6]; defineOperators(operators);

	istringstream expressionStream;
	expressionStream.str(expression);

	Stack operatorStack;
	stringstream postfixExpression;
	while (!expressionStream.eof())
	{
		string token;
		expressionStream >> token;

		//while (isspace(peek))
		//{	//ignore whitespace
		//	expressionStream.ignore();
		//	peek = expressionStream.peek();
		//}

		if (isdigit(token[0]) || isnegative(token)) //if an operand
		{
			postfixExpression << token << " ";
		}
		else if (getPrecedence(token)) //if an operator
		{														// if operator stack is not empty
			if (operatorStack.getCount() > 0 && token != "(")	// and operator in question is not "("
			{
				int stackPrecedence = getPrecedence(operatorStack.peek());
				int precedence = getPrecedence(token);
				while (stackPrecedence >= precedence) // while the stack has a greater precedence
				{
					string stackOp = "";
					operatorStack.pop(stackOp);
					postfixExpression << stackOp << " ";
					if (operatorStack.getCount() > 0)
						stackPrecedence = getPrecedence(operatorStack.peek());
					else break;
				}
			}
			if (token != ")")
				operatorStack.push(token);
			else
				operatorStack.pop(token); //takes '(' off of stack and does not push ')'
		}
		else
		{						//if for some reason there was
			return "invalid";	//a character that was not recognized
		}
	}
	string stackOp = "";
	while (operatorStack.getCount() > 0)
	{
		operatorStack.pop(stackOp);
		if (stackOp != "(")
			postfixExpression << stackOp << " ";
	}
	
	return postfixExpression.str();
}

void main()
{
	queue<string> infixExpressions;

	ifstream infix("infix.txt");
	while (!infix.eof())
	{
		//sets expression and expressionStreamto a string and stringstream of the expression
		string expression;
		getline(infix, expression);
		infixExpressions.push(expression); //push to queue for later

		cout << postfix(expression) << endl;
		
	}
}