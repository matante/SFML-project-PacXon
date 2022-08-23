#include "Occupation.h"

void OccupationSolver::floodFillRecursive(std::vector<std::vector<Occupation>>& grid, int row, int col,
	Occupation newOccStatus, Occupation oldOccStatus)
{
	if (row < 0 || col < 0 || row >= ROWS || col >= COLS) // if on edges
		return;
	if (grid[row][col] != oldOccStatus) // if it's not a state we want to change
		return;
	if (grid[row][col] == newOccStatus) // already new state
		return;

	grid[row][col] = newOccStatus; // change

	floodFillRecursive(grid, 1 + row, col, newOccStatus, oldOccStatus);
	floodFillRecursive(grid, row, 1 + col, newOccStatus, oldOccStatus);
	floodFillRecursive(grid, -1 + row, col, newOccStatus, oldOccStatus);
	floodFillRecursive(grid, row, -1 + col, newOccStatus, oldOccStatus);
	return;

}
// ------------------------------------


void OccupationSolver::floodFill(
	std::vector<std::vector<Occupation>>& grid, int row, int col,
	Occupation newOccStatus) 
{
	
	Occupation oldOccStatus = Occupation::Free; // could send this in func, but easier to understand
	OccupationSolver::floodFillRecursive(grid, row, col , newOccStatus, oldOccStatus);
}