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
	//0 precedence reserved for failure aka false aka not an operator
	operators[0].name = "("; operators[0].precedence = 1;
	operators[1].name = "-"; operators[1].precedence = 3;
	operators[2].name = "+"; operators[2].precedence = 3;
	operators[3].name = "*"; operators[3].precedence = 4;
	operators[4].name = "/"; operators[4].precedence = 4;
	operators[5].name = ")"; operators[5].precedence = 2; //Will keep popping until '(' is found
}

//Returns the precedence of an operator; returns zero if failed; almost redundanted by below
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
			if (token  != ")")
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

//Gives the solution to a postfix expression
string solution(string expression)
{
	string errorMessage = "invalid infix expression";
	if (expression == "invalid") return errorMessage;

	Operator operators[6]; defineOperators(operators);

	istringstream expressionStream;
	expressionStream.str(expression);

	Stack operandStack;
	while (!expressionStream.eof())
	{
		string token;
		expressionStream >> token;

		if (isdigit(token[0]) || isnegative(token)) //if an operand
		{
			operandStack.push(token);
		}
		else if (getPrecedence(token)) //if an operator and there is a sufficient number of operands
		{
			string operand1 = ""; string operand2 = "";
			if (operandStack.pop(operand2) && operandStack.pop(operand1))
			{
				int result;  int op1 = stoi(operand1); int op2 = stoi(operand2); char operation = token[0];
				
				if      (operation == '+') result = op1 + op2;
				else if (operation == '-') result = op1 - op2;
				else if (operation == '*') result = op1 * op2;
				else if (operation == '/' && op2 != 0) result = (float)op1 / op2 + .5;

				operandStack.push(to_string(result));
			}
			else return errorMessage;
		}
		else return errorMessage;
	}
	string result = ""; operandStack.pop(result);

	if (operandStack.getCount() == 1)
		return result;
	else return errorMessage;
}

void main()
{
	queue<string> infixExpressions;
	queue<string> answers;
	ifstream infix("infix.txt");

	while (!infix.eof())
	{
		string expression; getline(infix, expression);//read expression
		infixExpressions.push(expression); //push original equation to queue for later
		answers.push(solution(postfix(expression))); //push answer to queue for later	
	}

	int length = answers.size(); //Note here that the last one will always be invalid and shoud never be printed
	for (int i = 1; i < length; i++)
	{
		string expression = infixExpressions.front(); infixExpressions.pop();
		string answer = answers.front(); answers.pop();
		cout << i << ") " << expression << " = " << answer << endl;
	}
}