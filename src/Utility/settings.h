#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

namespace Utility {
    struct AppSettings {
        std::string inFilename = "";
        std::string outFilename = "";
        bool verbose = false;
        bool force = false;
    };
}

#endif