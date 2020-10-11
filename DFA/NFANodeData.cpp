#include "NFANodeData.h"

NFANodeData::NFANodeData() {
}

NFANodeData::NFANodeData(const NFANodeData& data) {
}

NFANodeData::~NFANodeData() {
}

std::ostream& operator << (std::ostream& out, NFANodeData& data) {
	return out;
}