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
	std::vector<std::vector<int>> chords; //хорды графа
	std::map<std::pair<int, int>, int> edgesIndex;  // нумерует ребра графа
	std::vector<std::vector<int>> contoursCoef; //матрица B
	std::vector<std::vector<double>> resistance; //матрица сопротивлений 
	std::vector<std::vector<double>> voltage;	//матрица напряжений
	
private:
	void fillEdgesIndex();
	int vertexDegree(int vertex, std::vector<std::vector<int>>& graph);
	void createTree();
	void getIndependentLoop(std::list<int>& path, int vStart, int vEnd);
	void printGraph();
	void getLoopCoef(std::list<int>& path, std::vector<int>& countoursCoef);
};

std::istream& operator>>(std::istream& in, Circuit& circuit);