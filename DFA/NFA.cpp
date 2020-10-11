#include "NFA.h"

NFA::NFA(bool autoInitNode) : MyGraphWithStartEnd<NFANodeData, char>::MyGraphWithStartEnd(autoInitNode)
{
}

NFA::NFA(char condition) : MyGraphWithStartEnd<NFANodeData, char>::MyGraphWithStartEnd(condition)
{
}

NFA::NFA(const NFA& nfa) : MyGraphWithStartEnd<NFANodeData, char>::MyGraphWithStartEnd(nfa)
{
}

NFA::NFA(const MyGraphWithStartEnd<NFANodeData, char>& graph)
	: MyGraphWithStartEnd<NFANodeData, char>::MyGraphWithStartEnd(graph)
{
}

NFA::NFA(const cell& c) : MyGraphWithStartEnd<NFANodeData, char>::MyGraphWithStartEnd(false) {
	map<string, int> c2n;
	int nowId = 0, id = -1;
	for (int i = 0; i < c.EdgeCount; i++) {
		std::string startState = c.EdgeSet[i].StartState.StateName;
		std::string endState = c.EdgeSet[i].EndState.StateName;

		if (c2n.find(startState) == c2n.end()) {
			c2n.insert(std::pair<string, int>(startState, nowId));
			this->addNode(nowId);
			nowId++;
		}
		if (c2n.find(endState) == c2n.end()) {
			c2n.insert(std::pair<string, int>(endState, nowId));
			this->addNode(nowId);
			nowId++;
		}
	}

	for (int i = 0; i < c.EdgeCount; i++) {
		std::string startState = c.EdgeSet[i].StartState.StateName;
		std::string endState = c.EdgeSet[i].EndState.StateName;
		char symbol = c.EdgeSet[i].TransSymbol;
		if (symbol == '#') {
			symbol = '\0';
		}

		this->addEdge(c2n[startState], c2n[endState], symbol, true);
	}

	this->startId = c2n[c.StartState.StateName];
	this->endId = c2n[c.EndState.StateName];
}

NFA::~NFA()
{
}

cell NFA::getCell() const {
	cell res;
	/*for (auto it = this->index.begin(); it != this->index.end(); it++) {
		for (auto itt = this->nodes[it->second].getToEdges().begin(); itt != this->nodes[it->second].getToEdges().end(); itt++) {

		}
	}*/
	return res;
}