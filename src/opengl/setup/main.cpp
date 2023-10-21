#include <GL/glew.h> // should be included before glfw3.h
#include <GLFW/glfw3.h>

#include <iostream>

int main(int argc, char *argv[])
{
    GLFWwindow *window{};

    // Initialize GLFW3 library
    if (!glfwInit())
    {
        std::cerr << "Unable to initialize GLFW library";
        return -1;
    }

    window = glfwCreateWindow(1240, 768, "Hello World", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Unable to create window.";
        glfwTerminate();
        return -1;
    }

    // create opengl context
    glfwMakeContextCurrent(window);

    // Initialize GLEW library, this should be done after creating opengl context
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW library";
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Legacy opengl
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5F, -0.5F);
        glVertex2f(0.0F, 0.5F);
        glVertex2f(0.5F, -0.5F);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
