#include <iostream>
#include <vector>
#include <iterator>
#include <iomanip>

std::vector<std::vector<double>> MatrixMul(std::vector<std::vector<int>>& matrix1, std::vector<std::vector<double>>& matrix2) {

    int rows1 = matrix1.size();
    int columns1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int columns2 = matrix2[0].size();
    std::vector<std::vector<double>> matrix3(rows1, std::vector<double>(columns2));
    if (columns1 != rows2) { std::cout << "Error, matrix data cannot be multiplied!"; return matrix3; }
    for (int i = 0; i < rows1; i++)
        for (int j = 0; j < columns2; j++)
        {
            matrix3[i][j] = 0;
            for (int h = 0; h < columns1; h++)
            {
                matrix3[i][j] += matrix1[i][h] * matrix2[h][j];
            }
        }
    return matrix3;
}

std::vector<std::vector<double>> MatrixMul(std::vector<std::vector<double>>& matrix1, std::vector<std::vector<int>>& matrix2) {

    int rows1 = matrix1.size();
    int columns1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int columns2 = matrix2[0].size();
    std::vector<std::vector<double>> matrix3(rows1, std::vector<double>(columns2));
    if (columns1 != rows2) { std::cout << "Error, matrix data cannot be multiplied!"; return matrix3; }
    for (int i = 0; i < rows1; i++)
        for (int j = 0; j < columns2; j++)
        {
            matrix3[i][j] = 0;
            for (int h = 0; h < columns1; h++)
            {
                matrix3[i][j] += matrix1[i][h] * matrix2[h][j];
            }
        }
    return matrix3;
}

std::vector<std::vector<double>> MatrixMul(std::vector<std::vector<double>>& matrix1, std::vector<std::vector<double>>& matrix2) {

    int rows1 = matrix1.size();
    int columns1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int columns2 = matrix2[0].size();
    std::vector<std::vector<double>> matrix3(rows1, std::vector<double>(columns2));
    if (columns1 != rows2) { std::cout << "Error, matrix data cannot be multiplied!"; return matrix3; }
    for (int i = 0; i < rows1; i++)
        for (int j = 0; j < columns2; j++)
        {
            matrix3[i][j] = 0;
            for (int h = 0; h < columns1; h++)
            {
                matrix3[i][j] += matrix1[i][h] * matrix2[h][j];
            }
        }
    return matrix3;
}

template<typename T>
std::vector<std::vector<T>> MatrixInv(std::vector<std::vector<T>>& matrix1) {
    std::vector<std::vector<T>> matrix2(matrix1.size(), std::vector<T>(matrix1.size()));

    float temp;
    int N = matrix1.size();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            matrix2[i][j] = 0.0;

            if (i == j)
                matrix2[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++)
    {
        temp = matrix1[k][k];

        for (int j = 0; j < N; j++)
        {
            matrix1[k][j] /= temp;
            matrix2[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++)
        {
            temp = matrix1[i][k];

            for (int j = 0; j < N; j++)
            {
                matrix1[i][j] -= matrix1[k][j] * temp;
                matrix2[i][j] -= matrix2[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = matrix1[i][k];

            for (int j = 0; j < N; j++)
            {
                matrix1[i][j] -= matrix1[k][j] * temp;
                matrix2[i][j] -= matrix2[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix1[i][j] = matrix2[i][j];
    return matrix2;
}

template<typename T>
std::vector<std::vector<T>> MatrixTransp(std::vector<std::vector<T>>& matrix1) {
    std::vector<std::vector<T>> matrix2(matrix1[0].size(), std::vector<T>(matrix1.size()));
    for (int i = 0; i < matrix1.size(); i++)
        for (int j = 0; j < matrix1[0].size(); j++)
            matrix2[j][i] = matrix1[i][j];
    return matrix2;
}

//Матрица 1 = матрица В, матрица 2 = матрица сопротивлений, матрица 3 = матрица напряженний
std::vector<std::vector<double>> MatrixRez(std::vector<std::vector<int>>& matrix1, std::vector<std::vector<double>>& matrix2, std::vector<std::vector<double>>& matrix3) {
    std::vector<std::vector<double>> matrix4(matrix1.size(), std::vector<double>(matrix1.size())); // матрица контурных сопротивлений
    std::vector<std::vector<double>> matrix5(matrix1.size(), std::vector<double>(matrix3[0].size())); // матрица контурных напряжений
    std::vector<std::vector<double>> matrix6(matrix5.size(), std::vector<double>(matrix5[0].size())); // матрица контурных токов
    std::vector<std::vector<double>> matrix7(matrix1.size(), std::vector<double>(matrix1[0].size())); // матрица В*Z
    std::vector<std::vector<int>> matrix8(matrix1[0].size(), std::vector<int>(matrix1.size())); // транспонированная матрица В
    std::vector<std::vector<double>> matrix9(matrix4.size(), std::vector<double>(matrix4.size())); // обратная матрица контурных сопротивлений
    std::vector<std::vector<double>> matrix10(matrix8.size(), std::vector<double>(matrix8[0].size())); // матрица токов

    matrix8 = MatrixTransp(matrix1);
    matrix7 = MatrixMul(matrix1, matrix2);
    matrix4 = MatrixMul(matrix7, matrix8);
    matrix5 = MatrixMul(matrix1, matrix3);
    matrix9 = MatrixInv(matrix4);
    matrix6 = MatrixMul(matrix9, matrix5);
    matrix10 = MatrixMul(matrix8, matrix6);

    return matrix10;
}
