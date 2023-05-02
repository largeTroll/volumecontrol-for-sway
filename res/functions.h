#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum MODE {
        AUDIO = 1,
        LIGHT = 2,
        BAR = 3
};

struct glid
{
        unsigned int vao, ibo, indexsize, program;
};


static unsigned int scalelocpicto = 0, offsetlocpicto = 0, brightnesslocpicto = 0;
static unsigned int volumelocbar = 0, brightnesslocbar = 0;

void loop(GLFWwindow* window, int mode, float(*function)());
void shadercompicto(unsigned int program, float scale);
void shadercombar(unsigned int program, float scale);