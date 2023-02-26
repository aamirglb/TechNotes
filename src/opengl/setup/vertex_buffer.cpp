#include <GL/glew.h> // should be included before glfw3.h
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

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

    float position[6]{
        -0.5f,
        -0.5f,
        0.0f,
        0.5f,
        0.5f,
        -0.5f,
    };

    // define a vertex buffer
    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    glfwSetKeyCallback(window, key_callback);

    std::string vertex_shader =
        "#version 330 core\n"
        "layout(location = 0) in vec4 pos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = pos;\n"
        "}\n";

    std::string fragment_shader =
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "void main()\n"
        "{\n"
        "    color = vec4(1.0, 0.0, 0.0, 1);\n"
        "}\n";

    GLuint shader = create_shader(vertex_shader, fragment_shader);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 0, 255, 100);

        // Legacy opengl
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5F, -0.5F);
        // glVertex2f(0.0F, 0.5F);
        // glVertex2f(0.5F, -0.5F);
        // glEnd();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
}
