#include <sys/file.h>
#include <errno.h>
#include <sysexits.h>

#include "res/initilizer.h"
#include "res/errorhandling.h"
#include "res/functions.h"
#include "res/readconfig.h"


int main(int argc, char* argv[])
{
        int pid_file = open("/tmp/msgbox.pid", O_CREAT | O_RDWR, 0666);
        int rc = flock(pid_file, LOCK_EX | LOCK_NB);
        if (rc) {
                if (EWOULDBLOCK == errno) {
                        std::cout << "Program already started!" << std::endl;
                        exit(0);
                }
        } else {
                std::cout << "Starting Program..." << std::endl;

                // Setup the window stuff
                GLFWwindow* window = startGLFW(300, 300, "MSG");

                // See, wether the audio or the backlight has to be tracked
                if (*argv[1] == *"audio")
                        loop(window, MODE::AUDIO, getVolume);
                else if (*argv[1] == *"light")
                        loop(window, MODE::LIGHT, getLight);

                glfwDestroyWindow(window);
                glfwTerminate();
        }
}