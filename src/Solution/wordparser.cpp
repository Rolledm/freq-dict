#include "./wordparser.h"
#include "../Utility/logger.h"
#include <algorithm>

#include <iostream>

namespace Solution {

    void CParserForest::SolveText() {
        ParseFile();
        _LOGGER.Log(Utility::etSeverity::INFO, "File parsed. Preparing output...");
        PrepareDict("", m_root);
        _LOGGER.Log(Utility::etSeverity::INFO, "Done. Sorting...");
        std::sort(m_dict.begin(), m_dict.end(), [](const std::pair<int, std::string>& l, const std::pair<int, std::string>& r) {
            if (l.first != r.first) {
                return l.first > r.first;
            }
            return l.second.compare(r.second) < 0;
        });
        SaveToFile();
        _LOGGER.Log(Utility::etSeverity::INFO, "Freeing memory...");
        FreeData(m_root);
        m_inFile.close();
        m_outFile.close();
        _LOGGER.Log(Utility::etSeverity::INFO, "Finished!");
    }

    void CParserForest::ParseFile() {
        _LOGGER.Log(Utility::etSeverity::INFO, "Parsing file...");
        char c;
        const int offset = 'a' - 'A';
        CTreeNode* node = m_root;

        std::string str;
        while(std::getline(m_inFile, str)) {
            for (char& c : str) {
                // normalize
                if (c >= 'A' && c <= 'Z') {
                    c += offset;
                }
                if (c >= 'a' && c <= 'z') { //< add letter to word in tree
                    c -= 'a';
                    if(!node->next[c]) {
                        node->next[c] = new CTreeNode();
                    }
                    node = node->next[c];
                } else if (node != m_root) { //< parse end of word
                    node->count++;
                    node = m_root;
                } //< ignore trash
            }
        }
    }

    void CParserForest::PrepareDict(std::string str, CTreeNode* node) {
        if (node->count) { //< found complete word
            m_dict.emplace_back(node->count, str);
        }

        for (int i = 0; i < MAX_ARR_VAL; i++) {
            if (node->next[i]) {
                PrepareDict(str + char(i + 'a'), node->next[i]);
            }
        }
    }

    void CParserForest::SaveToFile() {
        _LOGGER.Log(Utility::etSeverity::INFO, "Done. Dumping to file...");
        for (const auto& iter : m_dict) {
            m_outFile << iter.first << " " << iter.second << std::endl;
        }
    }

    void CParserForest::FreeData(CTreeNode* node) {
        for (int i = 0; i < MAX_ARR_VAL; i++) {
            if (node->next[i]) {
                FreeData(node->next[i]);
            }
        }
        delete node;
    }

}