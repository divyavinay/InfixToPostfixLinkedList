#pragma once

struct NodeType
{
	char data;
	NodeType* next;
};

class StackType
{
public:
	StackType();
	~StackType();
	void push(char);
	void pop();
	char Top();
	bool isFull() const;
	bool isEmpty() const;
	void print();

private:
	NodeType* TopPtr;
	NodeType* listData;
	
};