#include "DFA.h"
#include <sstream>

DFA::DFA()
{

}

DFA::DFA(cell& c) : MyGraphWithStartEnd<DFANodeData, char>(false)
{
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

	this->startId = this->endId = -1;

	string temp;
	istringstream in(c.EndState.StateName);
	while (in >> temp) {
		this->setTerminal(c2n[temp]);
	}
}

DFA::~DFA()
{
}

STATUS  DFA::setTerminal(int nodeid) {
	(this->nodes[this->index[nodeid]]).getData().setTerminal(true);
	return STATUS::OK;
}

STATUS DFA::isEndNode(DFA  input, const int nodeid) {
	if (input.index.find(nodeid) != input.index.end())
	{
		if ((((input.nodes[input.index[nodeid]]).getData()).getTerminal()) == true)
			return STATUS::NODE_IS_TERMINAL;
		else return STATUS::NODE_NOT_TERMINAL;
	}
	else return STATUS::NODE_NOT_EXSIST;
}

std::vector<int> DFA::getAllTerminal(DFA input) {
	std::vector<int> tmp;
	while (!tmp.empty()) tmp.pop_back();
	for (std::map<int, int>::iterator it = input.index.begin(); it != input.index.end(); it++)
	{
		STATUS status = DFA::isEndNode(input, (*it).first);
		if (status == STATUS::NODE_IS_TERMINAL)
		{
			tmp.push_back((*it).first);
		}
	}
	return tmp;
}
std::vector<int> DFA::getAllNoTerminal(DFA input) {
	std::vector<int> tmp;
	while (!tmp.empty()) tmp.pop_back();
	for (std::map<int, int>::iterator it = input.index.begin(); it != input.index.end(); it++)
	{
		STATUS status = DFA::isEndNode(input, (*it).first);
		if (status == STATUS::NODE_NOT_TERMINAL)
		{
			tmp.push_back((*it).first);
		}
	}
	return tmp;
}
STATUS DFA::delUnReachNode(DFA& input)
{
	std::queue<int> tmp;
	std::map<int, bool> isReachAbleNode;
	std::set<int> passedNode;
	for (std::map<int, int>::iterator it = input.index.begin(); it != input.index.end(); it++)
	{
		STATUS status = DFA::isEndNode(input, (*it).first);
		if (status == STATUS::NODE_IS_TERMINAL) {
			isReachAbleNode[(*it).first] = 1;
			tmp.push((*it).first);
		}
		else if (status == STATUS::NODE_NOT_TERMINAL) {
			isReachAbleNode[(*it).first] = 0;
		}
		else if (status == STATUS::NODE_NOT_EXSIST) {
			return STATUS::NODE_NOT_EXSIST;
		}
		else return STATUS::ERROR;
	}
	while (!tmp.empty())
	{
		int currentid = tmp.front();
		tmp.pop();
		if (passedNode.find(currentid) != passedNode.end()) {
			continue;
		}
		std::vector<Edge<char> > edge = input.nodes[input.index[currentid]].getFromEdges();
		std::vector<Edge<char> >::iterator itt;
		for (itt = edge.begin(); itt != edge.end(); itt++)
		{
			tmp.push((*itt).getFromId());
			isReachAbleNode[(*itt).getFromId()] = 1;
		}
		passedNode.insert(currentid);
	}
	for (std::map<int, int>::iterator it = input.index.begin(); it != input.index.end(); it++)
	{
		if (isReachAbleNode[(*it).first] == false)
			input.delNode((*it).first);
	}
	return STATUS::OK;
}

STATUS DFA::DFAMinimise(DFA& input)
{
	if (delUnReachNode(input) != STATUS::OK) return STATUS::ERROR;

	int nodeNum = input.index.size();

	//@author:KATE 
	std::vector<std::vector<bool>> pair(nodeNum, std::vector<bool>(nodeNum, false));
	std::map<int, int> pairIndexToNodesIndex; 
	std::map<int, int> NodesIndexTopairIndex; 
	int i = 0;
	for (std::map<int, int>::iterator it = input.index.begin(); it != input.index.end(); it++, i++) {
		pairIndexToNodesIndex[i] = (*it).first;
		NodesIndexTopairIndex[(*it).first] = i;
	}
	std::vector<int> allTerminal = input.getAllTerminal(input);
	std::vector<int> allNoTerminal = input.getAllNoTerminal(input);
	for (auto it = allTerminal.begin(); it != allTerminal.end(); it++) { 
		for (auto itt = allNoTerminal.begin(); itt != allNoTerminal.end(); itt++) {
			pair[NodesIndexTopairIndex[(*it)]][NodesIndexTopairIndex[(*itt)]] = 1;
			pair[NodesIndexTopairIndex[(*itt)]][NodesIndexTopairIndex[(*it)]] = 1;
		}
	}
	
	for (int i = 0; i < nodeNum; i++) {
		for (int j = 0; j < nodeNum; j++) {
			if (pair[i][j] == 1) continue;
			if (i < j) {
				std::vector<Edge<char> > toEdge1 = input.nodes[input.index[pairIndexToNodesIndex[i]]].getToEdges();
				std::vector<Edge<char> > toEdge2 = input.nodes[input.index[pairIndexToNodesIndex[j]]].getToEdges();
				std::map<int, int> condiTo;
				for (auto it = toEdge1.begin(); it != toEdge1.end(); it++) {
					condiTo[(*it).getCondition()] = (*it).getToId();
				}
				for (auto it = toEdge2.begin(); it != toEdge2.end(); it++) {
					if (condiTo.find((*it).getCondition()) == condiTo.end()) {
						pair[i][j] = 1;
					}
					else if (pair[NodesIndexTopairIndex[condiTo[(*it).getCondition()]]][NodesIndexTopairIndex[(*it).getToId()]] == 1) {
						pair[i][j] = 1;
					}
				}
			}
		}
	}

	for (int i = 0; i < nodeNum; i++) {
		for (int j = 0; j < nodeNum; j++) {
			if (i < j && pair[i][j] == 0) { 
				int id1 = pairIndexToNodesIndex[i];
				int id2 = pairIndexToNodesIndex[j];
				if (input.index.find(id1) == input.index.end()) continue;
				std::vector<Edge<char> > fromEdge = input.nodes[input.index[id1]].getFromEdges();
				std::vector<Edge<char> > toEdge = input.nodes[input.index[id1]].getToEdges();
				for (auto it = fromEdge.begin(); it != fromEdge.end(); it++) {
					char condition = (*it).getCondition();
					int fromId = (*it).getFromId();
					Edge edge(fromId, id2, condition);
					if (input.nodes[input.index[id2]].isExistEdge(edge) == STATUS::EDGE_NOT_EXISTED)
						input.addEdge(fromId, id2, condition, false);
				}
				for (auto it = toEdge.begin(); it != toEdge.end(); it++) {
					char condition = (*it).getCondition();
					int toId = (*it).getToId();
					Edge edge(id2, toId, condition);
					if (input.nodes[input.index[id2]].isExistEdge(edge) == STATUS::EDGE_NOT_EXISTED)
						input.addEdge(id2, toId, condition, false);
				}
				input.delNode(id1);
			}
		}
	}
	return STATUS::OK;
}
STATUS  DFA::DFAMinimise() {
	return DFA::DFAMinimise(*this);
}