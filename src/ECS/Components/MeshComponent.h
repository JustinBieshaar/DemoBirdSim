#pragma once

#include "Component.h"

struct MeshComponent : Component
{
	unsigned int m_vertexArrayObject; // vertex array object
	unsigned int m_vertexCount;
};