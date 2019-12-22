#pragma once

#include <GL/glew.h>

#include <vector>
#include <iostream>

#include "../utilities.hpp"
#include "../components/meshcomponent.hpp"

// essentially a static class that loads model data into the GPU and returns a RawModel object with its VAO ID.
class Loader
{
public:

	// transform an array of vertices to a RawModel object.
	static void PrepareMesh(MeshComponent& mesh);

private:

	// pass data to GPU:
	static void VAO_Initialize(uint& vaoID);
	static void VAO_Unbind();
	static void AttributeList_Triangles(std::vector<uint>& triangles);
	static void AttributeList_StoreData(std::vector<Vertex>& vertices);


	// lists of IDs of all VBOs and VAOs.
	static std::vector<uint*> m_vaos;

	// manage lists:
	static void Add_VAO(uint* vaoID);
	static void Delete_VAOs();

	Loader();
	~Loader();

};
