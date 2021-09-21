#include<iostream>
#include<vector>
#include<map>
#include"circuit.h"
#include"matrixOperations.h"
using namespace std;

template<typename T>
void printMatrix(vector<vector<T>>& matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void printResult(vector<vector<double>>& matrix, vector<vector<vector<double>>>& values)
{
	int counter = 0;
	for (int i = 0; i < values.size(); ++i)
	{
		for (int j = 0; j < values[i].size(); ++j)
		{
			if (values[i][j][0] != -1)
			{
				cout << i << "->" << j << ": I = " << matrix[counter++][0] << "A" << endl;
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Ru");
	Circuit circuit;
	cin >> circuit;
	circuit.fillContoursCoef();
	vector<vector<int>>& contoursCoef = circuit.getContoursCoef();
	for (int i = 0; i < contoursCoef.size(); ++i)
	{
		for (int j = 0; j < contoursCoef[i].size(); ++j)
		{
			cout << contoursCoef[i][j] << " ";
		}
		cout << endl;
	}
	circuit.fillResistAndVolt();
	cout << "Resistance: " << endl;
	printMatrix(circuit.getResistance());
	cout << endl << endl;
	cout << "Voltage: " << endl;
	printMatrix(circuit.getVoltage());

	vector<vector<double>> currents = MatrixRez(circuit.getContoursCoef(), circuit.getResistance(), circuit.getVoltage());
	printResult(currents, circuit.getValues());
	system("pause");
	return 0;
}