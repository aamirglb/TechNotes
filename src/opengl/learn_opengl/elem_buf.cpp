#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <functional>

struct color
{
    float red;
    float green;
    float blue;
    float alpha;
};

color bg{.2f, .3f, .3f, 1.f};
auto d = std::bind(std::uniform_real_distribution(-1.f, 1.f), std::mt19937(std::random_device{}()));

std::string read_shader_from_file(const std::string &filename)
{
    std::ifstream stream(filename);
    std::ostringstream ostr;
    ostr << stream.rdbuf();
    return ostr.str();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    std::cout << "window size (" << width << ", " << height << ")" << std::endl;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        bg = {d(), d(), d(), 1.0f};
    }
}

int main()
{
    // GLFW init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // glViewport(0, 0, 800, 600);

    // vertex shader
    std::string vertex_shader_src = read_shader_from_file("basic_vertex_shader.glsl");
    const char *vsrc = vertex_shader_src.c_str();
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vsrc, nullptr);
    glCompileShader(vertex_shader);

    int success;
    char info[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info);
        std::cerr << "Error: vertex shader: " << std::endl;
        std::cerr << info << std::endl;
    }

    // fragment shader
    std::string fragment_shader_src = read_shader_from_file("basic_fragment_shader.glsl");
    const char *fsrc = fragment_shader_src.c_str();
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fsrc, nullptr);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        memset(info, 0, 512);
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info);
        std::cerr << "Error: fragment shader: " << std::endl;
        std::cerr << info << std::endl;
    }

    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, info);
        std::cerr << "Error: Link failure: " << std::endl;
        std::cerr << info << std::endl;
    }
    glUseProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // triangle vertices
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f}; // top left

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int vao_id, vbo_id, ebo_id;
    glGenVertexArrays(1, &vao_id);
    glGenBuffers(1, &vbo_id);
    glGenBuffers(1, &ebo_id);

    glBindVertexArray(vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        // process input
        processInput(window);

        // render frame
        glClearColor(bg.red, bg.green, bg.blue, bg.alpha); // state setting function
        glClear(GL_COLOR_BUFFER_BIT);                      // state using function

        glUseProgram(shader_program);
        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao_id);
    glDeleteBuffers(1, &vbo_id);
    glDeleteBuffers(1, &ebo_id);
    glDeleteProgram(shader_program);

    glfwTerminate();
    return 0;
}