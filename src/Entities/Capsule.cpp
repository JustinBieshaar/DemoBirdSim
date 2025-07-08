#include "../Utils/ObjLoader.h"
#include "Capsule.h"
#include "../Shaders/ColorShader.h"
#include "../Shaders/TexturedShader.h"

Capsule::Capsule(Loader* loader)
{
	auto meshComponent = ObjLoader::loadMeshFromObjFile("Capsule", loader);

	ColorShader* shader = new ColorShader(); // todo, no new instance here..
	meshComponent->m_shader = shader;
	addComponent(meshComponent);
}
