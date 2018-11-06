/* Дана прямоугольная таблица, состоящая из m строк и n столбцов. На
пересечении i-й строки и j-го столбца записано целое число aij. Требуется найти
такие четыре различные ячейки таблицы, чтобы их центры были вершинами
прямоугольника со сторонами, параллельными сторонам таблицы, а сумма чисел,
записанных в этих ячейках, была максимальна. */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int** InputMatrixFromFile(int &rows, int &columns)
{
    ifstream fin;
    fin.open("input_task13.txt");
    fin >> rows;
    fin >> columns;

    int ** matrix = new int*[columns];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[rows];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            fin >> matrix[i][j];
        }
    }
    fin.close();
    return matrix;
}

void PrintResult(int x1, int x2, int y1, int y2, int ** matrix, int maxSum)
{
    cout << "Max sum is: " << maxSum << endl;

    cout << "Max sum rectangle indexes: " << endl;
    cout << "(" << x1 << ";" << y1 << ")" << "  " << "(" << x2 << ";" << y1 << ")" << endl;
	cout << "(" << x1 << ";" << y2 << ")" << "  " << "(" << x2 << ";" << y2 << ")" << endl;

	cout << "Max sum rectangle elements: " << endl;
	cout << matrix[x1][y1] << "  " << matrix[x2][y1] << endl;
	cout << matrix[x1][y2] << "  " << matrix[x2][y2] << endl;
}

int main()
{
    int rows, columns, temporarySum = 0, maxSum = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int** matrix = InputMatrixFromFile(rows, columns);

    for (int leftX = 0; leftX < rows; leftX++)
    {
        for (int upperY = 0; upperY < columns; upperY++)
        {
            for (int rightX = leftX + 1; rightX < rows; rightX++)
            {
                for (int lowerY = upperY + 1; lowerY < columns; lowerY++)
                {
                    temporarySum = matrix[leftX][upperY];
                    temporarySum += matrix[leftX][lowerY];
                    temporarySum += matrix[rightX][upperY];
                    temporarySum += matrix[rightX][lowerY];
                    if (temporarySum > maxSum)
                    {
                        maxSum = temporarySum;
                        x1 = leftX;
                        x2 = rightX;
                        y1 = upperY;
                        y2 = lowerY;
                    }
                }
            }
        }
    }
    PrintResult(x1, x2, y1, y2, matrix, maxSum);
}
