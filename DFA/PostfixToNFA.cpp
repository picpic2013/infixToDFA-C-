#include "PostfixToNFA.h"
#include "PrefixToPostfix.h"

PostfixToNFA::PostfixToNFA() {
}

PostfixToNFA ::~PostfixToNFA() {
}

NFA PostfixToNFA::postfix2NFA(std::vector<char>& input) {
	std::vector<NFA> NFAStack;
	for (std::vector<char>::iterator it = input.begin(); it != input.end(); it++) {
		char w = *it;
		if (PrefixToPostfix::isSpecialSign(w)) {
			if (w == '*') {
				NFA temp = NFAStack.back();
				NFAStack.pop_back();
				NFAStack.push_back(*temp);
			}
			else if (w == '|') {
				NFA temp1 = NFAStack.back();
				NFAStack.pop_back();
				NFA temp2 = NFAStack.back();
				NFAStack.pop_back();
				NFAStack.push_back(temp2 | temp1);
			}
			else if (w == '.') {
				NFA temp1 = NFAStack.back();
				NFAStack.pop_back();
				NFA temp2 = NFAStack.back();
				NFAStack.pop_back();
				NFAStack.push_back(temp2 + temp1);
			}
			else {
				std::cout << "Unknown Error" << std::endl;
				exit(-2);
			}
		} else {
			NFAStack.push_back(NFA(w));
		}
	}
	if (NFAStack.size() != 1) {
		std::cout << "Unknown Error" << std::endl;
		exit(-2);
	}
	return NFAStack.back();
}