#include "DFANodeData.h"

DFANodeData::DFANodeData() {
}

DFANodeData::DFANodeData(std::set<char> statusSubset) {
	this->statusSubset = statusSubset;
}

std::ostream& operator << (std::ostream& out, DFANodeData& data) {
	out << "status subset: { ";
	std::set<char>::iterator it = data.statusSubset.begin();
	if (it != data.statusSubset.end()) {
		out << *it;
		it++;
		for (; it != data.statusSubset.end(); it++) {
			out << ", " << *it;
		}
	}
	out << " }";
	return out;
}