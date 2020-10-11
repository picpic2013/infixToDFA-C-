#pragma once
#include <iostream>

template<typename DataType>
class Edge {
public:
	Edge(int, int, const DataType&);
	Edge(const Edge<DataType>&);
	~Edge();
	int getFromId() const;
	int getToId() const;
	DataType& getCondition();
	friend std::ostream& operator << (std::ostream& out, Edge<DataType>& edge) {
		out << "edge:\tNode [ " << edge.fromId << " ] == '" << edge.condition << "' ==> Node [ " << edge.toId << " ]";
		return out;
	}

private:
	int fromId, toId;
	DataType condition;
};

template<typename DataType>
Edge<DataType>::Edge(int fromId, int toId, const DataType& condition) {
	this->fromId = fromId;
	this->toId = toId;
	this->condition = condition;
}

template<typename DataType>
Edge<DataType>::Edge(const Edge<DataType>& edge) {
	this->fromId = edge.fromId;
	this->toId = edge.toId;
	this->condition = edge.condition;
}

template<typename DataType>
Edge<DataType>::~Edge() {
}

template<typename DataType>
int Edge<DataType>::getFromId() const {
	return this->fromId;
}

template<typename DataType>
int Edge<DataType>::getToId() const {
	return this->toId;
}

template<typename DataType>
DataType& Edge<DataType>::getCondition() {
	return this->condition;
}