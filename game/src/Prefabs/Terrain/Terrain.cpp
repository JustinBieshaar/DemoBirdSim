#include "Terrain.h"
#include <vector>
#include <Components/TextureComponent.h>
#include <Components/MeshComponent.h>
#include <TexturedShader.h>
#include "../../Global/Globals.h"

Terrain::Terrain(std::shared_ptr<Loader> loader, const glm::vec3& position) : GameObject(glm::vec3(position.x * Terrain_Size, 0, position.z * Terrain_Size))
{
	generate(loader);
    addComponent<TextureComponent>(loader, "terrain.png");
}

void Terrain::generate(std::shared_ptr<Loader> loader)
{
    int count = Terrain_VertexCount * Terrain_VertexCount;
    std::vector<float> vertices(count * 3);
    std::vector<float> normals(count * 3);
    std::vector<float> textureCoordinates(count * 2);
    std::vector<GLuint> indices(6 * (Terrain_VertexCount - 1) * (Terrain_VertexCount - 1));

    int vertexPointer = 0;
    for (int i = 0; i < Terrain_VertexCount; i++)
    {
        for (int j = 0; j < Terrain_VertexCount; j++)
        {
            vertices[vertexPointer * 3] = (float)j / ((float)Terrain_VertexCount - 1) * Terrain_Size;
            vertices[vertexPointer * 3 + 1] = 0;
            vertices[vertexPointer * 3 + 2] = (float)i / ((float)Terrain_VertexCount - 1) * Terrain_Size;

            normals[vertexPointer * 3] = 0;
            normals[vertexPointer * 3 + 1] = 1;
            normals[vertexPointer * 3 + 2] = 0;

            textureCoordinates[vertexPointer * 2] = (float)j / ((float)Terrain_VertexCount - 1);
            textureCoordinates[vertexPointer * 2 + 1] = (float)i / ((float)Terrain_VertexCount - 1);

            vertexPointer++;
        }
    }

    int pointer = 0;
    for (int gz = 0; gz < Terrain_VertexCount - 1; gz++)
    {
        for (int gx = 0; gx < Terrain_VertexCount - 1; gx++)
        {
            int topLeft = (gz * Terrain_VertexCount) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * Terrain_VertexCount) + gx;
            int bottomRight = bottomLeft + 1;

            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }

    auto [vao, vertexCount] = loader->loadToMeshComponent(vertices, textureCoordinates, normals, indices);
    auto meshComp = addComponent<MeshComponent>(vao, vertexCount);
    meshComp->setShader(new TexturedShader());
    meshComp->setRepeat(40);
}
