// Reads the configuration file and saves the information

#include <string>

struct pictogramsettings
{
        std::string device = "Master";
        float zerosize = 0.6f;
        float maxsize = 0.7f;
        float zerobrightness = 0.625f;
        float maxbrightness = 0.625f;
        float movex = 0.0f;
        float movey = 0.25f;

        void operator= (const pictogramsettings& other)
        {
                device = other.device;
                zerosize = other.zerosize;
                maxsize = other.maxsize;
                zerobrightness = other.zerobrightness;
                maxbrightness = other.maxbrightness;
                movex = other.movex;
                movey = other.movey;
        }
};

struct barsettings
{
        float brightness = 0.7f;

        void operator= (const barsettings& other)
        {
                brightness = other.brightness;
        }
};

// Executes a given command and returns the output from stdout
std::string exec(const char* cmd);

// Write the settings read from the file in the corresponding struct
void readsettings(const char* filepath);

pictogramsettings getPictoSettings(int mode);

barsettings getBarSettings();

// Returns the volume of the audiodevice specified in config.conf
float getVolume();

// Returns the current brightness
float getLight();