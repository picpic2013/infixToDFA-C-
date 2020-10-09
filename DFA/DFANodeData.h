#pragma once
#include <iostream>
#include <set>

class DFANodeData {
public:
	std::set<char> statusSubset;
	DFANodeData();
	DFANodeData(std::set<char> statusSubset);
	friend std::ostream& operator << (std::ostream&, DFANodeData&);
};
std::ostream& operator << (std::ostream&, DFANodeData&);