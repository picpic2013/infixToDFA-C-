#include "DFANodeData.h"

DFANodeData::DFANodeData() {
	this->isTermin = false;
}

DFANodeData::DFANodeData(std::set<char> statusSubset) {
	this->statusSubset = statusSubset;
}

DFANodeData::DFANodeData(const DFANodeData& data) {
	this->statusSubset = data.statusSubset;
}

bool DFANodeData::getTerminal() {
	return this->isTermin;
}
STATUS DFANodeData::setTerminal(bool input) {
	this->isTermin = input;
	return STATUS::OK;
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