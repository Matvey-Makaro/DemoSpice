#pragma once
#include<vector>

std::vector<std::vector<double>> MatrixMul(std::vector<std::vector<int>>& matrix1, std::vector<std::vector<double>>& matrix2);
std::vector<std::vector<double>> MatrixMul(std::vector<std::vector<double>>& matrix1, std::vector<std::vector<int>>& matrix2);
std::vector<std::vector<double>> MatrixMul(std::vector<std::vector<double>>& matrix1, std::vector<std::vector<double>>& matrix2);
template<typename T>
std::vector<std::vector<T>> MatrixInv(std::vector<std::vector<T>>& matrix1);
template<typename T>
std::vector<std::vector<T>> MatrixTransp(std::vector<std::vector<T>>& matrix1);
std::vector<std::vector<double>> MatrixRez(std::vector<std::vector<int>>& matrix1, std::vector<std::vector<double>>& matrix2, std::vector<std::vector<double>>& matrix3);


//std::vector<std::vector<float>> MatrixMul(std::vector<std::vector<float>>&, std::vector<std::vector<float>>&);
//std::vector<std::vector<float>> MatrixInv(std::vector<std::vector<float>>&);
//std::vector<std::vector<float>> MatrixTransp(std::vector<std::vector<float>>&);
//std::vector<std::vector<float>> MatrixRez(std::vector<std::vector<float>>& matrix1, std::vector<std::vector<float>>& matrix2, std::vector<std::vector<float>>& matrix3);
