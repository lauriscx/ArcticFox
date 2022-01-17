#pragma once
#include <AppFrame.h>
#include <glm/glm.hpp>
#include <map>
#include "TextureInterface.h"

class Material {
public:

private:
	glm::vec4 m_Color;
	glm::vec2 m_Specularity;

	std::map<std::string, TextureInterface*> m_Textures;
};