// Used to start GLFW and set up the Vertex and Index Buffer for OpenGL

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Initiates all important things like GLEW or GLFW
GLFWwindow* startGLFW(uint32_t winsizex, uint32_t winsizey, const char* title);

// Constructs a vertex array buffer and returns it. Needs the data and the number of floats in the array
uint32_t getVertexBuffer3f(float *data, int count);
// Same as above, but takes a 2D vector
uint32_t getVertexBuffer2f(float* data, int count);

// Make an index buffer and return it. Needs the data and the number of indices in the array
uint32_t getIndexBuffer(uint32_t *data, int count);

// Compiles a given shader and returns the shaderid
uint32_t compileShader(const char* filename, uint32_t shadertype);

// Takes the shaderfiles as inputs and returns a finished program with all shaders attached to it. If you don't have a shaderfile, use '\0' as filename
uint32_t getProgram(const char *vertfile, const char *geomfile, const char *fragfile);

// Loads the given model
void loadVertices(uint8_t num, uint32_t& vao, uint32_t& ibo, uint32_t& size);