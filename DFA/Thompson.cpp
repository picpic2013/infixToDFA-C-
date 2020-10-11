#include "Thompson.h"
;
int STATE_NUM = 0;
int DFA_STATE_NUM = 0;
int char_count = 0;
char Character_Set[20] = { NULL };

int sum11 = 0;//�¼���Ԫ�ظ���

//���ʽתNFA������,�������յ�NFA���
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
	cout << "�������!" << endl;
	Cell = STACK.top();
	STACK.pop();
	return Cell;
}

//NFAתDFA������,�������յ�DFA���
cell express_2_DFA(cell nfa)
{
	cell DFA;
	int DFA_Count = 0;

	//��NFA�ıߵ��������������vector����ʽ����
	vector<edge> NFA;
	Initialize(NFA, nfa, nfa.EdgeCount);

	//ȥ���ַ������ظ���Ԫ�ز�����
	Deduplication_char(Character_Set, strlen(Character_Set));
	int sigma_lenth = strlen(Character_Set);

	//�ӳ�ʼ�ڵ�����������մ������ʼ����
	string start = closure(nfa.StartState.StateName, NFA);
	sort(start.begin(), start.end());
	
	//�����Ӽ�
	vector<string> rawDFA;
	rawDFA.push_back(start);
	//�����Ӽ��Ƿ���ɵı�־��false����δ����
	vector<bool> rawDFAflag;
	rawDFAflag.push_back(false);
	
	//DFA��ʼ��
	DFA.EdgeCount = 0;
	state first;
	first.StateName = start;
	DFA.StartState = first;

	while (checkFlag(rawDFAflag) != -1)//����һ���������飬�������������Ԫ����һ����false���ͽ�����һ���������ж��Ƿ����м��϶���������
	{
		int m = checkFlag(rawDFAflag);//�����ƣ�m=0��1��2......���ǲ���������ֵΪfalse��λ��
		rawDFAflag[m] = true;//ȡ��һ���󣬾ͽ�����Ϊtrue
		for (int i = 0; i < sigma_lenth; i++)//������ĸ��
		{
			string u = closure(move(rawDFA[m], Character_Set[i], NFA), NFA);//��ǰDFA����Ԫ�أ�������ǰ�ַ��õ������нڵ�ıհ�
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

			if (!checkINrawDFA(rawDFA, u))//�����ǰ����û�д���DFA��������
			{
				rawDFA.push_back(u);//����
				rawDFAflag.push_back(false);//�Ӵ����ʶ
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

bool check(string str, char x)//����������һ��Ԫ����x��ͬ����true
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

//���ղ���Ϊ�ϸ��ڵ㾭��һ���ַ�����������нڵ�
string closure(string setp, vector<edge> NFA)//��һ������֮ǰ�õ��Ľڵ�ıհ�
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

string move(string t, char a, vector<edge> NFA)//�����Ǽ��ϡ��������ַ���NFA
{
	string temp = "";
	for (unsigned int i = 0; i < t.length(); i++)//��������
	{
		for (unsigned int j = 0; j < NFA.size(); j++)//�������б�
		{
			if (t[i] == NFA[j].StartState.StateName[0] && NFA[j].TransSymbol == a)//�Լ��ϵ�ÿһ��Ԫ�أ���ӵ�ǰԪ�س�����������ǰ�ַ����ܵ�������нڵ�
			{
				if (!check(temp, NFA[j].EndState.StateName[0]))//���ݵļ��ϵ�һ��Ϊ�գ�xΪ��ǰ�ڵ㾭���ַ�����Ľڵ㣬����ýڵ�Ŀǰ���ڼ����У��ͽ������
				{
					temp += NFA[j].EndState.StateName[0];
				}
			}
		}
	}
	return temp;
}

bool checkINrawDFA(vector<string> rawDFA, string u)//�жϵ�ǰ�����Ƿ񱻴���DFA���飬��û���򷵻�false���з���true
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

//���� a|b
cell do_Unite(cell Left, cell Right)
{
	cell NewCell;
	NewCell.EdgeCount = 0;
	edge Edge1, Edge2, Edge3, Edge4;
	//����µ���״̬�ڵ�
	state StartState = new_StateNode();
	state EndState = new_StateNode();
	//������
	Edge1.StartState = StartState;
	Edge1.EndState = Left.EdgeSet[0].StartState;
	Edge1.TransSymbol = '#';  //����մ�

	Edge2.StartState = StartState;
	Edge2.EndState = Right.EdgeSet[0].StartState;
	Edge2.TransSymbol = '#';

	Edge3.StartState = Left.EdgeSet[Left.EdgeCount - 1].EndState;
	Edge3.EndState = EndState;
	Edge3.TransSymbol = '#';

	Edge4.StartState = Right.EdgeSet[Right.EdgeCount - 1].EndState;
	Edge4.EndState = EndState;
	Edge4.TransSymbol = '#';

	//������Ԫ
	//�Ƚ�Left��Right��EdgeSet���Ƶ�NewCell
	cell_EdgeSet_Copy(NewCell, Left);
	cell_EdgeSet_Copy(NewCell, Right);

	//���¹����������߼���EdgeSet
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge1;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge2;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge3;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge4;

	//����NewCell����ʾ״̬�ͽ���״̬
	NewCell.StartState = StartState;
	NewCell.EndState = EndState;

	return NewCell;
}
//���� ab
cell do_Join(cell Left, cell Right)
{
	//��Left�Ľ���״̬��Right�Ŀ�ʼ״̬�ϲ�����Right�ı߸��Ƹ�Left����Left����
	//��Right��������StartState��ͷ�ı�ȫ���޸�
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
	//��Left�Ľ���״̬����ΪRight�Ľ���״̬
	Left.EndState = Right.EndState;
	return Left;
}
//���� a*
cell do_Star(cell Cell)
{
	cell NewCell;
	NewCell.EdgeCount = 0;
	edge Edge1, Edge2, Edge3, Edge4;
	//����µ���״̬�ڵ�
	state StartState = new_StateNode();
	state EndState = new_StateNode();
	//������
	Edge1.StartState = StartState;
	Edge1.EndState = EndState;
	Edge1.TransSymbol = '#';  //�հ�ȡ�մ�

	Edge2.StartState = Cell.EndState;
	Edge2.EndState = Cell.StartState;
	Edge2.TransSymbol = '#';  //ȡ�ַ���������

	Edge3.StartState = StartState;
	Edge3.EndState = Cell.StartState;
	Edge3.TransSymbol = '#';

	Edge4.StartState = Cell.EndState;
	Edge4.EndState = EndState;
	Edge4.TransSymbol = '#';
	//������Ԫ
	//�Ƚ�Cell��EdgeSet���Ƶ�NewCell
	cell_EdgeSet_Copy(NewCell, Cell);
	//���¹����������߼���EdgeSet
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge1;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge2;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge3;
	NewCell.EdgeSet[NewCell.EdgeCount++] = Edge4;
	//����NewCell����ʾ״̬�ͽ���״̬
	NewCell.StartState = StartState;
	NewCell.EndState = EndState;

	return NewCell;
}
//���� a
cell do_Cell(char element)
{
	cell NewCell;
	NewCell.EdgeCount = 0;
	edge NewEdge;
	//����µ���״̬�ڵ�
	state StartState = new_StateNode();
	state EndState = new_StateNode();
	//������
	NewEdge.StartState = StartState;
	NewEdge.EndState = EndState;
	NewEdge.TransSymbol = element;
	//������Ԫ
	NewCell.EdgeSet[NewCell.EdgeCount++] = NewEdge;
	NewCell.StartState = NewCell.EdgeSet[0].StartState;
	NewCell.EndState = NewCell.EdgeSet[0].EndState;//EdgeCount��ʱΪ1
	return NewCell;
}

cell New_DFA_Cell(char element)
{
	cell NewCell;
	NewCell.EdgeCount = 0;
	edge NewEdge;
	//����µ���״̬�ڵ�
	state StartState = new_DFA_StateNode();
	state EndState = new_DFA_StateNode();
	//������
	NewEdge.StartState = StartState;
	NewEdge.EndState = EndState;
	NewEdge.TransSymbol = element;
	//������Ԫ
	NewCell.EdgeSet[NewCell.EdgeCount++] = NewEdge;
	NewCell.StartState = NewCell.EdgeSet[0].StartState;
	NewCell.EndState = NewCell.EdgeSet[0].EndState;//EdgeCount��ʱΪ1
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

//����µ�״̬�ڵ㣬ͳһ���������ڹ������ܲ����ظ���״̬,����ӵ�state_set[]������
state new_StateNode()
{
	state newState;
	newState.StateName = STATE_NUM + 65;//ת���ɴ�д��ĸ
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

//��������������ʽ��RegularExpression��Ϊ�ش�����
void input(string& RegularExpression)
{
	cout << "�������׺���ʽ" << endl;
	
		cin >> RegularExpression;
}

//��ʾNFA
void Display_NFA(cell Cell)
{
	cout << "NFA �ı�����" << Cell.EdgeCount << endl;
	cout << "NFA ����ʼ״̬��" << Cell.StartState.StateName << endl;
	cout << "NFA �Ľ���״̬��" << Cell.EndState.StateName << endl;
	for (int i = 0; i < Cell.EdgeCount; i++)
	{
		cout << "��" << i + 1 << "���ߵ���ʼ״̬��" << Cell.EdgeSet[i].StartState.StateName
			<< "  ����״̬��" << Cell.EdgeSet[i].EndState.StateName
			<< "  ת������" << Cell.EdgeSet[i].TransSymbol << endl;
	}
	cout << "����" << endl;
}

//��ʾDFA
void Display_DFA(cell Cell)
{
	cout << "DFA �ı�����" << Cell.EdgeCount << endl;
	cout << "DFA ����ʼ״̬��" << Cell.StartState.StateName << endl;
	cout << "DFA �Ľ���״̬��" << Cell.EndState.StateName << endl;
	for (int i = 0; i < Cell.EdgeCount; i++)
	{
		cout << "��" << i + 1 << "���ߵ���ʼ״̬��" << Cell.EdgeSet[i].StartState.StateName
			<< "  ����״̬��" << Cell.EdgeSet[i].EndState.StateName
			<< "  ת������" << Cell.EdgeSet[i].TransSymbol << endl;
	}
	cout << "����" << endl;
}