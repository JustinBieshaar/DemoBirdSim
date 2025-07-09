#include "../../Utils/ObjLoader.h"
#include "Capsule.h"
#include "../../Shaders/ColorShader.h"
#include "../../Shaders/TexturedShader.h"

Capsule::Capsule(std::shared_ptr<Loader> loader, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : GameObject(position, rotation, scale)
{
	auto meshComponent = ObjLoader::loadMeshFromObjFile("Capsule", loader);

	ColorShader* shader = new ColorShader(); // todo, no new instance here..
	meshComponent->m_shader = shader;
	addComponent(meshComponent);
}
