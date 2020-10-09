#pragma once
#include <iostream>
#include "Edge.h"

template <typename DataType>
class Node {
public:
	Node(int id, DataType = DataType());
	~Node();
	int getId() const;
	DataType getData() const;
	std::vector<Edge>& getFromEdges();
	std::vector<Edge>& getToEdges();
	STATUS addFromEdge(Edge);
	STATUS addToEdge(Edge);
	STATUS delFromEdge(int);
	STATUS delToEdge(int);
	friend std::ostream& operator << (std::ostream& out, Node<DataType>& node) {
		out << "Node [ " << node.id << " ]: " << node.data;
		return out;
	}

private:
	int id;
	std::vector<Edge> fromEdges;
	std::vector<Edge> toEdges;
	DataType data;
};

#include "Node.cpp"