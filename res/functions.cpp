// This file contains the main loop for drawing the symbol and bar.

#include "functions.h"

#include "errorhandling.h"
#include "initilizer.h"
#include "readconfig.h"

static pictogramsettings pictset;
static barsettings barset;

void loop(GLFWwindow* window, int mode, float(*function)())
{
        glid picto; // IDs for the pictogram
        glid bar;
        loadVertices(mode, picto.vao, picto.ibo, picto.indexsize);
        loadVertices(MODE::BAR, bar.vao, bar.ibo, bar.indexsize);

        picto.program = getProgram("graphics/picto.vert", "\0", "graphics/picto.frag");
        GLCall(glUseProgram(0));
        bar.program = getProgram("graphics/bar.vert", "\0", "graphics/bar.frag");
        GLCall(glUseProgram(0));

        readsettings("/home/domax/.config/msgbox/config.conf");
        barset = getBarSettings();
        pictset = getPictoSettings(mode);


        float level, lastLevel;

        double endtime = glfwGetTime() + 5.0, time;

        while (!glfwWindowShouldClose(window)) {
                int width, height;
                glfwGetFramebufferSize(window, &width, &height);
                glViewport(0, 0, width, height);

                // Make sure, that the window closes 1.5 sec after the last level-change
                level = function();
                if (level - lastLevel != 0.0f){
                        lastLevel = level;
                        endtime = glfwGetTime() + 2.0;
                }

                time = glfwGetTime();
                if (time > endtime)
                        break;


                GLCall(glClear(GL_COLOR_BUFFER_BIT));


                // Bind all stuff for the pictogram
                GLCall(glBindVertexArray(picto.vao));
                GLCall(glUseProgram(picto.program));
                GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, picto.ibo));
                shadercompicto(picto.program, level);

                // Draw the pictorgram
                GLCall(glDrawElements(GL_TRIANGLES, picto.indexsize, GL_UNSIGNED_INT, nullptr));



                // Bind the bar related stuff
                GLCall(glUseProgram(bar.program));
                GLCall(glBindVertexArray(bar.vao));
                GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bar.ibo));

                shadercombar(bar.program, level);

                // Draw the Bar
                GLCall(glDrawElements(GL_TRIANGLES, bar.indexsize, GL_UNSIGNED_INT, nullptr));



                // Do the Bufferswap
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
}


// Sets the variables for the vertex and fragment shader
void shadercompicto(unsigned int program, float scale)
{
        if (scalelocpicto == 0 && offsetlocpicto == 0 && brightnesslocpicto == 0) {
                scalelocpicto = glGetUniformLocation(program, "u_scale");
                offsetlocpicto = glGetUniformLocation(program, "u_offset");
                brightnesslocpicto = glGetUniformLocation(program, "u_brightness");
        }

        GLCall(glUniform1f(scalelocpicto, pictset.zerosize + (pictset.maxsize - pictset.zerosize) * (scale / 100.0f)));
        GLCall(glUniform2f(offsetlocpicto, pictset.movex, pictset.movey));
        GLCall(glUniform1f(brightnesslocpicto, pictset.zerobrightness + (pictset.maxbrightness - pictset.zerobrightness) * (scale / 100.0f)));
}

void shadercombar(unsigned int program, float volume)
{
        if (volumelocbar == 0 && brightnesslocbar == 0) {
                volumelocbar = glGetUniformLocation(program, "u_volume");
                brightnesslocbar = glGetUniformLocation(program, "u_brightness");
        }

        GLCall(glUniform1f(volumelocbar, volume / 100.0f));
        GLCall(glUniform1f(brightnesslocbar, barset.brightness));
}