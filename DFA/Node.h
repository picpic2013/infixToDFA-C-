#pragma once
#include <iostream>
#include "Edge.h"

template <typename NodeDataType, typename EdgeDataType>
class Node {
public:
	Node(int id, NodeDataType = NodeDataType());
	~Node();
	int getId() const;
	NodeDataType& getData();
	std::vector<Edge<EdgeDataType> >& getFromEdges();
	std::vector<Edge<EdgeDataType> >& getToEdges();
	STATUS addFromEdge(const Edge<EdgeDataType>&);
	STATUS addToEdge(const Edge<EdgeDataType>&);
	STATUS delFromEdge(int);
	STATUS delToEdge(int);
	friend std::ostream& operator << (std::ostream& out, Node<NodeDataType, EdgeDataType>& node) {
		out << "Node [ " << node.id << " ]: " << node.data;
		return out;
	}

private:
	int id;
	std::vector<Edge<EdgeDataType> > fromEdges;
	std::vector<Edge<EdgeDataType> > toEdges;
	NodeDataType data;
};

#include "Node.cpp"