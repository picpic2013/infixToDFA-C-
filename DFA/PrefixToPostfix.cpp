#include "PrefixToPostfix.h"

PrefixToPostfix::PrefixToPostfix() {
	
}

PrefixToPostfix::~PrefixToPostfix() {

}

bool PrefixToPostfix::isSpecialSign(const char x) {
	if (x == '*' || x == '.' || x == '|' || x == '(' || x == ')') {
		return true;
	} else {
		return false;
	}
}

STATUS PrefixToPostfix::isMorePrioer(const char x, const char y, bool& result) {
	if (y == '(') {
		result = true;
		return STATUS::OK;
	}
	if (x == '(' || x == ')' || y == '(') {
		result = false;
		return STATUS::ERROR;
	}
	
	switch (x)
	{
	case '*':
		result = true;
		return STATUS::OK;
	case '.':
		if (y == '*') {
			result = false;
			return STATUS::OK;
		} else {
			result = true;
			return STATUS::OK;
		}
	case '|':
		result = false;
		return STATUS::OK;
	default:
		result = false;
		return STATUS::ERROR;
	}
}

// TODO 转义
STATUS PrefixToPostfix::autoAddChar(std::string input, std::vector<char>& output) {
	if (isSpecialSign(input[0]) && input[0] != '(') {
		output = std::vector<char>();
		return STATUS::ERROR;
	}
	output = std::vector<char>();
	// 前后自动加一对括号
	output.push_back('(');
	output.push_back(input[0]);
	for (uint32_t i = 1; i < input.size(); i++) {
		char lastOutputChar = output[output.size() - 1];
		char currentChar = input[i];
		// 字母之间 & 星号后面 & 反括号后面 自动补充连接符
		if ((!isSpecialSign(currentChar) && !isSpecialSign(lastOutputChar)) ||
			((lastOutputChar == '*' || lastOutputChar == ')') && 
			(currentChar == '(' || !isSpecialSign(currentChar)))) {
			output.push_back('.');
			output.push_back(currentChar);
		} else {
			output.push_back(currentChar);
		}
	}
	output.push_back(')');
	return STATUS::OK;
}

STATUS PrefixToPostfix::mergeLastTwoNodes(std::vector<std::vector<char> >& num, std::vector<char>& sig) {
	if (sig.size() == 0) {
		return STATUS::ERROR;
	}
	char lastSign = sig.back();
	sig.pop_back();
	if (num.size() == 0) {
		return STATUS::ERROR;
	}
	std::vector<char> lastNum = num.back();
	num.pop_back();
	// 单目运算符
	if (lastSign == '*') {
		lastNum.push_back('*');
		num.push_back(lastNum);
	} else {
		if (num.size() == 0) {
			return STATUS::ERROR;
		}
		std::vector<char> secondLastNum = num.back();
		num.pop_back();
		for (std::vector<char>::iterator it = lastNum.begin(); it != lastNum.end(); it++) {
			secondLastNum.push_back(*it);
		}
		secondLastNum.push_back(lastSign);
		num.push_back(secondLastNum);
	}
	return STATUS::OK;
}

STATUS PrefixToPostfix::preToPost(std::string input, std::vector<char>& output) {
	std::vector<char> autoAddResult;
	if (PrefixToPostfix::autoAddChar(input, autoAddResult) == STATUS::ERROR) {
		return STATUS::ERROR;
	}

	std::vector<std::vector<char> > num;
	std::vector<char> sig;
	for (std::vector<char>::iterator it = autoAddResult.begin(); it != autoAddResult.end(); it++) {
		char w = *it;
		if (PrefixToPostfix::isSpecialSign(w)) {
			if (sig.size() == 0 && w != '(') {
				return STATUS::ERROR;
			}
			if (w == '(') {
				sig.push_back(w);
			}
			else if (w == ')') {
				while (sig[sig.size() - 1] != '(') {
					if (PrefixToPostfix::mergeLastTwoNodes(num, sig) == STATUS::ERROR) {
						return STATUS::ERROR;
					}
				}
				sig.pop_back();
			}
			else {
				bool tempResult = false;
				if (PrefixToPostfix::isMorePrioer(w, sig[sig.size() - 1], tempResult) == STATUS::ERROR) {
					return STATUS::ERROR;
				}
				if (tempResult) {
					sig.push_back(w);
				}
				else {
					do {
						if (PrefixToPostfix::mergeLastTwoNodes(num, sig) == STATUS::ERROR) {
							return STATUS::ERROR;
						}
						if (PrefixToPostfix::isMorePrioer(w, sig[sig.size() - 1], tempResult) == STATUS::ERROR) {
							return STATUS::ERROR;
						}
					} while (!tempResult);
					sig.push_back(w);
				}
			}
		} else {
			std::vector<char> tempVec;
			tempVec.push_back(w);
			num.push_back(tempVec);
		}
	}
	if (sig.size() != 0 || num.size() != 1) {
		return STATUS::ERROR;
	}
	output = num[0];
	return STATUS::OK;
}