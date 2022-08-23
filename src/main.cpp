#include <SFML/Graphics.hpp>
#include "Controller.h"


int main()	try
{
	Controller game;
	game.runGame();
	return EXIT_SUCCESS;
}


catch (std::exception& e) {
	std::cerr << "Exception: " << e.what() << '\n'; return EXIT_FAILURE;
}

catch (...) {
	std::cerr << "Unknown exception\n"; return EXIT_FAILURE;
}

//#include <stdio.h>
//#include <experimental/vector>
//#include <iostream>
//
//
//using namespace std;
//class Solution
//{
//public:
//	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor);
//	void flood_fill(vector<vector<int>>& image, int sr, int sc, int newColor, int row, int col, int oldColor);
//};
//
//void Solution::flood_fill(vector<vector<int>>& image, int sr, int sc, int newColor, int row, int col, int oldColor)
//{
//	if (sr < 0 || sc < 0 || sr >= row || sc >= col)
//		return;
//	if (image[sr][sc] != oldColor)
//		return;
//	if (image[sr][sc] == newColor)
//		return;
//
//	image[sr][sc] = newColor;
//
//	flood_fill(image, 1 + sr, sc, newColor, row, col, oldColor);
//	flood_fill(image, sr, 1 + sc, newColor, row, col, oldColor);
//	flood_fill(image, -1 + sr, sc, newColor, row, col, oldColor);
//	flood_fill(image, sr, -1 + sc, newColor, row, col, oldColor);
//	return;
//
//}
//vector<vector<int>> Solution::floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
//	int row = image.size();
//	int col = image[0].size();
//	vector<vector<int>>imageo = image;
//	int oldColor = image[sr][sc];
//	flood_fill(imageo, sr, sc, newColor, row, col, oldColor);
//	return imageo;
//
//}
//
//
//
//int	main()
//{
//	int tc;
//	std::cin >> tc;
//	while (tc--)
//	{
//		int n, m;
//
//		cin >> n >> m;
//		vector < vector < int >>image(n, vector < int >(m, 0));
//
//		for (int i = 0; i < n; i++)
//		{
//			for (int j = 0; j < m; j++)
//				cin >> image[i][j];
//		}

//		int sr, sc, newColor;
//		cin >> sr >> sc >> newColor;
//		Solution obj;
//		vector < vector < int >>ans = obj.floodFill(image, sr, sc, newColor);
//		for (auto i : ans)
//		{
//			for (auto j : i)
//				cout << j << " ";
//			cout << "\n";
//
//
//		}
//		return 0;
//
//	}
//
//}
