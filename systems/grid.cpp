#include "grid.hpp"


/********* constructors/destructors *********/
Grid::Grid(int rows, int columns)
{
	// initialize vectors for the matrix data
	for (int i = 0; i < rows; ++i)
	{
		std::vector<Block> blankColumn(columns);
		grid.push_back(blankColumn);
	}
}
Grid::~Grid(){}





/********* getters/setters for rows/columns/elements *********/

int Grid::getRows()
{
	return grid.size();
}
int Grid::getColumns()
{
	return grid[0].size();
}

Block Grid::getElement(int row, int column)
{
	return this->grid[row][column];
}
void Grid::setElement(int row, int column, Block block)
{
	this->grid[row][column]=block;
}



/********* Utility *********/

void Grid::Print()
{
	if (this->grid.size() == 0)
	{
		std::cout << "[ ]" << std::endl;
	}
	else 
	{
		for (int j = getColumns() - 1; j >= 0; --j)
		{
			for (int i = 0; i < getRows(); ++i)
			{
				std::cout << (int)grid[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
