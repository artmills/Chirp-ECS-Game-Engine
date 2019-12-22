#pragma once

#include <vector>

#include "../ecs/ecscomponent.hpp"
#include "vertex.hpp"

// contains data necessary for rendering:
// * model vertices.
// * triangle configuration .
// * vaoID.
class MeshComponent : public ECSComponent<MeshComponent>
{
public:

	MeshComponent(uint entityID);
	MeshComponent(std::vector<Vertex> vertices, std::vector<uint> triangles);
	MeshComponent(uint entityID, std::vector<Vertex> vertices, std::vector<uint> triangles);

	// getters/setters:
	uint get_VAO_ID();
	uint getCount();
	void set_VAO_ID(uint vaoID);

	std::vector<Vertex>& getVertices();
	std::vector<uint>& getTriangles();
	
	void CreateModel(std::vector<Vertex> vertices, std::vector<uint> triangles);

private:

	// raw model data:
	std::vector<Vertex> m_vertices;
	std::vector<uint> m_triangles;

	// OpenGL rendering data:
	uint m_vaoID;

};
