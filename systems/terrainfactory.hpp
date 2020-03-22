#pragma once

#include <iostream>
#include "../ecs/ecsentity.hpp"
#include "../components/meshcomponent.hpp"

// in charge of creating the mesh for a terrain.
// returns a mesh component.
class TerrainFactory
{

public:

	static MeshComponent CA(int x, int y, int percent, int affinity, int smooth);


private:

	TerrainFactory();
	~TerrainFactory();

};
