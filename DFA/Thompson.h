#ifndef THOMPSON_H
#define THOMPSON_H

#include <iostream>
#include <stdio.h>
#include <cctype>
#include <stack>
#include <string>
#include <list>
#include <vector>
#include <queue>

using namespace std;

#define MAX 100

//�ڵ㣬����ɽṹ�壬�����Ժ���չ
struct state
{
	string StateName;
};

//�ߣ���ת������'#'��ʾ
struct edge
{
	state StartState;
	state EndState;
	char TransSymbol;
};

//NFA��Ԫ
struct cell
{
	edge EdgeSet[MAX];
	int EdgeCount;
	state StartState;
	state EndState;
};

/***************NFA�ľ���ṹ****************/

struct node
{
	edge* In_edges;
	edge* Out_edges;
	//state
};

/********************************************/

//��������
void input(string&);
//���ʽתNFA
cell express_2_NFA(string);
//NFAתDFA
cell express_2_DFA(cell);
//���� a|b
cell do_Unite(cell, cell);
//���� ab
cell do_Join(cell, cell);
//���� a*
cell do_Star(cell);
//���� a
cell do_Cell(char);
//��һ����Ԫ�ıߵļ��ϸ��Ƶ���һ����Ԫ
void cell_EdgeSet_Copy(cell&, cell);
//����һ���µ�״̬�ڵ㣬���ڹ���
state new_StateNode();
//ȥ���ظ���ĸ������
void Deduplication_char(char* a, int num);
//��ʾ
void Display_NFA(cell Cell);
void Display_DFA(cell Cell);

void Initialize(vector<edge> &NFA, cell &nfa, int num);
bool check(string str, char x);
string closure(string setp, vector<edge> NFA);
string move(string t, char a, vector<edge> NFA);
bool checkINrawDFA(vector<string> rawDFA, string u);
int checkFlag(vector<bool> t);

state new_DFA_StateNode();
void make_EndState(cell& DFA, vector<string> rawDFA, cell& NFA);


#endif  //THOMPSON.H
#pragma once