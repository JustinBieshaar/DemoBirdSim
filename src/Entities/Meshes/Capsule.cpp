#include "../../Utils/ObjLoader.h"
#include "Capsule.h"
#include "../../Shaders/ColorShader.h"
#include "../../Shaders/TexturedShader.h"
#include "../../ECS/Components/TextureComponent.h"

Capsule::Capsule(std::shared_ptr<Loader> loader, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : GameObject(position, rotation, scale)
{
	auto meshComponent = ObjLoader::loadMeshFromObjFile("Capsule", loader);

	ColorShader* shader = new ColorShader(glm::vec3{.56f,1,.56f}); // todo, no new instance here..
	meshComponent->setShader(shader);
	addComponent(meshComponent);
	//addComponent(std::make_shared<TextureComponent>(loader, "terrain.png"));
}
