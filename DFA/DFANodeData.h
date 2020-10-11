#pragma once
#include <iostream>
#include <set>
#include "Status.h"

class DFANodeData {
public:
	DFANodeData();
	DFANodeData(const DFANodeData&);

	bool getTerminal() const;
	bool getStart() const;
	STATUS setTerminal(bool);
	STATUS setStart(bool);

	friend std::ostream& operator << (std::ostream&, DFANodeData&);

	std::set<char> statusSubset;
	bool isTermin;
	bool isStart;
};
std::ostream& operator << (std::ostream&, DFANodeData&);