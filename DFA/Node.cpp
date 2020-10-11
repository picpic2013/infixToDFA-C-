#include "Node.h"

template <typename NodeDataType, typename EdgeDataType>
Node<NodeDataType, EdgeDataType>::Node(int id, const NodeDataType& data) {
	this->id = id;
	this->data = data;
}

template <typename NodeDataType, typename EdgeDataType>
Node<NodeDataType, EdgeDataType>::Node(const Node<NodeDataType, EdgeDataType>& node) {
	this->id = node.id;
	this->fromEdges = node.fromEdges;
	this->toEdges = node.toEdges;
	this->data = node.data;
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

template <typename NodeDataType, typename EdgeDataType>
STATUS Node<NodeDataType, EdgeDataType>::isExistEdge(Edge<EdgeDataType> edge) {
	if (edge.getFromId() == this->getId()) {
		std::vector<Edge<char> >::iterator it = this->getToEdges().begin();
		for (it; it != this->getToEdges().end(); it++) {
			if ((*it).getCondition() == edge.getCondition() && (*it).getToId() == edge.getToId())
				return STATUS::EDGE_IS_EXISTED;
		}
		return STATUS::EDGE_NOT_EXISTED;
	}
	else if (edge.getToId() == this->getId()) {
		std::vector<Edge<char> >::iterator it = this->getFromEdges().begin();
		for (it; it != this->getFromEdges().end(); it++) {
			if ((*it).getCondition() == edge.getCondition() && (*it).getFromId() == edge.getFromId())
				return STATUS::EDGE_IS_EXISTED;
		}
		return STATUS::EDGE_NOT_EXISTED;
	}
	else return STATUS::EDGE_NOT_EXISTED;
}