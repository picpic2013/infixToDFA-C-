#pragma once
#include <iostream>

class NFANodeData {
public:
	NFANodeData();
	friend std::ostream& operator << (std::ostream&, NFANodeData&);
};
std::ostream& operator << (std::ostream&, NFANodeData&);