#include "Mesh.h"




ArcticFox::Graphics::Mesh::Mesh() {
/*	glm::vec3 QoudPositionTemplate[8] = { {-0.5f, -0.5f, 0.0f},{-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f},{-0.5f, -0.5f, 0.0f}, {0.5f, 0.5f, 0.0f},{-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f},{-0.5f, -0.5f, 0.0f} };

	uint32_t ind[6] = { 0, 1, 2, 2, 3, 0 };

	m_VBO = VertexBuffer::Create(QoudPositionTemplate, sizeof(QoudPositionTemplate));
	m_IBO = IndexBuffer::Create(ind, sizeof(ind));

	m_VBO->SetLayout({ {"a_Position", DataType::FLOAT_3, false},
					{"a_Normals", DataType::FLOAT_3, false},
		});


	m_VAO = VertexArray::Create();
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);*/
}

void ArcticFox::Graphics::Mesh::LoadFile(std::filesystem::path path) {
	m_path = path;

	AppFrame::ResourceMesh meshRes = AppFrame::ResourceManager::GetInstance()->GetResource<AppFrame::ResourceMesh>(path);

	std::vector<float> vertex;
	std::vector<uint32_t> Indices;

	if (meshRes.IsAvailable() || meshRes.Get()->mFlags & AI_SCENE_FLAGS_INCOMPLETE /*|| !meshRes->Get()->mRootNode*/) {
		int numMeshes = meshRes.Get()->mNumMeshes;
		for (uint32_t m = 0; m < numMeshes; m++) {
			const aiMesh *mesh = meshRes.Get()->mMeshes[m];
		
			int numVertices = mesh->mNumVertices;
			for (uint32_t g = 0; g < numVertices; g++) {
				vertex.push_back(mesh->mVertices[g].x);
				vertex.push_back(mesh->mVertices[g].y);
				vertex.push_back(mesh->mVertices[g].z);

				vertex.push_back(mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][g].y : 0);
				vertex.push_back(mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][g].x : 0);
			}

			int numFaces = mesh->mNumFaces;
			for (uint32_t i = 0; i < numFaces; i++) {
				const aiFace& face = mesh->mFaces[i];
				for (uint32_t j = 0; j < face.mNumIndices; j++) {
					Indices.push_back(face.mIndices[j]);
				}
			}
		}

		m_VBO = VertexBuffer::Create(vertex.data(), vertex.size() * sizeof(float));
		m_IBO = IndexBuffer::Create(Indices.data(), Indices.size()/* * sizeof(unsigned int)*/);
		
		m_VBO->SetLayout({	{"a_Position", DataType::FLOAT_3, false},
							{"a_TextureCoords", DataType::FLOAT_2, false}
			});


		m_VAO = VertexArray::Create();
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetIndexBuffer(m_IBO);
	}
}

ArcticFox::Graphics::Mesh::~Mesh() { }