#include"circuit.h"  //������� �������� �� ���������� ����
#include"resistor.h" //�� ��������� ������ �����������, ��� ������������ ����� ���� ������� ���� � ��������, � ������ ����� 4-�� ������ ������
#include"voltageSource.h" //����� ����� �������� �� enum
#include"correctInput.h"
#include<stack>
#include<list>
std::istream& operator>>(std::istream& in, Circuit& circuit)
{
	std::cout << "���� ����: " << std::endl;
	std::cout << "������� ���������� ������ �����: ";
	int nVertex;
	in >> nVertex;
	/*if (nVertex <= 0) //�������� ���������� �������� �� ������������ ���-�� ������
		return in;*/
	circuit.values.resize(nVertex);
	for (int i = 0; i < nVertex; ++i)
		circuit.values[i].resize(nVertex, std::vector<double>(1, -1));
	circuit.elements.resize(nVertex);
	for (int i = 0; i < nVertex; ++i)
		circuit.elements[i].resize(nVertex, std::vector<char>(1, '0'));


	/*int number = 0; //����, ����������� �� ������ ���������� -1
	for(int i = 0; i < circuit.graph.size(); ++i)
		for (int j = 0; j < circuit.graph[i].size(); ++j)
		{
			if (circuit.graph[i][j][0].getValue() == -1)
				++number;
		}
	if (number == circuit.graph.size() * circuit.graph.size())
		std::cout << "�� ��������" << std::endl;*/


	std::cout << "������ ������� -> ������ ������� -> (U/R) -> value" << std::endl;
	int fVertex = 0, sVertex = 0;
	double value = 0;
	char unit = '0';

	while (true)
	{
		correctInput(fVertex);
		correctInput(sVertex);
		if (fVertex < 0 || sVertex < 0)
			break;
		correctInput(unit);
		correctInput(value);
		if (fVertex >= nVertex || sVertex >= nVertex)
		{
			std::cout << "����� ������� �� ����������. ���������� ��� ���." << std::endl;
		}
		else
		{
			if (unit == 'U' || unit == 'u')
			{
				if (circuit.elements[fVertex][sVertex][0] == '0') //���� �� ����� ������ �� ����������, �� ������ ������ ��������
				{
					circuit.elements[fVertex][sVertex][0] = 'U';
					circuit.values[fVertex][sVertex][0] = value;
				}
				else
				{
					circuit.elements[fVertex][sVertex].push_back('U');	//���� �� ��� ����������, �� ��������� ����� �������
					circuit.values[fVertex][sVertex].push_back(value);
				}	
			}
			else if (unit == 'R' || unit == 'r')
			{
				if (circuit.elements[fVertex][sVertex][0] == '0') //���� �� ����� ������ �� ����������, �� ������ ������ ��������
				{
					circuit.elements[fVertex][sVertex][0] = 'R';
					circuit.values[fVertex][sVertex][0] = value;
				}
				else
				{
					circuit.elements[fVertex][sVertex].push_back('R');	//���� �� ��� ����������, �� ��������� ����� �������
					circuit.values[fVertex][sVertex].push_back(value);
				}
			}
			else
			{
				std::cout << "������ �������� �������." << std::endl;
			}
		}
	}
	return in;
}



void printMatrix(std::vector<std::vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
			std::cout << matrix[i][j] << " ";
		std::cout << std::endl;
	}
}

void Circuit::createTree()
{
	tree.resize(values.size());
	for (int i = 0; i < tree.size(); ++i)
		tree[i].resize(values.size(), 0);
	chords.resize(values.size());
	for (int i = 0; i < chords.size(); ++i)
		chords[i].resize(values.size(), 0);
	int v = 0;
	// 0-����� ����, 1-������� ����, 2 - ������ ����
	std::vector<int> color(values.size(), 0);
	color[v] = 1;
	std::stack<int> stack;
	stack.push(v);
	while (!stack.empty())
	{
		v = stack.top();
		stack.pop();
		color[v] = 2;
		for (int i = 0; i < values.size(); ++i)
		{
			if (color[i] == 1)
			{
				if (values[v][i][0] != -1)
					chords[v][i] = 1;
				else if (values[i][v][0] != -1)
					chords[i][v] = 1;
			}
			else if (color[i] == 0)
			{
				if (values[v][i][0] != -1)
				{
					stack.push(i);
					tree[v][i] = 1;
					color[i] = 1;
				}
				else if (values[i][v][0] != -1)
				{
					stack.push(i);
					tree[i][v] = 1;
					color[i] = 1;
				}
				
			}
		}
	}
	std::cout << "Tree: " << std::endl;
	printMatrix(tree);
	std::cout << std::endl;
	std::cout << "C: " << std::endl;
	printMatrix(chords);
}


//void Circuit::createTree()
//{
//	tree.resize(values.size());
//	for (int i = 0; i < tree.size(); ++i)
//		tree[i].resize(values.size(), 0);
//	chords.resize(values.size());
//	for (int i = 0; i < chords.size(); ++i)
//		chords[i].resize(values.size(), 0);
//	int v = 0;
//	// 0-����� ����, 1-������� ����, 2 - ������ ����
//	std::vector<int> color(values.size(), 0);
//	color[v] = 1;
//	std::stack<int> stack;
//	stack.push(v);
//	while (!stack.empty())
//	{
//		v = stack.top();
//		stack.pop();
//		color[v] = 2;
//		for (int i = 0; i < values.size(); ++i)
//		{
//			if (color[i] == 1)
//			{
//				if (values[v][i][0] != -1)
//					chords[v][i] = 1;
//				if (values[i][v][0] != -1)
//					chords[i][v] = 1;
//			}
//			else if (color[i] == 0)
//			{
//				if (values[v][i][0] != -1)
//				{
//					stack.push(i);
//					tree[v][i] = 1;
//					color[i] = 1;
//				}
//			}
//		}
//	}
//	std::cout << "Tree: " << std::endl;
//	printMatrix(tree);
//	std::cout << std::endl;
//	std::cout << "C: " << std::endl;
//	printMatrix(chords);
//}



int Circuit::vertexDegree(int vertex, std::vector<std::vector<int>>& graph)
{
	int counter = 0;
	for (int i = 0; i < graph.size(); ++i)
		if (graph[vertex][i] != 0 || graph[i][vertex] != 0)
			++counter;
	return counter;
}

void mergeLists(std::list<int>& fList, std::list<int>& sList)
{
	for (auto i : sList)
		fList.push_back(i);
}

void Circuit::getIndependentLoop(std::list<int>& path, int vStart, int vEnd)
{
	int v = vStart;
	path.push_back(v);
	std::list<int> tmp;
	// 0-����� ����, 1-������� ����, 2 - ������ ����
	std::vector<int> color(values.size(), 0);
	color[v] = 1;
	bool isEnd = false;
	while (true)
	{
		if (vertexDegree(vEnd, tree) <= 2)
		{
			tmp.push_front(vEnd);
			color[vEnd] = 2;
			if (vEnd == vStart)
			{
				path = tmp;
				isEnd = true;
			}
			for (int i = 0; i < tree.size(); ++i)
			{
				if (color[i] == 0 && (tree[i][vEnd] != 0 || tree[vEnd][i] != 0))
				{
					vEnd = i;
					break;
				}
			}
		}
		else break;
	}
	while (!isEnd)
	{
		if (color[v] != 1 && !path.empty())
		{
			v = path.back();
			path.pop_back();

		}
		else
		{
			color[v] = 2;
			if (v != vEnd)
			{
				for (int i = 0; i < tree.size(); i++)
				{
					if (color[i] == 0 && (tree[v][i] != 0 || tree[i][v] != 0))
					{
						if (vEnd == i)
						{
							color[vEnd] = 2;
							path.push_back(i);
							isEnd = true;
							break;
						}
						//path.push_back(i);
						color[i] = 1;
					}
				}
			}
			else break;
		}
	}
	for (auto i = path.begin(); i != path.end(); ++i)
	{
		if (color[*i] == 1)
			path.erase(i);
	}
	//S.merge(P);
	mergeLists(path, tmp);
}


void Circuit::printGraph()
{
	for (int i = 0; i < elements.size(); ++i)
	{
		for (int j = 0; j < elements[i].size(); ++j)
		{
			std::cout << elements[i][j][0] << " ";
		}
		std::cout << std::endl;
	}
}

void Circuit::getLoopCoef(std::list<int>& path, std::vector<int>& coef) //��� - ��� ��������
{
	
	coef.resize(edgesIndex.size(), 0);
	//int direction = 1;
	auto i = path.begin();
	auto j = path.begin();
	++j;
	//int index = 0;
	auto it = edgesIndex.begin();
	while (j != path.end())
	{
		it = edgesIndex.find(std::pair<int, int>(*i, *j));
		if (it == edgesIndex.end())
		{
			it = edgesIndex.find(std::pair<int, int>(*j, *i));
			coef[it->second] = -1;  //����� ���������� ������ ����������� ������
		}
		else
		{
			coef[it->second] = 1;	//����� ���������� �� ����������� ������
		}
		++i; ++j;
	}
	i = --path.end();  //��������, ����� ������ ��������� ���������, �� ������ ������ ����� ��������� -> ������
	j = path.begin();
	it = edgesIndex.find(std::pair<int, int>(*i, *j));
	if (it == edgesIndex.end())
	{
		it = edgesIndex.find(std::pair<int, int>(*j, *i));
		coef[it->second] = -1;  //����� ���������� ������ ����������� ������
	}
	else
	{
		coef[it->second] = 1;  //����� ���������� �� ����������� ������
	}
	for (auto& i : path)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void Circuit::fillEdgesIndex()  // �������� ����� �����
{
	int counter = 0;
	for (int i = 0; i < values.size(); ++i)
	{
		for (int j = 0; j < values.size(); ++j)
		{
			if (values[i][j][0] != -1)
			{
				edgesIndex.emplace(std::pair<int, int>(i, j), counter);
				++counter;
			}
		}
	}
}

void Circuit::fillContoursCoef()
{
	int counter = 0;
	//contoursCoef.push_back(std::vector<int>(edgesIndex.size(), 0));
	createTree();
	fillEdgesIndex();
	std::list<int> path;
	for (int i = 0; i < chords.size(); ++i)
	{
		for (int j = 0; j < chords[i].size(); ++j)
		{
			if (chords[i][j] == 1)
			{
				getIndependentLoop(path, i, j);
				contoursCoef.push_back(std::vector<int>(edgesIndex.size(), 0));
				getLoopCoef(path, contoursCoef[counter]);
				path.clear();
				++counter;
			}
		}
	}
		
}

std::vector<std::vector<int>>& Circuit::getContoursCoef()
{
	return contoursCoef;
}


std::vector<std::vector<double>>& Circuit::getResistance()
{
	return resistance;
}

std::vector<std::vector<double>>& Circuit::getVoltage()
{
	return voltage;
}

std::vector<std::vector<std::vector<double>>>& Circuit::getValues()
{
	return values;
}

void Circuit::fillResistAndVolt() //�� �������� 
{
	resistance.resize(edgesIndex.size());
	for (int i = 0; i < resistance.size(); ++i)
		resistance[i].resize(resistance.size(), 0);
	voltage.resize(edgesIndex.size(), std::vector<double>(1, 0));
	int resistCounter = 0;
	int voltageCounter = 0;
	double R = 0;
	double U = 0;
	for (int i = 0; i < values.size(); ++i)
	{
		for (int j = 0; j < values[i].size(); ++j)
		{
			if (values[i][j][0] != - 1)
			{
				for (int k = 0; k < values[i][j].size(); ++k)
				{
					if (elements[i][j][k] == 'R' || elements[i][j][k] == 'r')
						R += values[i][j][k];
					else
						U += values[i][j][k];
				}
				resistance[resistCounter][resistCounter] = R;
				voltage[voltageCounter][0] = U;
				R = 0;
				U = 0;
				++resistCounter;
				++voltageCounter;
			}
		}
	}
}