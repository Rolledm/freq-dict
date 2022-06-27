#ifndef WORDPARSER_H
#define WORDPARSER_H

#include <fstream>
#include <vector>
#include <unordered_map>

namespace Solution {

    const int MAX_ARR_VAL = 26;

    struct CTreeNode {
        CTreeNode* next[MAX_ARR_VAL];
        int count = 0;
    };

    class CParserForest {
    public:
        CParserForest(std::ifstream& inFile, std::ofstream& outFile) : m_inFile(inFile), m_outFile(outFile) {};
        void SolveText();
    protected:
        void ParseFile();
        void PrepareDict(std::string str, CTreeNode* node);
        void SaveToFile();
        void FreeData(CTreeNode* node);
    private:
        std::ifstream& m_inFile;
        std::ofstream& m_outFile;
        CTreeNode* m_root = new CTreeNode();
        std::vector<std::pair<int, std::string>> m_dict;
    };
    
}

#endif