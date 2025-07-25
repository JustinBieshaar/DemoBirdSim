#include "Terrain.h"
#include <vector>
#include <Components/TextureComponent.h>
#include <Components/MeshComponent.h>
#include <TexturedShader.h>
#include "../../Global/Globals.h"

Terrain::Terrain(std::shared_ptr<Loader> loader, const glm::vec3& position) : GameObject(glm::vec3(position.x * Terrain_Size, 0, position.z * Terrain_Size))
{
	generate(loader);
    addComponent<ECS::TextureComponent>(loader, "terrain.png");
}

void Terrain::generate(std::shared_ptr<Loader> loader)
{
    // Total number of vertices
    int count = Terrain_VertexCount * Terrain_VertexCount;

    // Allocate space for mesh attributes
    std::vector<float> vertices(count * 3);             // 3 components (x, y, z)
    std::vector<float> normals(count * 3);              // Flat normals (pointing up)
    std::vector<float> textureCoordinates(count * 2);   // 2D texture mapping
    std::vector<GLuint> indices(6 * (Terrain_VertexCount - 1) * (Terrain_VertexCount - 1)); // 2 triangles per square

    int vertexPointer = 0;

    // Generate vertex positions, normals, and texture coordinates
    for (int i = 0; i < Terrain_VertexCount; i++)
    {
        for (int j = 0; j < Terrain_VertexCount; j++)
        {
            // Vertex position in world space (flat terrain)
            vertices[vertexPointer * 3] = (float)j / ((float)Terrain_VertexCount - 1) * Terrain_Size;
            vertices[vertexPointer * 3 + 1] = 0; // height
            vertices[vertexPointer * 3 + 2] = (float)i / ((float)Terrain_VertexCount - 1) * Terrain_Size;

            // Flat normal (pointing straight up)
            normals[vertexPointer * 3] = 0;
            normals[vertexPointer * 3 + 1] = 1;
            normals[vertexPointer * 3 + 2] = 0;

            // Texture coordinate (normalized across the grid)
            textureCoordinates[vertexPointer * 2] = (float)j / ((float)Terrain_VertexCount - 1);
            textureCoordinates[vertexPointer * 2 + 1] = (float)i / ((float)Terrain_VertexCount - 1);

            vertexPointer++;
        }
    }

    // Generate indices for two triangles per square (forming quads)
    int pointer = 0;
    for (int gz = 0; gz < Terrain_VertexCount - 1; gz++)
    {
        for (int gx = 0; gx < Terrain_VertexCount - 1; gx++)
        {
            int topLeft = (gz * Terrain_VertexCount) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * Terrain_VertexCount) + gx;
            int bottomRight = bottomLeft + 1;

            // First triangle
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;

            // Second triangle
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }

    // Upload mesh data to GPU and get VAO and vertex count
    auto [vao, vertexCount] = loader->loadToMeshComponent(vertices, textureCoordinates, normals, indices);

    // Create mesh component and assign textured shader
    auto meshComp = addComponent<ECS::MeshComponent>(vao, vertexCount);
    meshComp->setShader(new TexturedShader());

    // Set UV repeat tiling factor (makes texture tile across terrain)
    meshComp->setRepeat(Terrain_Texture_Repeat);
}
