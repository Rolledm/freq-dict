#include "./wordparser.h"

#include <algorithm>
#include<iostream> //remove


namespace Solution {

    void CParserForest::SolveText() {
        std::cout << "Parsing file..." << std::endl;
        ParseFile();
        std::cout << "File parsed. Preparing output..." << std::endl;
        PrepareDict("", m_root);
        std::cout << "Done. Sorting..." << std::endl;
        std::sort(m_dict.begin(), m_dict.end(), [](const std::pair<int, std::string>& l, const std::pair<int, std::string>& r) {
            if (l.first != r.first) {
                return l.first > r.first;
            }
            return l.second.compare(r.second) < 0;
        });
        std::cout << "Done. Dumping to file..." << std::endl;
        SaveToFile();
        FreeData(m_root);
    }

    void CParserForest::ParseFile() {
        char c;
        const int offset = 'a' - 'A';
        CTreeNode* node = m_root;

        while (m_inFile.get(c)) {
            // normalize
            if (c >= 'A' && c <= 'Z') {
                c += offset;
            }
            if (c >= 'a' && c <= 'z') { //< add letter to word in tree
                if(node->next.find(c) == node->next.end()) {
                    node->next[c] = new CTreeNode();
                }
                node = node->next[c];
            } else if (node != m_root) { //< parse end of word
                node->count++;
                node = m_root;
            } //< ignore trash
        }
    }

    void CParserForest::PrepareDict(std::string str, CTreeNode* node) {
        if (node->count) { //< found complete word
            m_dict.emplace_back(node->count, str);
        }

        for (auto iter : node->next) {
            PrepareDict(str + iter.first, iter.second);
        }
    }

    void CParserForest::SaveToFile() {
        for (const auto& iter : m_dict) {
            m_outFile << iter.first << " " << iter.second << std::endl;
        }
    }

    void CParserForest::FreeData(CTreeNode* node) {
        for (auto iter: node->next) {
            FreeData(iter.second);
        }
        delete node;
    }

}