#ifndef RADIXTREE_HH
#define RADIXTREE_HH

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include "radixnode.hh"
#include "Record.h"

class RadixTree {
    private:
    long _memsize = 0;
    clock_t tStart, tEnd;
    std::string datafile;
    RadixNode* root = 0;
    
    void find(std::string str, RadixNode* cur, int i = 0, bool partial = false) {
        if(str == "") {
            if(partial) return dfs(cur);
            if(cur->content.size() == i && cur->finalNode) return print_cur(cur);
        }
        if(cur->content == "" && cur->children[str[0]])
            return find(str, cur->children[str[0]], i, partial);
        if(str[0] == cur->content[i])
            return find(str.substr(1), cur, i + 1, partial);
        if(!cur->children[str[0]])
            std::cout << "No existe el archivo" << std::endl;
        else
            find(str, cur->children[str[0]], 0, partial);
    }

    void print_cur(RadixNode* cur) {
        std::ifstream file(this->datafile, std::ios::binary);
        int idx;
        std::vector<std::string> paths;
        for(auto dir : cur->dirs) {
            file.seekg(dir);
            Record r{};
            file.read((char*)&r, sizeof(r));
            paths.push_back(r.name);
            std::cout << ++idx << ") " << r.name << std::endl;
        }
        findEqual(paths);
    }

    void dfs(RadixNode* cur) {
        if(!cur) return;
        _memsize += cur->memsize();
        if(cur->finalNode) print_cur(cur);
        for(auto [ c, child ] : cur->children)
            dfs(child);
    }

    long memsize() {
        _memsize = 0;
        dfs(root);
        return _memsize + sizeof(long) + sizeof(std::string) + datafile.size() + sizeof(root) + root->memsize();
    }

    public:
    RadixTree(const char *datafile): datafile{datafile} {
        root = new RadixNode{};
    }

    void insert(std::string word, unsigned long dir, RadixNode* cur = 0) {
        if(word == "") {
            if(!cur || cur == root) return;
            cur->finalNode = true;
            cur->dirs.push_back(dir);
            return;
        }
        if(!cur) cur = root;
        if(cur != root) {
            int minlength = std::min(word.size(), cur->content.size());
            int i = 0;
            for(; i < minlength && word[i] == cur->content[i]; ++i) {}
            if(i == word.size()) {
                if(i == cur->content.size()) {
                    cur->dirs.push_back(dir);
                    cur->finalNode = true;
                    return;
                }
                cur->split(i, dir);
                return;
            }
            if(i == 0)
                return cur->parent->add_child(new RadixNode(word, dir));
            if(cur->children[word[i]])
                return insert(word.substr(i), dir, cur->children[word[i]]);
            if(i == cur->content.size()) {
                cur->add_child(new RadixNode(word.substr(i), dir));
                return;
            }
            RadixNode* node = cur->split(i);
            node->add_child(new RadixNode(word.substr(i), dir));
            return;
        }
        if(cur->children[word[0]])
            return insert(word, dir, cur->children[word[0]]);
        return cur->add_child(new RadixNode(word, dir));
    }

    void find(std::string str, bool partial = false) {
        find(str, root, 0, partial);
    }

    void addFiles(){
        std::ifstream infile("data.db");
        Record r;
        int pos = 0;
        while (infile.read((char*)&r, sizeof(Record))){
            std::string name = r.name;
            name = std::string(name.rbegin(),name.rend());
            name.erase(0,name.find('.')+1);
            name.erase(name.find('/'),name.size());
            name = std::string(name.rbegin(),name.rend());
            insert(name, pos, root);
            pos = infile.tellg();
        }
    }

    void startMeasures() {
        tStart = clock();
    }

    std::pair<double, long> endMeasures() {
        tEnd = clock();
        auto timeTaken = double(tEnd - tStart)/CLOCKS_PER_SEC;
        auto s = memsize();
        std::cout << "Time taken: " << timeTaken << " s , Total size: " << s << " B" << std::endl;
        return {timeTaken, s};
    }

    void findEqual(std::vector<std::string> paths){
        bool f;
        int size = paths.size();
        std::map<int,std::vector<int>> files;
        for(int i=0; i<size; i++){
            f = 0;
            for(auto pp:files){
                if(cmpFiles(paths[i], paths[pp.first])){
                    files[pp.first].push_back(i);
                    f = 1;
                    break;
                }
            }
            if(!f) files[i].push_back(i);
        }
        for(auto pp:files){
            if(pp.second.size() == 1)
                continue;
            for(int idx:pp.second){
                cout << idx << ", ";
            }
            cout << " are EQUAL.\n";
        }
    }
};


#endif