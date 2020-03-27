#include "gridcomponent.hpp"


/********* constructors/destructors *********/
GridComponent::GridComponent(int rows, int columns)
{
	// initialize vectors for the matrix data
	for (int i = 0; i < rows; ++i)
	{
		std::vector<Block> blankColumn(columns);
		grid.push_back(blankColumn);
	}
}
GridComponent::~GridComponent(){}





/********* getters/setters for rows/columns/elements *********/

int GridComponent::getRows()
{
	return grid.size();
}
int GridComponent::getColumns()
{
	return grid[0].size();
}

Block GridComponent::getElement(int row, int column)
{
	return this->grid[row][column];
}
void GridComponent::setElement(int row, int column, Block block)
{
	this->grid[row][column]=block;
}



/********* Utility *********/

void GridComponent::Print()
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
