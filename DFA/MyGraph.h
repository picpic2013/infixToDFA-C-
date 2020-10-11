#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "Status.h"
#include "Node.h"

template <typename NodeDataType, typename EdgeDataType>
class MyGraph {
public:
	MyGraph();
	~MyGraph();
	int addNode(int, NodeDataType = NodeDataType(), bool = false);
	int addNode(Node<NodeDataType, EdgeDataType>&);
	STATUS addEdge(int, int, char = '\0', bool = false);
	STATUS delNode(int);
	STATUS delEdge(int, int);
	friend std::ostream& operator << (std::ostream& out, MyGraph<NodeDataType, EdgeDataType>& graph) {
		out << "Graph: " << std::endl;
		for (auto it = graph.index.begin(); it != graph.index.end(); it++) {
			Node<NodeDataType, EdgeDataType>& tempNode = graph.nodes[it->second];
			out << "\t" << tempNode << std::endl;
			for (auto itt = tempNode.getToEdges().begin(); itt != tempNode.getToEdges().end(); itt++) {
				out << "\t\t" << *itt << std::endl;
			}
			if (tempNode.getToEdges().size() == 0) {
				out << std::endl;
			}
		}
		return out;
	}

protected:
	std::map<int, int> index;
	std::queue<int> availableSpace;
	std::vector<Node<NodeDataType, EdgeDataType> > nodes;
};

#include "MyGraph.cpp"