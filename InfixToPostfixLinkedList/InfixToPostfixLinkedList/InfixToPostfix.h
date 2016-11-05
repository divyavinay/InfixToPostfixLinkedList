
#include "iostream"
#include "stdafx.h"
#include <string>
using namespace std;

class InfixToPostfix
{
public:
	void InfixToPostfixCon(InfixToPostfix obj);
	void ReadString();
	void outputToFile(InfixToPostfix obj);
	

private:
	string infix;
	char postfix[30];
}; 
