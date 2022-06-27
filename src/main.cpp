#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>

class CParserForest {

};

struct CTreeNode {
    std::map<char, CTreeNode*> next;
    int count = 0;
};


std::vector<std::pair<int, std::string>> dict;

void PrepareDict(std::string str, CTreeNode* node) {
    if (node->count) {
        dict.emplace_back(node->count, str);
    }

    for (auto iter : node->next) {
        PrepareDict(str + iter.first, iter.second);
    }
}



int main(int argc, char** argv) {

    //parse args adequate
    std::string in = "huge.txt";
    std::string out = "out.txt"; //use

    std::cout << "Trying to open file." << std::endl;

    std::ifstream srcFile(in); //check file
    
    std::cout << "File opened successfully." << std::endl;

    char c;
    const int offset = 'a' - 'A';

    CTreeNode* root = new CTreeNode();
    CTreeNode* node = root;

    std::cout << "Parsing file..." << std::endl;

    while (srcFile.get(c)) {
        //normalize and check
        if (c >= 'A' && c <= 'Z') {
            c += offset;
        }
        if (c >= 'a' && c <= 'z') {
            if(node->next.find(c) == node->next.end()) {
                node->next[c] = new CTreeNode();
            }
            node = node->next[c];
        } else if (node != root) {
            node->count++;
            node = root;
        }
    }

    std::cout << "File parsed. Preparing output..." << std::endl;

    PrepareDict("", root);

    std::cout << "Done. Sorting..." << std::endl;

    std::sort(dict.begin(), dict.end(), [](const std::pair<int, std::string>& l, const std::pair<int, std::string>& r) {
        if (l.first != r.first) {
            return l.first > r.first;
        }

        return l.second.compare(r.second) > 0;
    });

    std::cout << "Done. Dumping to file..." << std::endl;

    std::ofstream outFile(out);

    for (const auto& iter : dict) {
        outFile << iter.first << " " << iter.second << std::endl;
    }

    std::cout << "Done." << std::endl;

    // close file
    // free

    return 0;
}