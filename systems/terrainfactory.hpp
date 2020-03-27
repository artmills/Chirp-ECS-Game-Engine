#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../ecs/ecsentity.hpp"
#include "../components/meshcomponent.hpp"
#include "../components/gridcomponent.hpp"

/** Creates the mesh for the game's terrain.
 *
 * The process involves creating a grid of blocks using some terrain generation algorithm.
 * Available algorithms:
 *
 * 1) Cellular automation.
 *
 * Once the grid has been created, a mesh component will be created to suitably package the data for the GPU. */
class TerrainFactory
{

public:

	/** Create a grid from cellular automata.
	 * Parameters:
	 * 
	 * x,y : the size of the terrain grid.
	 *
	 * percent: initially, a grid is created that is randomly filled in with air and stone blocks. 
	 * This parameter chooses what percentage of the grid should be randomly filled in at this initial stage.
	 *
	 * affinity: next, each block is checked against its neighbors.
	 * If a majority of a block's neighbors are stone, the current block will become stone.
	 * Affinity controls how many of those neighbors must be stone for this to happen.
	 * Diagonals are counted and the block itself is not counted.
	 *
	 * smooth: the number of times the cellular automata algorithm should be run. */
	static GridComponent CA(int x, int y, int percent, int affinity, int smooth);


	/** Create the actual mesh component for the terrain.
	 *
	 * The terrain ID must be specified, probably from the ObjectFactory.
	 *
	 * The size of the block needs to be specified here.
	 * The actual location of the terrain will be provided by a TransformComponent, which will be managed by the ObjectFactory. 
	 * 
	 * A color is temporarily hard-coded in as black.
	 * Later, this should be determined by the block type. */
	static MeshComponent ConvertToMesh(const uint entityID, GridComponent& grid, float blockSize);



private:

	/** Randomly fill in a grid to be *percent* full. 
	 *
	 * Currently, this will only choose a block of the grid to be either air or stone. */
	static void RandomFill(GridComponent& grid, int percent);


	/** Count how many active (stone) neighbors are around the given point.
	 *
	 * neighborScanDistance should probably just be set to 1. 
	 * This counts all eight adjacent neighbors to a given block.
	 *
	 * Logic is there to avoid counting the block itself as a neighbor and to skip over the edges of the grid where there are no blocks. */
	static int GetNeighbors(GridComponent& grid, int x, int y, int neighborScanDistance);

	
	/** Apply the cellular automata algorithm. */
	static GridComponent Smooth(GridComponent& grid, int affinity, int neighborScanDistance);


	TerrainFactory();
	~TerrainFactory();

};
