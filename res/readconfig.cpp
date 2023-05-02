#include "readconfig.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include <fstream>
#include <sys/stat.h>

pictogramsettings aset;
pictogramsettings lset;
barsettings bset;

std::string exec(const char* cmd)
{
        std::array<char, 128> buffer;
        std::string result;
        std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())) {
                if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
                        result += buffer.data();
        }

        return result;
}

// Removes all spaces in the string
void removeSpaces(std::string& line)
{
        int beginnIndex;
        while (line.find(" ") != std::string::npos) {
                beginnIndex = line.find(" ");
                line = line.replace(beginnIndex, 1, "");
        }
        // std::cout << line.substr(beginnIndex) << std::endl;
}

// Removes anything, that is after a '#' symbol, the '#' included
void removeComment(std::string& line)
{
        int firstComment = line.find_first_of("#");
        if (firstComment == 0)
                line = "";
        else {
                if (firstComment != -1)
                        line = line.substr(0, firstComment);
        }
        // std::cout << line << std::endl;
}

// Assigns a setting from the file to the corresponding settingsstruct
void assignallSettings(const std::string& line)
{
        int equal = line.find("=");
        std::string prefix = line.substr(0, equal);
        if (prefix == "audiodevice")
                aset.device = line.substr(equal + 2, line.size() - equal - 3);
        else if (prefix == "audiozerosize")
                aset.zerosize = std::stof(line.substr(equal + 1));
        else if (prefix == "audiomaxsize")
                aset.maxsize = std::stof(line.substr(equal + 1));
        else if (prefix == "audiozerobrightness")
                aset.zerobrightness = std::stof(line.substr(equal + 1));
        else if (prefix == "audiomaxbrightness")
                aset.maxbrightness = std::stof(line.substr(equal + 1));
        else if (prefix == "audiomovex")
                aset.movex = std::stof(line.substr(equal + 1));
        else if (prefix == "audiomovey")
                aset.movey = std::stof(line.substr(equal + 1));
        else if (prefix == "barbrightness")
                bset.brightness = std::stof(line.substr(equal + 1));
        else if (prefix == "lightzerosize")
                lset.zerosize = std::stof(line.substr(equal + 1));
        else if (prefix == "lightmaxsize")
                lset.maxsize = std::stof(line.substr(equal + 1));
        else if (prefix == "lightzerobrightness")
                lset.zerobrightness = std::stof(line.substr(equal + 1));
        else if (prefix == "lightmaxbrightness")
                lset.maxbrightness = std::stof(line.substr(equal + 1));
        else if (prefix == "lightmovex")
                lset.movex = std::stof(line.substr(equal + 1));
        else if (prefix == "lightmovey")
                lset.movey = std::stof(line.substr(equal + 1));
}

// Checks, if a file exists
inline bool fileexists(const char* name)
{
        std::ifstream f(name);
        return f.good();
}

// Reads the settings from the specified file and writes them in the corresponding struct
void readsettings(const char* filepath)
{
        if (fileexists(filepath)) {
                std::cout << "Config file found" << std::endl;
                std::ifstream file(filepath);
                pictogramsettings audset;

                std::string line;
                while (getline(file, line)) {
                        // Empty line
                        if (line[0] == '\0')
                                continue;

                        removeSpaces(line);
                        removeComment(line);
                        // Line only with comment
                        if (line == "")
                                continue;

                        assignallSettings(line);
                }

                file.close();
        }
}

// Return either the audio (mode = 1) or the light settings (mode = 2)
pictogramsettings getPictoSettings(int mode)
{
        std::cout << "Audio config: " << std::endl;
        std::cout << "0% brightness: " << aset.zerobrightness << " 100% brightness: " << aset.maxbrightness << " 0% size: " << aset.zerosize << " 100% size: " << aset.maxsize << " Move x: " << aset.movex << " Move y: " << aset.movey << " Device: " << aset.device << std::endl;

        std::cout << "Light config: " << std::endl;
        std::cout << "0% brightness: " << lset.zerobrightness << " 100% brightness: " << lset.maxbrightness << " 0% size: " << lset.zerosize << " 100% size: " << lset.maxsize << " Move x: " << lset.movex << " Move y: " << lset.movey << std::endl;
        return (mode == 1 ? aset : lset);
}

// Return the barsettings
barsettings getBarSettings()
{
        return bset;
}

// Get the current audio volume and return it
float getVolume()
{
        std::string cmd = "amixer -c 0 sget " + aset.device + " | grep [][]";
        std::string amixeroutput = exec(cmd.c_str());

        if (amixeroutput.find("off") != std::string::npos)
                return 0;
        // std::cout << "Audio off" << std::endl;
        else {
                int audindbeg = amixeroutput.find("[");
                int audindend = amixeroutput.find("%");
                // std::cout << amixeroutput.substr(audindbeg + 1, audindend - audindbeg - 1) << std::endl;
                int volume = std::stoi(amixeroutput.substr(audindbeg + 1, audindend - audindbeg - 1));
                // std::cout << std::stoi(number) << std::endl;
                return (float)volume;
        }
}

// Get the brightness and return it
float getLight()
{
        std::string lightoutput = exec("light");
        float light = std::stof(lightoutput);
        return light;
}