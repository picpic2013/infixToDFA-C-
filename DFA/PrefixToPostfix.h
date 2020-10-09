#pragma once
#include <vector>
#include <string>
#include "Status.h"

class PrefixToPostfix {
public:
	PrefixToPostfix();
	~PrefixToPostfix();
	static STATUS preToPost(std::string, std::vector<char>&);
	static bool isSpecialSign(const char);
	
private:
	static STATUS autoAddChar(const std::string, std::vector<char>&);
	static STATUS isMorePrioer(const char, const char, bool&);
	static STATUS mergeLastTwoNodes(std::vector<std::vector<char> >&, std::vector<char>&);
};