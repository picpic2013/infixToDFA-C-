#include "Node.h"

template <typename NodeDataType, typename EdgeDataType>
Node<NodeDataType, EdgeDataType>::Node(int id, NodeDataType data) {
	this->id = id;
	this->data = data;
}

template <typename NodeDataType, typename EdgeDataType>
Node<NodeDataType, EdgeDataType>::~Node() {
}

template <typename NodeDataType, typename EdgeDataType>
int Node<NodeDataType, EdgeDataType>::getId() const{
	return this->id;
}

template <typename NodeDataType, typename EdgeDataType>
std::vector<Edge<EdgeDataType> >& Node<NodeDataType, EdgeDataType>::getFromEdges() {
	return this->fromEdges;
}

template <typename NodeDataType, typename EdgeDataType>
std::vector<Edge<EdgeDataType> >& Node<NodeDataType, EdgeDataType>::getToEdges() {
	return this->toEdges;
}

template <typename NodeDataType, typename EdgeDataType>
STATUS Node<NodeDataType, EdgeDataType>::addFromEdge(const Edge<EdgeDataType> &edge) {
	this->fromEdges.push_back(edge);
	return STATUS::OK;
}

template <typename NodeDataType, typename EdgeDataType>
STATUS Node<NodeDataType, EdgeDataType>::addToEdge(const Edge<EdgeDataType> &edge) {
	this->toEdges.push_back(edge);
	return STATUS::OK;
}

template <typename NodeDataType, typename EdgeDataType>
STATUS Node<NodeDataType, EdgeDataType>::delFromEdge(int fromNodeId) {
	std::vector<Edge<EdgeDataType> > tempVector;
	for (auto it = this->fromEdges.begin(); it != this->fromEdges.end(); it++) {
		if (it->getFromId() != fromNodeId) {
			tempVector.push_back(*it);
		}
	}
	this->fromEdges = tempVector;
	return STATUS::OK;
}

template <typename NodeDataType, typename EdgeDataType>
STATUS Node<NodeDataType, EdgeDataType>::delToEdge(int toNodeId) {
	std::vector<Edge<EdgeDataType> > tempVector;
	for (auto it = this->toEdges.begin(); it != this->toEdges.end(); it++) {
		if (it->getToId() != toNodeId) {
			tempVector.push_back(*it);
		}
	}
	this->toEdges = tempVector;
	return STATUS::OK;
}

template <typename NodeDataType, typename EdgeDataType>
NodeDataType& Node<NodeDataType, EdgeDataType>::getData() {
	return this->data;
}