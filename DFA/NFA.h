#pragma once

#include "NFANodeData.h"
#include "MyGraphWithStartEnd.h"
#include "Thompson.h"

class NFA : public MyGraphWithStartEnd<NFANodeData, char>
{
public:
	NFA(bool = true);
	NFA(char);
	NFA(const NFA&);
	NFA(const MyGraphWithStartEnd<NFANodeData, char>&);
	NFA(const cell&);
	~NFA();

	cell getCell() const;

	friend std::ostream& operator << (std::ostream& out, NFA& graph) {
		out << "Graph [ start: " << graph.startId << " | end: " << graph.endId << " ]: " << std::endl;
		for (auto it = graph.index.begin(); it != graph.index.end(); it++) {
			Node<NFANodeData, char>& tempNode = graph.nodes[it->second];
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

private:

};