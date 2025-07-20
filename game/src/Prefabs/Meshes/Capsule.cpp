#include <ObjLoader.h>
#include <Components/TextureComponent.h>
#include "Capsule.h"
#include "../../Shaders/ColorShader.h"
#include "../../Shaders/TexturedShader.h"
#include <Components/MeshComponent.h>

Capsule::Capsule(std::shared_ptr<Loader> loader, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : GameObject(position, rotation, scale)
{
	auto [vao, vertexCount] = ObjLoader::loadMeshFromObjFile("Capsule", loader);

	ColorShader* shader = new ColorShader(glm::vec3{.56f,1,.56f}); // todo, no new instance here..
	auto meshComponent = addComponent<MeshComponent>(vao, vertexCount);
	meshComponent->setShader(shader);
	//addComponent(std::make_shared<TextureComponent>(loader, "terrain.png"));
}
