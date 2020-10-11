#pragma once
#include <iostream>
#include <set>
#include "Status.h"

class DFANodeData {
public:
	DFANodeData();
	DFANodeData(const DFANodeData&);
	DFANodeData(std::set<char> statusSubset);

	bool getTerminal();
	STATUS setTerminal(bool);

	friend std::ostream& operator << (std::ostream&, DFANodeData&);

	std::set<char> statusSubset;
	bool isTermin;

};
std::ostream& operator << (std::ostream&, DFANodeData&);