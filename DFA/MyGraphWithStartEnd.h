#pragma once
#include "MyGraph.h"
#include "NFANodeData.h"
#include "DFANodeData.h"
#include <xkeycheck.h>

template <typename DataType>
class MyGraphWithStartEnd : public MyGraph<DataType> {
public:
	MyGraphWithStartEnd();
	MyGraphWithStartEnd(char);
	~MyGraphWithStartEnd();

	int getStartId() const {
		return this->startId;
	}

	int getEndId() const {
		return this->endId;
	}

	bool isStartNode(int nodeId) {
		return nodeId == this->startId;
	}

	bool isEndNode(int nodeId) {
		return nodeId == this->endId;
	}
	
	friend MyGraphWithStartEnd<DataType> operator + (MyGraphWithStartEnd<DataType> a, MyGraphWithStartEnd<DataType> b) {
		MyGraphWithStartEnd<DataType> res;
		std::map<int, int> a2new, b2new;
		for (auto it = a.nodes.begin(); it != a.nodes.end(); it++) {
			int oldId = it->getId();
			int newId = res.addNode(*it);
			a2new.insert(std::pair<int, int>(oldId, newId));
		}

		for (auto it = b.nodes.begin(); it != b.nodes.end(); it++) {
			int oldId = it->getId();
			int newId = res.addNode(*it);
			b2new.insert(std::pair<int, int>(oldId, newId));
		}

		for (auto it = a.nodes.begin(); it != a.nodes.end(); it++) {
			for (auto itt = it->getToEdges().begin(); itt != it->getToEdges().end(); itt++) {
				res.addEdge(a2new[itt->getFromId()], a2new[itt->getToId()], itt->getCondition());
			}
		}

		for (auto it = b.nodes.begin(); it != b.nodes.end(); it++) {
			for (auto itt = it->getToEdges().begin(); itt != it->getToEdges().end(); itt++) {
				res.addEdge(b2new[itt->getFromId()], b2new[itt->getToId()], itt->getCondition());
			}
		}

		res.addEdge(res.getStartId(), a2new[a.getStartId()]);
		res.addEdge(a2new[a.getEndId()], b2new[b.getStartId()]);
		res.addEdge(b2new[b.getEndId()], res.getEndId());
		return res;
	}

	friend MyGraphWithStartEnd<DataType> operator | (MyGraphWithStartEnd<DataType> a, MyGraphWithStartEnd<DataType> b) {
		MyGraphWithStartEnd<DataType> res;
		std::map<int, int> a2new, b2new;
		for (auto it = a.nodes.begin(); it != a.nodes.end(); it++) {
			int oldId = it->getId();
			int newId = res.addNode(*it);
			a2new.insert(std::pair<int, int>(oldId, newId));
		}

		for (auto it = b.nodes.begin(); it != b.nodes.end(); it++) {
			int oldId = it->getId();
			int newId = res.addNode(*it);
			b2new.insert(std::pair<int, int>(oldId, newId));
		}

		for (auto it = a.nodes.begin(); it != a.nodes.end(); it++) {
			for (auto itt = it->getToEdges().begin(); itt != it->getToEdges().end(); itt++) {
				res.addEdge(a2new[itt->getFromId()], a2new[itt->getToId()], itt->getCondition());
			}
		}

		for (auto it = b.nodes.begin(); it != b.nodes.end(); it++) {
			for (auto itt = it->getToEdges().begin(); itt != it->getToEdges().end(); itt++) {
				res.addEdge(b2new[itt->getFromId()], b2new[itt->getToId()], itt->getCondition());
			}
		}

		res.addEdge(res.getStartId(), a2new[a.getStartId()]);
		res.addEdge(res.getStartId(), b2new[b.getStartId()]);
		res.addEdge(a2new[a.getEndId()], res.getEndId());
		res.addEdge(b2new[b.getEndId()], res.getEndId());
		return res;
	}

	MyGraphWithStartEnd<DataType> operator * () {
		MyGraphWithStartEnd<DataType> res;
		std::map<int, int> a2new;
		for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {
			int oldId = it->getId();
			int newId = res.addNode(*it);
			a2new.insert(std::pair<int, int>(oldId, newId));
		}

		for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {
			for (auto itt = it->getToEdges().begin(); itt != it->getToEdges().end(); itt++) {
				res.addEdge(a2new[itt->getFromId()], a2new[itt->getToId()], itt->getCondition());
			}
		}

		res.addEdge(res.getStartId(), a2new[this->getStartId()]);
		res.addEdge(a2new[this->getEndId()], a2new[this->getStartId()]);
		res.addEdge(a2new[this->getEndId()], res.getEndId());
		res.addEdge(res.getStartId(), res.getEndId());
		return res;
	}
	
	friend std::ostream& operator << (std::ostream& out, MyGraphWithStartEnd<DataType>& graph) {
		out << "Graph [ start: " << graph.startId << " | end: " << graph.endId << " ]: " << std::endl;
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

private:
	int startId, endId;
};

template <typename DataType>
MyGraphWithStartEnd<DataType>::MyGraphWithStartEnd() {
	this->addNode(0);
	this->addNode(1);

	this->startId = 0;
	this->endId = 1;
}

template <typename DataType>
MyGraphWithStartEnd<DataType>::MyGraphWithStartEnd(char singleChar) {
	this->addNode(0);
	this->addNode(1);

	this->startId = 0;
	this->endId = 1;

	this->addEdge(startId, endId, singleChar);
}

template <typename DataType>
MyGraphWithStartEnd<DataType>::~MyGraphWithStartEnd() {
}

typedef MyGraphWithStartEnd<NFANodeData> NFA;
typedef MyGraphWithStartEnd<DFANodeData> DFA;