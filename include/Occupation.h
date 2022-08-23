#pragma once

#include "Consts.h"

enum class Occupation
{
   Free, // clear
   Occupied, // blue
   Potential, // green
   EnemyArea, // clear but with invisible infection
   Dangerous, // red

};

class OccupationSolver 
{
public:
	static void floodFill(std::vector<std::vector<Occupation>>& grid, int row, int col,
		Occupation newOccStatus);
private:
	static void floodFillRecursive(std::vector<std::vector<Occupation>>& grid, int row, int col,
		Occupation newOccStatus, Occupation oldOccStatus);

};