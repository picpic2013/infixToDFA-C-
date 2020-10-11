#pragma once

#include "MyGraphWithStartEnd.h"
#include "DFANodeData.h"
#include "Thompson.h"
#include "Status.h"

class DFA : public MyGraphWithStartEnd<DFANodeData, char>
{
public:
	DFA();
	DFA(cell&);

	~DFA();

	STATUS setTerminal(int);
	STATUS setStart(int);
	STATUS DFAMinimise();
	static STATUS isEndNode(DFA, int);
	static STATUS DFAMinimise(DFA&);
	static std::vector<int> getAllTerminal(DFA);
	static std::vector<int> getAllNoTerminal(DFA);

private:
	static STATUS delUnReachNode(DFA&);
};