#include "terrainfactory.hpp"


TerrainFactory::TerrainFactory(){}
TerrainFactory::~TerrainFactory(){}

static MeshComponent TerrainFactory::CA(int x, int y, int percent, int affinity, int smooth)
{

}

void TerrainFactory::RandomFill(Grid& grid, int percent)
{
	// seed the random generator.
	//srand(time(0 + seedShift));
	//srand(time(NULL));

	// flip the elements in the grid.
	for (int x = 0; x < grid.getRows(); ++x)
	{
		for (int y = 0; y < grid.getColumns(); ++y)
		{
			int random = rand() % 101;
			if (random < percent)
			{
				grid.Flip(x, y);
			}
		}
	}
}


int TerrainFactory::GetNeighbors(Grid& grid, int x, int y, int neighborScanDistance)
{
	// since tiles are still considered to be path-connected
	// if they are diagonal, we will still consider diagonal
	// tiles as neighbors.
	int count = 0;
	for (int i = x - neighborScanDistance; i <= x + neighborScanDistance; ++i)
	{
		// ignore tiles outside the bounds of the map.
		if (i < 0 || i >= grid.getColumns())
		{
			continue;
		}
		
		for (int j = y - neighborScanDistance; j <= y + neighborScanDistance; ++j)
		{
			// ignore tiles outside the bounds of the map.	
			if (j < 0 || j >= grid.getRows())
			{
				continue;
			}

			// ignore itself.
			if (j == y && i == x)
			{
				continue;
			}

			// now check if (i, j) is an activated square.
			if (grid.getElement(i, j))
			{
				++count;
			}
		}
	}
	return count;
}


Grid TerrainFactory::Smooth(Grid& grid, int neighborTolerance, int neighborScanDistance)
{
	// get a blank grid. this grid will be filled in by
	// scanning the given grid. 
	Grid smoothGrid(grid.getRows(), grid.getColumns());

	for (int x = 0; x < grid.getRows(); ++x)
	{
		for (int y = 0; y < grid.getColumns(); ++y)
		{
			// check if we should convert the grid to its
			// neighbors' orientation.
			if (GetNeighbors(grid, x, y, neighborScanDistance) >= neighborTolerance)
			{
				smoothGrid.setElement(x, y, 1);	
			}
			else
			{
				smoothGrid.setElement(x, y, 0);
			}
		}
	}
	return smoothGrid;
}

