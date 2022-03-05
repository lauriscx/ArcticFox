#pragma once

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Application/Resources/ResourceMesh.h"
#include <AppFrame.h>
#include "Engine/Core/Modules/Render/Buffer.h"

namespace ArcticFox {
	namespace Graphics {
		class Mesh {
		public:
			Mesh();

			void LoadFile(std::filesystem::path path);
			inline VertexArray* GetVertextArray() { return m_VAO; };
			inline std::filesystem::path getPath() { return m_path; };

			~Mesh();
		private:
			VertexArray* m_VAO;
			VertexBuffer* m_VBO;
			IndexBuffer* m_IBO;

			std::filesystem::path m_path;
		};
	}
}