#include "DFANodeData.h"

DFANodeData::DFANodeData() {
	this->isTermin = false;
	this->isStart = false;
}

DFANodeData::DFANodeData(const DFANodeData& data) {
	this->statusSubset = data.statusSubset;
	this->isStart = data.isStart;
	this->isTermin = data.isTermin;
}

bool DFANodeData::getTerminal() const {
	return this->isTermin;
}

bool DFANodeData::getStart() const {
	return this->isStart;
}

STATUS DFANodeData::setTerminal(bool input) {
	this->isTermin = input;
	return STATUS::OK;
}

STATUS DFANodeData::setStart(bool input) {
	this->isStart = input;
	return STATUS::OK;
}

std::ostream& operator << (std::ostream& out, DFANodeData& data) {
	if (data.isStart) {
		out << "( Start Node ) ";
	}
	if (data.isTermin) {
		out << "( Terminal Node ) ";
	}
	return out;
}