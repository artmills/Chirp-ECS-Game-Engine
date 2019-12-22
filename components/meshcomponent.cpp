#include "meshcomponent.hpp"

MeshComponent::MeshComponent(uint entityID)
{
	setEntityHandle(entityID);
}
MeshComponent::MeshComponent(uint entityID, std::vector<Vertex> vertices, std::vector<uint> triangles)
	: m_vertices(vertices), m_triangles(triangles)
{
	setEntityHandle(entityID);
}
MeshComponent::MeshComponent(std::vector<Vertex> vertices, std::vector<uint> triangles)
	: m_vertices(vertices), m_triangles(triangles) {} 

uint MeshComponent::get_VAO_ID()
{
	return m_vaoID;
}
uint MeshComponent::getCount()
{
	return m_triangles.size();
}
void MeshComponent::set_VAO_ID(uint vaoID)
{
	m_vaoID = vaoID;
}

std::vector<Vertex>& MeshComponent::getVertices()
{
	return m_vertices;
}
std::vector<uint>& MeshComponent::getTriangles()
{
	return m_triangles;
}

void MeshComponent::CreateModel(std::vector<Vertex> vertices, std::vector<uint> triangles)
{
	m_vertices = vertices;
	m_triangles = triangles;
}
