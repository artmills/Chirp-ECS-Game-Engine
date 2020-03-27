#pragma once
#include <iostream>
#include <vector>

#include "block.hpp"
#include "../ecs/ecscomponent.hpp"

/** Representing a 2D terrain. */
class GridComponent : public ECSComponent<GridComponent>
{

public:

	/** Create a blank grid with the specified number of rows and columns. 
	 *
	 * This grid takes values in the block struct. */
	GridComponent(int rows, int columns);
	~GridComponent();

	
	/** Get the number of rows of the grid. */
	int getRows();


	/** Get the number of columns of the grid. */
	int getColumns();


	/** Get the element at this location. */
	Block getElement(int row, int column);


	/** Set the element at this location to the given value. */
	void setElement(int row, int column, Block block);


	/** Utility.
	 * Print out the grid as a matrix. */
	void Print();

private:

	/** The actual grid data as a 2D list of blocks. */
	std::vector<std::vector<Block>> grid;

};
