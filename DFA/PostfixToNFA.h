#pragma once
#include "MyGraphWithStartEnd.h"
#include <vector>

class PostfixToNFA {
public:
	PostfixToNFA();
	~PostfixToNFA();

	static NFA postfix2NFA(std::vector<char>&);
private:

};