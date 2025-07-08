#include "Cube.h"
#include "../Shaders/Shader.h"
#include "../Shaders/ColorShader.h"
#include "../Shaders/TexturedShader.h"

Cube::Cube(Loader* loader)
{
    std::vector<float> vertices = {
        // positions        
                -0.5f,0.5f,0,
                -0.5f,-0.5f,0,
                0.5f,-0.5f,0,
                0.5f,0.5f,0,

                -0.5f,0.5f,1,
                -0.5f,-0.5f,1,
                0.5f,-0.5f,1,
                0.5f,0.5f,1,

                0.5f,0.5f,0,
                0.5f,-0.5f,0,
                0.5f,-0.5f,1,
                0.5f,0.5f,1,

                -0.5f,0.5f,0,
                -0.5f,-0.5f,0,
                -0.5f,-0.5f,1,
                -0.5f,0.5f,1,

                -0.5f,0.5f,1,
                -0.5f,0.5f,0,
                0.5f,0.5f,0,
                0.5f,0.5f,1,

                -0.5f,-0.5f,1,
                -0.5f,-0.5f,0,
                0.5f,-0.5f,0,
                0.5f,-0.5f,1

    };

    std::vector<float> textureCoords = {
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0

    };

    std::vector<float> normals = {
        // Front face (-Z)
         0, 0, -1,
         0, 0, -1,
         0, 0, -1,
         0, 0, -1,

         // Back face (+Z)
         0, 0, 1,
         0, 0, 1,
         0, 0, 1,
         0, 0, 1,

         // Right face (+X)
         1, 0, 0,
         1, 0, 0,
         1, 0, 0,
         1, 0, 0,

         // Left face (-X)
         -1, 0, 0,
         -1, 0, 0,
         -1, 0, 0,
         -1, 0, 0,

         // Top face (+Y)
            0, 1, 0,
            0, 1, 0,
            0, 1, 0,
            0, 1, 0,

            // Bottom face (-Y)
             0, -1, 0,
             0, -1, 0,
             0, -1, 0,
             0, -1, 0,
    };

    std::vector<GLuint> indices =
    {
        0,1,3, 
        3,1,2, 
        4,5,7, 
        7,5,6,
        8,9,11,
        11,9,10,
        12,13,15,
        15,13,14,
        16,17,19,
        19,17,18,
        20,21,23,
        23,21,22
    };

    auto meshComponent = loader->loadToMeshComponent(vertices, textureCoords, normals, indices);

    TexturedShader* shader = new TexturedShader(); // todo, no new instance here..
    meshComponent->m_shader = shader;
    addComponent(meshComponent);
}
