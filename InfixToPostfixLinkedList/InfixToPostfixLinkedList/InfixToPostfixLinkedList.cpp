// InfixToPostfixLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StackType.h"
#include "fstream"
#include "iostream"
#include "InfixToPostfix.h"

using namespace std;

StackType s1;
ifstream ifile;
InfixToPostfix infixToPostfixObj[10];
ofstream outputfile;
int num = 0;


StackType::StackType()
{
	TopPtr = NULL;
}

StackType::~StackType()
{
	NodeType* tempPtr;
	while (TopPtr != NULL)
	{
		tempPtr = TopPtr;
		TopPtr = TopPtr->next;
		delete tempPtr;
	}
}

bool StackType::isFull() const {
	NodeType* location;
	try
	{
		location = new NodeType;
		delete location;
		return false;
	}
	catch(exception e)
	{
		return true;
	}
}

bool StackType::isEmpty() const
{
	return (TopPtr == NULL);
}

void StackType::pop()
{
	if (isEmpty())
		cout << "Stack full" << endl;
	else
	{
		NodeType* tempPtr;
		tempPtr = TopPtr;
		TopPtr = TopPtr->next;
		delete tempPtr;
	}
}

void StackType::push(char c) 
{
	if (isFull())
		cout << "Stack Full" << endl;
	else
	{
		NodeType* location;
		location = new NodeType;
		location->data = c;
		location->next = TopPtr;
		TopPtr = location;
	}
}

char StackType::Top()
{
	return TopPtr->data;
}

void InfixToPostfix::ReadString()
{
	ifile.open("InputFile.txt");
	char ch;
	char infix[30];
	int i = 0;

	if (!ifile.is_open())
	{
		cout << "Input file connection failed.Check if the file exists" << endl;
		return;
	}
	cout << "Fetching data" << endl;
	while (!ifile.eof())
	{
		while (ifile.get(ch))
		{

			if (ch != ';' && ch != '.' && ch != ' ' && ch != '\n' && ch !='\0')
			{
				infix[i] = ch;
				i++;
			}
			/*else if (ch == '\n')
				i++;*/
			else if (ch == ';' || ch == '.')
			{
				infix[i] = '\0'; // signifies end of string
				infixToPostfixObj[num].infix = infix;
				num++;
				i = 0;
				ch = NULL;
			}
		}
	}
}

int weight(char opr)
{
	switch (opr)
	{
	case '*':
	case '/': return 2;
	case '+':
	case '-':return 1;
	default:return 0;
	}
}

void InfixToPostfix::InfixToPostfixCon(InfixToPostfix obj)
{
	char in_char;
	int i=0,k=0,type = 0;
	int length = obj.infix.length();
	do
	{
		in_char = obj.infix[i];
		if (in_char == '(')
		{
			s1.push(in_char);
			i++;
			continue;
		}
		if (in_char == ')')
		{
			while (!s1.isEmpty() && s1.Top() != '(' && s1.Top() != ')' && s1.Top() != -52)
			{
				obj.postfix[k] = s1.Top();
				k++;
				s1.pop();
			}
			if (s1.Top() == '(')
				s1.pop();
			i++;
			continue;
		}

		type = weight(in_char);
		if (type == 0 && in_char != -52)
		{
			obj.postfix[k] = in_char;
			k++;
			i++;
			continue;
		}
		else
		{
			if (s1.isEmpty())
				s1.push(in_char);
			else
			{
				while (!s1.isEmpty() && s1.Top() != '(' && s1.Top() != ')' && type <= weight(s1.Top()) && in_char != -52)
				{
					obj.postfix[k] = s1.Top();
					k++;
					s1.pop();
					continue;
				}
				if (!s1.isEmpty())
				{
					if (s1.Top() != ')')
						s1.push(in_char);
				} 
				else
					s1.push(in_char);
			}
			i++;
		}
	} while (i != length && in_char != -52);

	while (!s1.isEmpty())
	{
		if (s1.Top() != '(' && s1.Top() != ')' && s1.Top() != -52 )
		{ 
			obj.postfix[k] = s1.Top();
			k++;
		}
		s1.pop();
	}

	outputToFile(obj);
	cout << obj.postfix << endl;
}

void InfixToPostfix::outputToFile(InfixToPostfix obj)
{
	
	outputfile << "Infix :" << obj.infix <<endl;
	outputfile << "Postfix:" << obj.postfix << endl;
	outputfile << endl;
	
}

void StackType:: print()
{
	NodeType* location;
	location = TopPtr;
	while (location != NULL)
	{
		cout << location->data << endl;
		location = location->next;
	}
}


int main()
{

	infixToPostfixObj[num].ReadString();
	outputfile.open("Result.txt");
	for (int i = 0; i < num; i++)
	{
		StackType();
		infixToPostfixObj[i].InfixToPostfixCon(infixToPostfixObj[i]);
	}
	getchar();
    return 0;
}

