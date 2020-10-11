#pragma once
#include <iostream>

class NFANodeData {
public:
	NFANodeData();
	NFANodeData(const NFANodeData&);
	~NFANodeData();
	friend std::ostream& operator << (std::ostream&, NFANodeData&);
};
std::ostream& operator << (std::ostream&, NFANodeData&);