#pragma once
#include "NFA.h"
#include <vector>

class PostfixToNFA {
public:
	PostfixToNFA();
	~PostfixToNFA();

	static NFA postfix2NFA(std::vector<char>&);
private:

};