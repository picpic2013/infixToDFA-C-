#pragma once
#include "MyGraph.h"

template <typename DataType>
MyGraph<DataType>::MyGraph() {
}

template <typename DataType>
MyGraph<DataType>::~MyGraph() {
}

template <typename DataType>
int MyGraph<DataType>::addNode(int nodeId, DataType data, bool autoCover) {
	if (nodeId < 0 && !autoCover) {
		nodeId = 0;
	}
	if (this->index.find(nodeId) == this->index.end()) {
		if (this->availableSpace.empty()) {
			this->nodes.push_back(Node<DataType>(nodeId, data));
			this->index.insert(std::pair<int, int>(nodeId, this->nodes.size() - 1));
		}
		else {
			int availableIndex = this->availableSpace.front();
			this->availableSpace.pop();
			this->nodes[availableIndex] = Node<DataType>(nodeId, data);
			this->index.insert(std::pair<int, int>(nodeId, availableIndex));
		}
	}
	else {
		if (autoCover) {
			this->nodes.push_back(Node<DataType>(nodeId, data));
			this->index[nodeId] = this->nodes.size() - 1;
		}
		else {
			nodeId = (--this->index.end())->first + 1;
			this->nodes.push_back(Node<DataType>(nodeId, data));
			this->index.insert(std::pair<int, int>(nodeId, this->nodes.size() - 1));
		}
	}
	return nodeId;
}
template <typename DataType>
int MyGraph<DataType>::addNode(Node<DataType>& newNode) {
	return this->addNode(newNode.getId(), newNode.getData(), false);
}

template <typename DataType>
STATUS MyGraph<DataType>::addEdge(int fromId, int toId, char condition, bool autoAddNode) {
	if (this->index.find(fromId) == this->index.end()) {
		if (autoAddNode) {
			this->addNode(fromId);
		}
		else {
			return STATUS::NODE_NOT_EXSIST;
		}
	}
	if (this->index.find(toId) == this->index.end()) {
		if (autoAddNode) {
			this->addNode(toId);
		}
		else {
			return STATUS::NODE_NOT_EXSIST;
		}
	}
	this->nodes[this->index[fromId]].addToEdge(Edge(fromId, toId, condition));
	this->nodes[this->index[toId]].addFromEdge(Edge(fromId, toId, condition));
	return STATUS::OK;
}

// Warning: 复杂度高
template <typename DataType>
STATUS MyGraph<DataType>::delNode(int nodeId) {
	std::map<int, int>::iterator it = this->index.find(nodeId);
	if (it == this->index.end()) {
		return STATUS::NODE_NOT_EXSIST;
	}

	for (auto itt = this->nodes[it->second].getFromEdges().begin(); 
		itt != this->nodes[it->second].getFromEdges().end(); itt++) {
		this->nodes[this->index[itt->getFromId()]].delToEdge(it->first);
	}

	for (auto itt = this->nodes[it->second].getToEdges().begin();
		itt != this->nodes[it->second].getToEdges().end(); itt++) {
		this->nodes[this->index[itt->getToId()]].delFromEdge(it->first);
	}

	this->availableSpace.push(it->second);
	this->index.erase(it);
	return STATUS::OK;
}

// Warning: 复杂度高
template <typename DataType>
STATUS MyGraph<DataType>::delEdge(int fromNodeId, int toNodeId) {
	if (this->index.find(fromNodeId) == this->index.end() || this->index.find(toNodeId) == this->index.end()) {
		return STATUS::NODE_NOT_EXSIST;
	}
	this->nodes[this->index[fromNodeId]].delToEdge(toNodeId);
	this->nodes[this->index[toNodeId]].delFromEdge(fromNodeId);
	return STATUS::OK;
}