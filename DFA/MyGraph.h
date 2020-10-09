#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "Status.h"
#include "Node.h"

template <typename DataType>
class MyGraph {
public:
	MyGraph();
	~MyGraph();
	int addNode(int, DataType = DataType(), bool = false);
	int addNode(Node<DataType>&);
	STATUS addEdge(int, int, char = '\0', bool = false);
	STATUS delNode(int);
	STATUS delEdge(int, int);
	friend std::ostream& operator << (std::ostream& out, MyGraph<DataType>& graph) {
		out << "Graph: " << std::endl;
		for (auto it = graph.index.begin(); it != graph.index.end(); it++) {
			Node<DataType>& tempNode = graph.nodes[it->second];
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
	std::vector<Node<DataType> > nodes;
};

#include "MyGraph.cpp"