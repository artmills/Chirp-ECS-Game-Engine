#include "rendersystem.hpp"

// constants for building projection matrix.
float RenderSystem::m_fieldOfViewRadians = (glm::pi<float>()) / 3.0f;
float RenderSystem::m_nearPlane = 0.01f;
float RenderSystem::m_farPlane = 1000.0f;



RenderSystem::RenderSystem(uint width, uint height) 
: m_width(width), m_height(height) 
{
	CreatePerspectiveProjectionMatrix(m_projectionMatrix, m_fieldOfViewRadians, m_width, m_height, m_nearPlane, m_farPlane);
}

void RenderSystem::PrintMatrix(glm::mat4& matrix)
{
	// matrices are in column-major order. 
	for (uint i = 0; i < 4; i++)
	{
		for (uint j = 0; j < 4; j++)
		{
			std::cout << matrix[i][j] << "   ";
		}
	std::cout << std::endl;
	}
	std::cout << std::endl;
}

void RenderSystem::Start()
{
	// initialize shader.
	m_basicShader = BasicShader();
	m_basicShader.Initialize();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

void RenderSystem::Update(float dt)
{
	ClearScreen();
	
	m_basicShader.Start();

	// iterate through the meshes.
	std::vector<MeshComponent>& meshes = m_meshes.getArray();
	for (uint i = 0; i < m_meshes.NumberOfComponents(); i++)
	{
		MeshComponent& mesh = meshes[i];
		uint entityID = mesh.getEntityHandle();
		uint transformHandle = m_entities[entityID][1];
		TransformComponent* transform = m_transforms.getComponent(transformHandle);
		if (transformHandle != -1 && transform != nullptr) // then the transform exists.
		{
			// render:
			InitializeMesh(mesh);
			LoadMatrix(*transform);
			glDrawElements(GL_TRIANGLES, mesh.getCount(), GL_UNSIGNED_INT, nullptr);
			Reset_VAO();
		}
	}

	m_basicShader.Stop();
}

void RenderSystem::InitializeMesh(MeshComponent& mesh)
{
	glBindVertexArray(mesh.get_VAO_ID());

	glEnableVertexAttribArray(0); // vPosition.
	glEnableVertexAttribArray(1); // vColor.
}

void RenderSystem::LoadMatrix(TransformComponent& transform)
{
	glm::mat4 mvp = m_projectionMatrix * Mathematics::GetTransformationMatrix(transform);
	//PrintMatrix(mvp);
	m_basicShader.LoadModelViewProjectionMatrix(mvp);
}

void RenderSystem::Reset_VAO()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

// projection matrix:
void RenderSystem::CreatePerspectiveProjectionMatrix(glm::mat4& matrix, float fieldOfViewRadians, uint width, uint height, float nearPlane, float farPlane)
{
	Mathematics::GetPerspectiveFieldOfViewMatrix(matrix, fieldOfViewRadians, width, height, nearPlane, farPlane);
}

// rendering:

void RenderSystem::Render()
{

}

void RenderSystem::ClearScreen()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}





// component management: 

void RenderSystem::RegisterEntity(uint entityID, TransformComponent& transform, MeshComponent& mesh)
{
	// load the model into the GPU.
	Loader::PrepareMesh(mesh);	

	// add components to the arrays and assign those handles to the entity.
	int transformHandle = m_transforms.AddComponent(transform);
	int meshHandle = m_meshes.AddComponent(mesh);
	std::vector<int> handles { transformHandle, meshHandle };
	m_entities.emplace(entityID, handles);

	std::cout << "Registering entity " << entityID << " to RenderSystem with components at indices " << transformHandle << " and " << meshHandle << std::endl;
}

void RenderSystem::DeregisterEntity(uint entityID)
{
	// remove components first:
	DeleteComponent(ComponentType::Transform, m_entities[entityID][0]);
	DeleteComponent(ComponentType::Mesh, m_entities[entityID][1]);

	m_entities.erase(entityID);
}

void RenderSystem::DeleteComponent(ComponentType componentType, uint handle)
{
	switch (componentType)
	{
		case ComponentType::Transform:
			m_transforms.RemoveComponent(handle);
			break;
		case ComponentType::Mesh:
			m_meshes.RemoveComponent(handle);
			break;
		default:
			break;
	}
}

void RenderSystem::SynchronizeTransforms(ECSComponentArray<TransformComponent>& from)
{
	m_transforms.TrustCopyFrom(from);	
}

ECSComponentArray<TransformComponent>& RenderSystem::ExportTransforms()
{
	return m_transforms;
}


void RenderSystem::PrintArrays()
{
	std::vector<TransformComponent>& transforms = m_transforms.getArray();
	for (uint i = 0; i < transforms.size(); i++)
	{
		std::cout << "Entity " << transforms[i].getEntityHandle() << " is at coordinates " << transforms[i].x() << ", " << transforms[i].y() << ", " << transforms[i].z() << std::endl;
	}
}








