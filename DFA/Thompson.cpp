#include "Thompson.h"
;
int STATE_NUM = 0;
int DFA_STATE_NUM = 0;
int char_count = 0;
char Character_Set[20] = { NULL };

int sum11 = 0;//新集合元素个数

//表达式转NFA处理函数,返回最终的NFA结合
cell express_2_NFA(string expression)
{
	int length = expression.size();
	char element;
	cell Cell, Left, Right;
	stack<cell> STACK;
	for (int i = 0; i < length; i++)
	{
		element = expression.at(i);
		switch (element)
		{
		case '|':
			Right = STACK.top();
			STACK.pop();
			Left = STACK.top();
			STACK.pop();
			Cell = do_Unite(Left, Right);
			STACK.push(Cell);
			break;
		case '*':
			Left = STACK.top();
			STACK.pop();
			Cell = do_Star(Left);
			STACK.push(Cell);
			break;
		case '+':
			Right = STACK.top();
			STACK.pop();
			Left = STACK.top();
			STACK.pop();
			Cell = do_Join(Left, Right);
			STACK.push(Cell);
			break;
		default:
			Character_Set[char_count++] = element;
			Cell = do_Cell(element);
			STACK.push(Cell);
		}
	}
	cout << "处理完毕!" << endl;
	Cell = STACK.top();
	STACK.pop();
	return Cell;
}

//NFA转DFA处理函数,返回最终的DFA结合
cell express_2_DFA(cell nfa)
{
	cell DFA;
	int DFA_Count = 0;

	//将NFA的边单独抽离出来，以vector的形式储存
	vector<edge> NFA;
	Initialize(NFA, nfa, nfa.EdgeCount);

	//去除字符集中重复的元素并排序
	Deduplication_char(Character_Set, strlen(Character_Set));
	int sigma_lenth = strlen(Character_Set);

	//从初始节点出发，经历空串创造初始集合
	string start = closure(nfa.StartState.StateName, NFA);
	sort(start.begin(), start.end());
	
	//存入子集
	vector<string> rawDFA;
	rawDFA.push_back(start);
	//存入子集是否完成的标志，false代表未存入
	vector<bool> rawDFAflag;
	rawDFAflag.push_back(false);
	
	//DFA初始化
	DFA.EdgeCount = 0;
	state first;
	first.StateName = start;
	DFA.StartState = first;

	while (checkFlag(rawDFAflag) != -1)//传进一个布尔数组，如果数组中所有元素有一个是false，就进行下一步，用于判断是否所有集合都遍历过了
	{
		int m = checkFlag(rawDFAflag);//按趋势，m=0、1、2......，是布尔数组中值为false的位数
		rawDFAflag[m] = true;//取出一个后，就将其设为true
		for (int i = 0; i < sigma_lenth; i++)//遍历字母表
		{
			string u = closure(move(rawDFA[m], Character_Set[i], NFA), NFA);//求当前DFA数组元素，经过当前字符得到的所有节点的闭包
			sort(u.begin(), u.end());
			if (u != "")
			{
				state StartState, EndState;
				StartState.StateName = rawDFA[m];
				EndState.StateName = u;

				edge line;
				line.StartState = StartState;
				line.EndState = EndState;
				line.TransSymbol = Character_Set[i];

				DFA.EdgeSet[DFA_Count++] = line;
				DFA.EdgeCount++;
				
			}
			make_EndState(DFA, rawDFA, nfa);

			if (!checkINrawDFA(rawDFA, u))//如果当前集合没有存入DFA集合数组
			{
				rawDFA.push_back(u);//存入
				rawDFAflag.push_back(false);//加存入标识
			}
		}
	}
	return DFA;
}

void Initialize(vector<edge> &NFA, cell &nfa, int num)
{
	for (int i = 0; i < num; i++)
	{
		edge temp;
		temp.StartState = nfa.EdgeSet[i].StartState;
		temp.TransSymbol = nfa.EdgeSet[i].TransSymbol;
		temp.EndState = nfa.EdgeSet[i].EndState;
		NFA.push_back(temp);
	}
}

bool check(string str, char x)//若集合中有一个元素与x相同，则true
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == x)
			return true;
	}
	return false;
}

void make_EndState(cell &DFA, vector<string> rawDFA, cell &NFA)
{
	vector<string> temp;
	string temp2 = "";
	for (unsigned int i = 0; i < rawDFA.size(); i++)
	{
		for (unsigned int j = 0; j < rawDFA[i].length(); j++)
		{
			if (rawDFA[i].at(j) == NFA.EndState.StateName[0])
			{
				temp.push_back(rawDFA[i]);
				break;
			}
		}

	}
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		temp2 = temp2 + temp[i] + " ";
	}
	DFA.EndState.StateName = temp2;
}

//接收参数为上个节点经过一个字符所到达的所有节点
string closure(string setp, vector<edge> NFA)//这一步是做之前得到的节点的闭包
{
	for (unsigned int i = 0; i < setp.length(); i++)
	{
		for (unsigned int j = 0; j < NFA.size(); j++)
		{
			if (setp[i] == NFA[j].StartState.StateName[0] && NFA[j].TransSymbol == '#')
			{
				if (!check(setp, NFA[j].EndState.StateName[0]))
				{
					setp += NFA[j].EndState.StateName[0];
				}
			}
		}
	}
	return setp;
}

string move(string t, char a, vector<edge> NFA)//参数是集合、经过的字符、NFA
{
	string temp = "";
	for (unsigned int i = 0; i < t.length(); i++)//遍历集合
	{
		for (unsigned int j = 0; j < NFA.size(); j++)//遍历所有边
		{
			if (t[i] == NFA[j].StartState.StateName[0] && NFA[j].TransSymbol == a)//对集合的每一个元素，求从当前元素出发，经过当前字符所能到达的所有节点
			{
				if (!check(temp, NFA[j].EndState.StateName[0]))//传递的集合第一次为空，x为当前节点经过字符到达的节点，如果该节点目前不在集合中，就将其加入
				{
					temp += NFA[j].EndState.StateName[0];
				}
			}
		}
	}
	return temp;
}

bool checkINrawDFA(vector<string> rawDFA, string u)//判断当前集合是否被存入DFA数组，若没有则返回false，有返回true
{
	for (unsigned int i = 0; i < rawDFA.size(); i++)
	{
		if (rawDFA[i] == u)
			return true;
	}
	return false;
}

int checkFlag(vector<bool> t)
{
	for (unsigned int i = 0; i < t.size(); i++)
	{
		if (t[i] == false)return i;
	}
	return -1;
}

void Deduplication_char(char* a, int num)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			if (a[i] == a[j])
			{
				a[j] = NULL;
			}
		}
	}
	for (int i = 0; i < num; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			if (a[j] == NULL)
			{
				a[j] = '\0';

			}
			else
			{
				if (int(a[i]) > int(a[j]))
				{
					char temp;
					temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
		}
	}
	for (int i = 1; i < num; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			if (a[i] == '\0' && a[j] != '\0')
			{
				char temp;
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;

			}
		}
	}
}

//处理 a|b
cell do_Unite(cell Left, cell Right)
{
	cell NewCell;
	NewCell.EdgeCount = 0;
	edge Edge1, Edge2, Edge3, Edge4;
	//获得新的新状态节点
	state StartState = new_StateNode();
	state EndState = new_StateNode();
	//构建边
	Edge1.StartState = StartState;
	Edge1.EndState = Left.EdgeSet[0].StartState;
	Edge1.TransSymbol = '#';  //代表空串

	Edge2.StartState = StartState;
	Edge2.EndState = Right.EdgeSet[0].StartState;
	Edge2.TransSymbol = '#';

	Edge3.StartState = Left.EdgeSet[Left.EdgeCount - 1].EndState;
	Edge3.EndState = EndState;
	Edge3.TransSymbol = '#';

	Edge4.StartState = Right.EdgeSet[Right.EdgeCount - 1].EndState;
	Edge4.EndState = EndState;
	Edge4.TransSymbol = '#';

	//构建单元
	//先将Left和Right的EdgeSet复制到NewCell
	cell_EdgeSet_Copy(NewCell, Left);
	cell_EdgeSet_Copy(NewCell, Right);

	//将新构建的四条边加入EdgeSet
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge1;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge2;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge3;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge4;

	//构建NewCell的启示状态和结束状态
	NewCell.StartState = StartState;
	NewCell.EndState = EndState;

	return NewCell;
}
//处理 ab
cell do_Join(cell Left, cell Right)
{
	//将Left的结束状态和Right的开始状态合并，将Right的边复制给Left，将Left返回
	//将Right中所有以StartState开头的边全部修改
	for (int i = 0; i < Right.EdgeCount; i++)
	{
		if (Right.EdgeSet[i].StartState.StateName.compare(Right.StartState.StateName) == 0)
		{
			Right.EdgeSet[i].StartState = Left.EndState;
			//STATE_NUM--;
		}
		else if (Right.EdgeSet[i].EndState.StateName.compare(Right.StartState.StateName) == 0)
		{
			Right.EdgeSet[i].EndState = Left.EndState;
			//STATE_NUM--;
		}
	}
	Right.StartState = Left.EndState;

	cell_EdgeSet_Copy(Left, Right);
	//将Left的结束状态更新为Right的结束状态
	Left.EndState = Right.EndState;
	return Left;
}
//处理 a*
cell do_Star(cell Cell)
{
	cell NewCell;
	NewCell.EdgeCount = 0;
	edge Edge1, Edge2, Edge3, Edge4;
	//获得新的新状态节点
	state StartState = new_StateNode();
	state EndState = new_StateNode();
	//构建边
	Edge1.StartState = StartState;
	Edge1.EndState = EndState;
	Edge1.TransSymbol = '#';  //闭包取空串

	Edge2.StartState = Cell.EndState;
	Edge2.EndState = Cell.StartState;
	Edge2.TransSymbol = '#';  //取字符，自连接

	Edge3.StartState = StartState;
	Edge3.EndState = Cell.StartState;
	Edge3.TransSymbol = '#';

	Edge4.StartState = Cell.EndState;
	Edge4.EndState = EndState;
	Edge4.TransSymbol = '#';
	//构建单元
	//先将Cell的EdgeSet复制到NewCell
	cell_EdgeSet_Copy(NewCell, Cell);
	//将新构建的四条边加入EdgeSet
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge1;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge2;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge3;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge4;
	//构建NewCell的启示状态和结束状态
	NewCell.StartState = StartState;
	NewCell.EndState = EndState;

	return NewCell;
}
//处理 a
cell do_Cell(char element)
{
	cell NewCell;
	NewCell.EdgeCount = 0;
	edge NewEdge;
	//获得新的新状态节点
	state StartState = new_StateNode();
	state EndState = new_StateNode();
	//构建边
	NewEdge.StartState = StartState;
	NewEdge.EndState = EndState;
	NewEdge.TransSymbol = element;
	//构建单元
	NewCell.EdgeSet[NewCell.EdgeCount++] = NewEdge;
	NewCell.StartState = NewCell.EdgeSet[0].StartState;
	NewCell.EndState = NewCell.EdgeSet[0].EndState;//EdgeCount此时为1
	return NewCell;
}

cell New_DFA_Cell(char element)
{
	cell NewCell;
	NewCell.EdgeCount = 0;
	edge NewEdge;
	//获得新的新状态节点
	state StartState = new_DFA_StateNode();
	state EndState = new_DFA_StateNode();
	//构建边
	NewEdge.StartState = StartState;
	NewEdge.EndState = EndState;
	NewEdge.TransSymbol = element;
	//构建单元
	NewCell.EdgeSet[NewCell.EdgeCount++] = NewEdge;
	NewCell.StartState = NewCell.EdgeSet[0].StartState;
	NewCell.EndState = NewCell.EdgeSet[0].EndState;//EdgeCount此时为1
	return NewCell;
}



void cell_EdgeSet_Copy(cell& Destination, cell Source)
{
	int D_count = Destination.EdgeCount;
	int S_count = Source.EdgeCount;
	for (int i = 0; i < S_count; i++)
	{
		Destination.EdgeSet[D_count + i] = Source.EdgeSet[i];
	}
	Destination.EdgeCount = D_count + S_count;
}

//获得新的状态节点，统一产生，便于管理，不能产生重复的状态,并添加到state_set[]数组中
state new_StateNode()
{
	state newState;
	newState.StateName = STATE_NUM + 65;//转换成大写字母
	STATE_NUM++;
	return newState;
}

state new_DFA_StateNode()
{
	state newState;
	newState.StateName = 'S' + (char)DFA_STATE_NUM;
	DFA_STATE_NUM++;
	return newState;
}

//接收输入正规表达式，RegularExpression作为回传函数
void input(string& RegularExpression)
{
	cout << "请输入后缀表达式" << endl;
	
		cin >> RegularExpression;
}

//显示NFA
void Display_NFA(cell Cell)
{
	cout << "NFA 的边数：" << Cell.EdgeCount << endl;
	cout << "NFA 的起始状态：" << Cell.StartState.StateName << endl;
	cout << "NFA 的结束状态：" << Cell.EndState.StateName << endl;
	for (int i = 0; i < Cell.EdgeCount; i++)
	{
		cout << "第" << i + 1 << "条边的起始状态：" << Cell.EdgeSet[i].StartState.StateName
			<< "  结束状态：" << Cell.EdgeSet[i].EndState.StateName
			<< "  转换符：" << Cell.EdgeSet[i].TransSymbol << endl;
	}
	cout << "结束" << endl;
}

//显示DFA
void Display_DFA(cell Cell)
{
	cout << "DFA 的边数：" << Cell.EdgeCount << endl;
	cout << "DFA 的起始状态：" << Cell.StartState.StateName << endl;
	cout << "DFA 的结束状态：" << Cell.EndState.StateName << endl;
	for (int i = 0; i < Cell.EdgeCount; i++)
	{
		cout << "第" << i + 1 << "条边的起始状态：" << Cell.EdgeSet[i].StartState.StateName
			<< "  结束状态：" << Cell.EdgeSet[i].EndState.StateName
			<< "  转换符：" << Cell.EdgeSet[i].TransSymbol << endl;
	}
	cout << "结束" << endl;
}