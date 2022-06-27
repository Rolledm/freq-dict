#include <iostream>
#include <fstream>
#include "./Utility/settings.h"
#include "./Utility/logger.h"
#include "./Solution/wordparser.h"
#include <string>
#include <cstring>

enum class ArgsRC {
    OK,
    NEED_HELP,
    TOO_MUCH
};

ArgsRC ParseArgs(int argc, char** argv, Utility::AppSettings& settings) {
    int filledFilesCount = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            settings.force = true;
        } else if (strcmp(argv[i], "-v") == 0) {
            settings.verbose = true;
        } else if (strcmp(argv[i], "-h") == 0) {
            return ArgsRC::NEED_HELP;
        } else if (filledFilesCount == 0) {
            settings.inFilename = argv[i];
            filledFilesCount++;
        } else if (filledFilesCount == 1) {
            settings.outFilename = argv[i];
            filledFilesCount++;
        } else {
            return ArgsRC::TOO_MUCH;
        }
    }
    return ArgsRC::OK;
}

int help() {
    std::cout << "Frequency dictionary" << std::endl;
    std::cout << "Usage: ./freq [OPTIONS] in.txt out.txt" << std::endl;
    std::cout << "-h\n\tShow this message." << std::endl;
    std::cout << "-v\n\tShow progress." << std::endl;
    std::cout << "-f\n\tOverride output file if exists. By default, program will exit." << std::endl;
    return 0;
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    Utility::AppSettings settings;
    _LOGGER.ChangeLogStrategy(std::make_shared<Utility::CSilentLogStrategy>());
    ArgsRC rc = ParseArgs(argc, argv, settings);
    switch (rc)
    {
    case ArgsRC::NEED_HELP:
        return help();
    case ArgsRC::TOO_MUCH:
        _LOGGER.Log(Utility::etSeverity::ERROR, "Too much arguments.");
        return 1;
    default:
        break;
    }

    if (!settings.inFilename.size() || !settings.outFilename.size()) {
        _LOGGER.Log(Utility::etSeverity::ERROR, "One of filenames (or both) not specified.");
        return 1;
    }

    std::ifstream in(settings.inFilename);
    if (!in.is_open()) {
        _LOGGER.Log(Utility::etSeverity::ERROR, "Can't open IN file. Check name and access rights.");
        return 1;
    }

    std::ifstream checkOut(settings.outFilename);
    if (checkOut.is_open() && !settings.force) {
        _LOGGER.Log(Utility::etSeverity::ERROR, "OUT file exists. Change name or enable forced overriding via providing -f argument");
        in.close();
        checkOut.close();
        return 1;
    }

    checkOut.close();

    std::ofstream out(settings.outFilename);
    if (!out.is_open()) {
        _LOGGER.Log(Utility::etSeverity::ERROR, "Can't open OUT file. Check access rights.");
        in.close();
        return 1;
    }

    if (settings.verbose) {
        _LOGGER.ChangeLogStrategy(std::make_shared<Utility::CVerboseLogStrategy>());
    }

    Solution::CParserForest forest(in, out);
    forest.SolveText();

    return 0;
}