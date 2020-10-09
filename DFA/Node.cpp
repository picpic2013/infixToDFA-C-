#include "Node.h"

template <typename DataType>
Node<DataType>::Node(int id, DataType data) {
	this->id = id;
	this->data = data;
}

template <typename DataType>
Node<DataType>::~Node() {
}

template <typename DataType>
int Node<DataType>::getId() const{
	return this->id;
}

template <typename DataType>
std::vector<Edge>& Node<DataType>::getFromEdges() {
	return this->fromEdges;
}

template <typename DataType>
std::vector<Edge>& Node<DataType>::getToEdges() {
	return this->toEdges;
}

template <typename DataType>
STATUS Node<DataType>::addFromEdge(Edge edge) {
	this->fromEdges.push_back(edge);
	return STATUS::OK;
}

template <typename DataType>
STATUS Node<DataType>::addToEdge(Edge edge) {
	this->toEdges.push_back(edge);
	return STATUS::OK;
}

template <typename DataType>
STATUS Node<DataType>::delFromEdge(int fromNodeId) {
	std::vector<Edge> tempVector;
	for (std::vector<Edge>::iterator it = this->fromEdges.begin(); it != this->fromEdges.end(); it++) {
		if (it->getFromId() != fromNodeId) {
			tempVector.push_back(*it);
		}
	}
	this->fromEdges = tempVector;
	return STATUS::OK;
}

template <typename DataType>
STATUS Node<DataType>::delToEdge(int toNodeId) {
	std::vector<Edge> tempVector;
	for (std::vector<Edge>::iterator it = this->toEdges.begin(); it != this->toEdges.end(); it++) {
		if (it->getToId() != toNodeId) {
			tempVector.push_back(*it);
		}
	}
	this->toEdges = tempVector;
	return STATUS::OK;
}

template <typename DataType>
DataType Node<DataType>::getData() const {
	return this->data;
}