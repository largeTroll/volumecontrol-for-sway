#include "initilizer.h"

#include <string>
#include <fstream>
#include <sysexits.h>

#include "errorhandling.h"
#include "pos.h"


GLFWwindow* startGLFW(uint32_t winsizex, uint32_t winsizey, const char* title)
{
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glfw window creation
        GLFWwindow* window = glfwCreateWindow(winsizey, winsizex, title, NULL, NULL);
        if (window == NULL) {
                glfwTerminate();
                return nullptr;
        }

        glfwSwapInterval(0);
        glfwMakeContextCurrent(window);

        // Unfortunately, they have no effect on wayland (on sway, configure with the
        // for_window [title="Your title"] floating enable command in the config file)
        // glfwSetWindowPos(window, posx, posy);
        // glfwSetWindowAttrib(window, GLFW_FLOATING, GLFW_TRUE);
        // glfwSetWindowAttrib(window, GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

        // Initiate GLEW
        if (glewInit() != GLEW_OK) {
                std::cout << "Something went terribly wrong! Stopping process..." << std::endl;
                exit(-1);
        }

        std::cout << glGetString(GL_VERSION) << std::endl;

        return window;
}

// Build a vertexbuffer from a 3 floats
uint32_t getVertexBuffer3f(float* data, int count)
{
        // Generate and bind Buffer
        uint32_t buffer;
        GLCall(glGenBuffers(1, &buffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));

        // Fill it with data
        GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));

        // Specify the layout of the buffer
        GLCall(glVertexAttribPointer(0,                 // Starting point for the shader
                3,                 // number of vertices
                GL_FLOAT,          // vertex type
                GL_FALSE,          // normalized
                3 * sizeof(float), // size per next data point
                0));               // starting point in the array

        // Enable the layout
        GLCall(glEnableVertexAttribArray(0));

        // Return the buffer
        return buffer;
}

// Build a vb from 2 floats
uint32_t getVertexBuffer2f(float* data, int count)
{
        // Generate and bind Buffer
        uint32_t buffer;
        GLCall(glGenBuffers(1, &buffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));

        // Fill it with data
        GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));

        // Specify the layout of the buffer
        GLCall(glVertexAttribPointer(0, // Starting point for the shader
                2,                      // number of vertices
                GL_FLOAT,               // vertex type
                GL_FALSE,               // normalized
                2 * sizeof(float),      // size per next data point
                0));                    // starting point in the array

        // Enable the layout
        GLCall(glEnableVertexAttribArray(0));

        // Return the buffer
        return buffer;
}

// Build a vb from 2 positions and 2 tex coords
uint32_t getVertexBuffer2f2t(float* data, int count)
{
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        // Generate and bind Buffer
        uint32_t buffer;
        GLCall(glGenBuffers(1, &buffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));

        // Fill it with data
        GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));

        // Specify the layout of the buffer
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, // Starting point for the shader
                2,                      // number of vertices
                GL_FLOAT,               // vertex type
                GL_FALSE,               // normalized
                4 * sizeof(float),      // size per next data point
                0));                    // starting point in the array in bytes

        // Enable the layout

        GLCall(glEnableVertexAttribArray(1));
        GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(8)));

        // Return the buffer
        return buffer;
}

// Make the indexbufferobject
uint32_t getIndexBuffer(uint32_t* data, int count)
{
        // Generate and bind the index buffer
        uint32_t indexbuffer;
        GLCall(glGenBuffers(1, &indexbuffer));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer));

        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));

        return indexbuffer;
}

// Compile the code in the file as a given shader and return the shaderid
uint32_t compileShader(const char* filename, uint32_t shadertype)
{
        // If there is no shaderfile specified
        if (*filename == '\0')
                return 0;

        // Opens a file for reading
        std::ifstream file(filename);

        std::string line, shadercode;

        // Reads every line in the file and appends it to the shadercode
        while (getline(file, line)) {
                shadercode += line;
                shadercode += '\n';
        }

        // Erzeugt eine angegebenen Shader
        unsigned int id = glCreateShader(shadertype);

        // Das Shaderprogramm
        const char* src = shadercode.c_str();

        // glShaderSource(Welcher Shader, Anzahl an Strings, Shaderprogramm, Laenge[nullptr wenn nullterminiert])
        GLCall(glShaderSource(id, 1, &src, nullptr));

        // Kompiliert den angegebenen Shader
        GLCall(glCompileShader(id));

        // Ueberpruefen, ob alles geklappt hat, ansonsten Fehlermeldung ausgeben
        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE) {
                int length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                char* message = (char*)alloca(length * sizeof(char));
                glGetShaderInfoLog(id, length, &length, message);
                std::cout << "Fehler beim Kompilieren des " << (shadertype == GL_VERTEX_SHADER ? "Vertex" : shadertype == GL_FRAGMENT_SHADER ? "Fragment"
                        : "Geometry")
                        << "shaders!" << std::endl;
                std::cout << message << std::endl;

                // Loescht den Shader
                GLCall(glDeleteShader(id));
                return 0;
        }
        file.close();

        // Gibt die ID des fertigen Shaders aus.
        return id;
}

// Compiles and links the three shaders. If you don't have one, pass "\0" as file
uint32_t getProgram(const char* vertfile, const char* geomfile, const char* fragfile)
{
        uint32_t program = glCreateProgram();

        // Compile all the shaderfiles
        uint32_t vertshader = compileShader(vertfile, GL_VERTEX_SHADER);
        uint32_t fragshader = compileShader(fragfile, GL_FRAGMENT_SHADER);
        uint32_t geomshader = compileShader(geomfile, GL_GEOMETRY_SHADER);

        // run all the steps for all shaders
        if (vertshader != 0) {
                GLCall(glAttachShader(program, vertshader));
                GLCall(glLinkProgram(program));
                GLCall(glValidateProgram(program));
                GLCall(glDeleteShader(vertshader));
        }
        if (geomshader != 0) {
                GLCall(glAttachShader(program, geomshader));
                GLCall(glLinkProgram(program));
                GLCall(glValidateProgram(program));
                GLCall(glDeleteShader(geomshader));
        }
        if (fragshader != 0) {
                GLCall(glAttachShader(program, fragshader));
                GLCall(glLinkProgram(program));
                GLCall(glValidateProgram(program));
                GLCall(glDeleteShader(fragshader));
        }
        // Return the finished program
        return program;
}

// Loads the positions and indices from pos.h. Needs the mode and a reference to a
// Vertex Array Object and a Index Buffer Object and the size of the Index Buffer for the
// draw-call
void loadVertices(uint8_t num, uint32_t& vao, uint32_t& ibo, uint32_t& size)
{
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        switch (num) {
        case 1:
        {
                getVertexBuffer2f(audioposition, 12);
                ibo = getIndexBuffer(audioindex, 12);

                size = 12;

                GLCall(glBindVertexArray(0));
                break;
        }
        case 2:
        {
                getVertexBuffer2f(lightposition, 56);
                ibo = getIndexBuffer(lightindex, 54);

                size = 54;

                GLCall(glBindVertexArray(0));
                break;
        }
        case 3:
        {
                getVertexBuffer2f2t(barposition, 16);
                ibo = getIndexBuffer(barindex, 6);

                size = 6;

                GLCall(glBindVertexArray(0));
                break;
        }
        default: // Can't happen, and if it does, there is a big messup
        {
                break;
        }
        }
}
