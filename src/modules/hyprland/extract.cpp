#include "modules/hyprland/extract.hpp"
#include <sstream>

namespace zdhpctl::modules::hyprland {

    std::string extractActiveKeymap(const std::string& devices) {
        std::string line;
        std::string currentKeymap;
        std::istringstream stream(devices);

        while (std::getline(stream, line)) {
            if (line.find("active keymap:") != std::string::npos) {
                currentKeymap = line.substr(line.find(":") + 2);
            }
            else if (line.find("main: yes") != std::string::npos && !currentKeymap.empty()) {
                return currentKeymap;
            }
        }

        return "";
    }

}
