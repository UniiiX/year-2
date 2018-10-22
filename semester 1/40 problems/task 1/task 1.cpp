#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include <cassert>

using namespace std;

struct Rectangle
{
	double minX;
	double minY;
	double maxX;
	double maxY;
};

void ReadRectanglesFromFile(int &rectanglesCount, vector<Rectangle> &rectangles, char* fileName)
{
	ifstream fin(fileName);
	fin >> rectanglesCount;
	for (int i = 0; i < rectanglesCount; i++)
	{
	    int x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;
		rectangles.push_back(Rectangle{min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2)});
	}
}

void FillXsAndYs(int rectanglesCount, vector<Rectangle> rectangles, vector<int> &xs, vector<int> &ys)
{
    //adding max size cell
    xs.push_back(-10001);
    xs.push_back(10001);
    ys.push_back(-10001);
    ys.push_back(10001);
    for (int i = 0; i < rectanglesCount; i++)
    {
        xs.push_back(rectangles[i].minX);
        xs.push_back(rectangles[i].maxX);
        ys.push_back(rectangles[i].minY);
        ys.push_back(rectangles[i].maxY);
    }
    //sorting vectors
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());

    //erasing not unique elements
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
}

void ApplyCoordinatesCompression(int rectanglesCount, vector<Rectangle> &rectangles, vector<int> &xs, vector<int> &ys)
{
    for (int i = 0; i < rectanglesCount; i++)
    {
        rectangles[i].minX = int(lower_bound(xs.begin(), xs.end(), rectangles[i].minX) - xs.begin());
        rectangles[i].minY = int(lower_bound(ys.begin(), ys.end(), rectangles[i].minY) - ys.begin());
        rectangles[i].maxX = int(lower_bound(xs.begin(), xs.end(), rectangles[i].maxX) - xs.begin());
        rectangles[i].maxY = int(lower_bound(ys.begin(), ys.end(), rectangles[i].maxY) - ys.begin());
    }

}

void FillBelongs(int rectanglesCount, vector<Rectangle> &rectangles, vector<vector<vector<bool> > > &belongs)
{
    for (int rectangleIndex = 0; rectangleIndex < rectanglesCount; rectangleIndex++)
    {
        for (int x = rectangles[rectangleIndex].minX; x < rectangles[rectangleIndex].maxX; x++)
        {
            for (int y = rectangles[rectangleIndex].minY; y < rectangles[rectangleIndex].maxY; y++)
            {
                belongs[x][y][rectangleIndex] = true;
            }
        }
    }
}

void Paint(int x, int y, vector<int> &xs, vector<int> &ys, vector<vector<bool> > &painted, vector<vector<vector<bool> > > &belongs)
{
    assert(!painted[x][y]);
    painted[x][y] = true;
    //cout << "painted cell(" << x << ", " << y << ")" << endl;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx * dx + dy * dy == 1) // for every neighbour cell do:
            {
                int neighbourX = x + dx;
                int neighbourY = y + dy;
                if (0 <= neighbourX && neighbourX < xs.size() - 1 && 0 <= neighbourY && neighbourY < ys.size() - 1 &&
                    !painted[neighbourX][neighbourY] && belongs[x][y] == belongs[neighbourX][neighbourY])
                {
                    Paint(neighbourX, neighbourY, xs, ys, painted, belongs);
                }
            }
        }
    }
}

int CountCells(vector<int> &xs, vector<int> &ys, vector<vector<vector<bool> > > &belongs)
{
    vector<vector<bool> > painted(xs.size() - 1, vector<bool>(ys.size() - 1, false));
    int result = 0;
    for (int x = 0; x < xs.size() - 1; x++)
    {
        for (int y = 0; y < ys.size() - 1; y++)
        {
            if (!painted[x][y])
            {
                Paint(x, y, xs, ys, painted, belongs);
                result++;
            }
        }
    }
    return result;
}

int main()
{
    int cellsCount;
    int rectanglesCount;
	vector<Rectangle> rectangles; //vector to store rectangles
	//vectors to store x and y coordinates of rectangles respectively
    vector<int> xs;
    vector<int> ys;

    ReadRectanglesFromFile(rectanglesCount, rectangles, "input.txt");
    FillXsAndYs(rectanglesCount, rectangles, xs, ys);
    ApplyCoordinatesCompression(rectanglesCount, rectangles, xs, ys);

    //belongs[x][y][rectangleIndex] is used to indicate whether cell (x, y) is inside rectangle with index rectangleIndex or not
    vector<vector<vector<bool> > > belongs(xs.size() - 1, vector<vector<bool> >(ys.size() - 1, vector<bool>(rectanglesCount, false)));

    FillBelongs(rectanglesCount, rectangles, belongs);
    cellsCount = CountCells(xs, ys, belongs);
    cout << "Cells count is: " << cellsCount << endl;
}
