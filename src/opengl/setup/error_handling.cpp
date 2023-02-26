#include <GL/glew.h> // should be included before glfw3.h
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#define ASSERT(x) \
    if (!(x))     \
        __debugbreak();

#define GLCall(x)     \
    gl_clear_error(); \
    x;                \
    ASSERT(gl_log_call(#x, __FILE__, __LINE__))

static void gl_clear_error()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

static void gl_check_error()
{
    while (GLenum error = glGetError())
    {
        std::cerr << "OpenGL Error: (" << error << ")" << std::endl;
    }
}

static bool gl_log_call()
{
    while (GLenum error = glGetError())
    {
        std::cerr << "OpenGL Error: (" << error << ")" << std::endl;
        return false;
    }
    return true;
}
struct ShaderProgramSource
{
    std::string vertexSrc;
    std::string fragmentSrc;
};

static ShaderProgramSource parse_shaders(const std::string &file)
{
    std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << "cwd = " << cwd.string() << std::endl;

    enum class ShaderType
    {
        None = -1,
        Vertex = 0,
        Fragment = 1
    };

    std::ifstream stream{file};
    std::stringstream ss[2];
    ShaderType type = ShaderType::None;

    if (!stream.is_open())
    {
        std::cerr << "Unable to open shader file." << std::endl;
        return {};
    }

    std::string line;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::Vertex;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::Fragment;
        }
        else
        {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

// Documentation can be found at docs.gl

static GLuint compile_shader(GLuint type, const std::string &source)
{
    GLuint id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // query error state
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        // get error message
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // char message = (char *)alloca(length * sizeof(char));
        std::vector<char> message(length);
        glGetShaderInfoLog(id, length, &length, message.data());
        std::cerr << "Failed to compiled '" << (type == GL_VERTEX_SHADER ? "vertex" : "fragement") << "' shader." << std::endl;
        std::cerr << message.data() << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

// compile and link shader
static int create_shader(const std::string &vertex_shader, const std::string &fragment_shader)
{
    GLuint program = glCreateProgram();
    GLuint vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

// key press call back
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        std::cout << "Space key pressed" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    GLFWwindow *window{};

    // Initialize GLFW3 library
    if (!glfwInit())
    {
        std::cerr << "Unable to initialize GLFW library";
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

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

    // clang-format off
    // float position[]{
    //     -0.5f, -0.5f,
    //      0.5f, -0.5f,
    //      0.5f,  0.5f,

    //      0.5f,  0.5f,
    //     -0.5f,  0.5f,
    //     -0.5f, -0.5f, 
    // };

    float position[] {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    // index buffer
    GLuint indices[] {
        0, 1, 2,  // first triangle
        2, 3, 0   // second triangle
    };

    // clang-format on

    // define a vertex buffer
    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    GLuint index_buffer_obj;
    glGenBuffers(1, &index_buffer_obj);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_obj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glfwSetKeyCallback(window, key_callback);

    auto source = parse_shaders("basic.shader");

    GLuint shader = create_shader(source.vertexSrc, source.fragmentSrc);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(255, 0, 255, 100);

        // Legacy opengl
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5F, -0.5F);
        // glVertex2f(0.0F, 0.5F);
        // glVertex2f(0.5F, -0.5F);
        // glEnd();

        // glDrawArrays(GL_TRIANGLES, 0, 6);
        gl_clear_error();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        ASSERT(gl_log_call());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
}
