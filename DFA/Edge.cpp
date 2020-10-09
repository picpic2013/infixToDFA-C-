#include "Edge.h"

Edge::Edge(int fromId, int toId, char condition) {
	this->fromId = fromId;
	this->toId = toId;
	this->condition = condition;
}

Edge::~Edge() {
}

int Edge::getFromId() const {
	return this->fromId;
}

int Edge::getToId() const {
	return this->toId;
}

char Edge::getCondition() const {
	return this->condition;
}

std::ostream& operator << (std::ostream& out, Edge& edge) {
	out << "edge:\tNode [ " << edge.fromId << " ] == '" << edge.condition << "' ==> Node [ " << edge.toId << " ]";
	return out;
}