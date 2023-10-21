#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>

#include <cstdio>

int width = 1280;
int height = 720;

GLfloat vertices[] = {
    -1, -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1,
    1, -1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1,
    -1, -1, -1, -1, -1, 1, 1, -1, 1, 1, -1, -1,
    -1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1,
    -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1,
    -1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 1};

GLfloat colors[] =
    {
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0};

void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
}

void drawCube()
{

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "C++ OpenGL Test Area", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyboard);

    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glViewport(0, 0, width, height);

        /* Render here */
        glClearColor(0.0, 192 / 256, 1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0, 0, 5);
        drawCube();

        glFlush();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}