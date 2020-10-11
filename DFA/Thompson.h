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

//节点，定义成结构体，便于以后扩展
struct state
{
	string StateName;
};

//边，空转换符用'#'表示
struct edge
{
	state StartState;
	state EndState;
	char TransSymbol;
};

//NFA单元
struct cell
{
	edge EdgeSet[MAX];
	int EdgeCount;
	state StartState;
	state EndState;
};

/***************NFA的矩阵结构****************/

struct node
{
	edge* In_edges;
	edge* Out_edges;
	//state
};

/********************************************/

//函数声明
void input(string&);
//表达式转NFA
cell express_2_NFA(string);
//NFA转DFA
cell express_2_DFA(cell);
//处理 a|b
cell do_Unite(cell, cell);
//处理 ab
cell do_Join(cell, cell);
//处理 a*
cell do_Star(cell);
//处理 a
cell do_Cell(char);
//将一个单元的边的集合复制到另一个单元
void cell_EdgeSet_Copy(cell&, cell);
//产生一个新的状态节点，便于管理
state new_StateNode();
//去除重复字母并排序
void Deduplication_char(char* a, int num);
//显示
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