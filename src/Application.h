#pragma once
#include "GLFW/glfw3.h"

class Application
{
public:
    bool init();
    void processInput(float deltaTime);

    void render();
    void renderUI();

    void run();

private:
    void cleanup();

    GLFWwindow* m_window;

    float m_lastTime;

    int cubeSize;
    GLuint vertexBuffer;

    const GLdouble coordinates[8][3] = {
        {-0.5, -0.5, -0.5},
        {0.5, -0.5, -0.5},
        {0.5, -0.5, 0.5},
        {-0.5, -0.5, 0.5},
        {-0.5, 0.5, 0.5},
        {-0.5, 0.5, -0.5},
        {0.5, 0.5, -0.5},
        {0.5, 0.5, 0.5}
    };

};

