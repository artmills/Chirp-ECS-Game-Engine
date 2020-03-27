#include "terrainfactory.hpp"


TerrainFactory::TerrainFactory(){}
TerrainFactory::~TerrainFactory(){}

GridComponent TerrainFactory::CA(int x, int y, int percent, int affinity, int smooth)
{
	// create the grid and perform cellular automation.
	GridComponent grid(x, y);
	RandomFill(grid, percent);
	for (int i = 0; i < smooth; ++i)
	{
		grid = Smooth(grid, affinity, 1);
	}

	//grid.Print();

	return grid;
}

void TerrainFactory::RandomFill(GridComponent& grid, int percent)
{
	// seed the random generator.
	// This should really be done elsewhere.
	srand(time(NULL));

	// flip the elements in the grid.
	for (int x = 0; x < grid.getRows(); ++x)
	{
		for (int y = 0; y < grid.getColumns(); ++y)
		{
			int random = rand() % 101;
			if (random < percent)
			{
				grid.setElement(x, y, Block::stone);
			}
		}
	}
}

int TerrainFactory::GetNeighbors(GridComponent& grid, int x, int y, int neighborScanDistance)
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
			if ((int)grid.getElement(i, j))
			{
				++count;
			}
		}
	}
	return count;
}


GridComponent TerrainFactory::Smooth(GridComponent& grid, int affinity, int neighborScanDistance)
{
	// get a blank grid. this grid will be filled in by
	// scanning the given grid. 
	GridComponent smoothGrid(grid.getRows(), grid.getColumns());

	for (int x = 0; x < grid.getRows(); ++x)
	{
		for (int y = 0; y < grid.getColumns(); ++y)
		{
			// check if we should convert the grid to its
			// neighbors' orientation.
			if (GetNeighbors(grid, x, y, neighborScanDistance) >= affinity)
			{
				smoothGrid.setElement(x, y, Block::stone);	
			}
			else
			{
				smoothGrid.setElement(x, y, Block::air);
			}
		}
	}
	return smoothGrid;
}


MeshComponent TerrainFactory::ConvertToMesh(uint entityID, GridComponent& grid, float blockSize)
{
	std::vector<Vertex> vertices;
	std::vector<uint> triangles;

	// create vertices:
	int i = 0;
	for (int y = 0; y < grid.getColumns(); ++y)
	{
		for (int x = 0; x < grid.getRows(); ++x)
		{
			// skip over air blocks.
			if (!(int)grid.getElement(x, y))
			{
				continue;
			}

			// color is temporarily specified here.
			int r = 0;
			int g = 0;
			int b = 0;
			int a = 1;

			// triangulate the given block.
			Vertex botLeft(blockSize * x, blockSize * y, 0, r, g, b, a);	
			Vertex botRight(blockSize * x + blockSize, blockSize * y, 0, r, g, b, a);	
			Vertex topRight(blockSize * x + blockSize, blockSize * y + blockSize, 0, r, g, b, a);	
			Vertex topLeft(blockSize * x, blockSize * y + blockSize, 0, r, g, b, a);	

			// add these vertices to the lists in the proper order.
			vertices.push_back(botLeft);
			vertices.push_back(botRight);
			vertices.push_back(topRight);
			vertices.push_back(topLeft);

			triangles.push_back(i);
			triangles.push_back(i+1);
			triangles.push_back(i+2);
			triangles.push_back(i);
			triangles.push_back(i+2);
			triangles.push_back(i+3);
			i += 4;
		}
	}

	return MeshComponent(entityID, vertices, triangles);
}
