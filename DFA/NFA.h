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

private:

};