#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<map>
class Circuit
{
public:
	Circuit() {}
	friend std::istream& operator>>(std::istream& in, Circuit& circuit);
	void fillContoursCoef();
	std::vector<std::vector<int>>& getContoursCoef();
	std::vector<std::vector<double>>& getResistance();
	std::vector<std::vector<double>>& getVoltage();
	std::vector<std::vector<std::vector<double>>>& getValues();
	void fillResistAndVolt();

private:
	std::vector<std::vector<std::vector<double>>> values;
	std::vector<std::vector<std::vector<char>>> elements;
	std::vector<std::vector<int>> tree;
	std::vector<std::vector<int>> chords; //����� �����
	std::map<std::pair<int, int>, int> edgesIndex;  // �������� ����� �����
	std::vector<std::vector<int>> contoursCoef; //������� B
	std::vector<std::vector<double>> resistance; //������� ������������� 
	std::vector<std::vector<double>> voltage;	//������� ����������
	
private:
	void fillEdgesIndex();
	int vertexDegree(int vertex, std::vector<std::vector<int>>& graph);
	void createTree();
	void getIndependentLoop(std::list<int>& path, int vStart, int vEnd);
	void printGraph();
	void getLoopCoef(std::list<int>& path, std::vector<int>& countoursCoef);
};

std::istream& operator>>(std::istream& in, Circuit& circuit);