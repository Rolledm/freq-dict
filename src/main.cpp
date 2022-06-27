#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include "./Utility/settings.h"
#include "./Utility/logger.h"
#include "./Solution/wordparser.h"

enum class ArgsRC {
    OK,
    NEED_FORCE,
    NEED_HELP,
    TOO_MUCH
};

ArgsRC ParseArgs(int argc, char** argv, Utility::AppSettings& settings) {
    int filledFilesCount = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i] == "-f") {
            settings.force = true;
        } else if (argv[i] == "-v") {
            settings.verbose = true;
        } else if (argv[i] == "-h") {
            return ArgsRC::NEED_HELP;
        } else if (filledFilesCount == 0) {
            settings.inFilename = argv[i];
        } else if (filledFilesCount == 1) {
            settings.outFilename = argv[i];
        } else {
            return ArgsRC::TOO_MUCH;
        }
    }
    return ArgsRC::OK;
}


int main(int argc, char** argv) {
    Utility::CLogger::GetInstance().ChangeLogStrategy(std::make_shared<Utility::CSilentLogStrategy>());
    Utility::CLogger::GetInstance().Log(Utility::etSeverity::INFO, "uiwehguiehw");

    std::ifstream in("huge.txt");
    std::ofstream out("out.txt");

    Solution::CParserForest forest(in, out);
    forest.SolveText();

    return 0;
}