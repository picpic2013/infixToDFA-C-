#pragma once
#include <iostream>

class Edge {
public:
	Edge(int, int, char);
	~Edge();
	int getFromId() const;
	int getToId() const;
	char getCondition() const;
	friend std::ostream& operator << (std::ostream&, Edge&);

private:
	int fromId, toId;
	char condition;
};
std::ostream& operator << (std::ostream&, Edge&);