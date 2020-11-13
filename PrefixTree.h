#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "Record.h"

class PrefixTree{
private:

	// 26 letras may, 26 min, 4 caracteres especiales
	struct Node{
		char value;
		map<char,Node*> children;
		vector<int> word_pos;

		long memsize() {
        	return sizeof(char) +
                sizeof(std::vector<int>) + (sizeof(int) * word_pos.size()) +
                sizeof(std::map<char, Node*>) + children.size() * 
                (sizeof(char) + sizeof(Node*));
    	}
	};	

	Node* init;

	// Exection time and disk access
    clock_t tStart, tEnd;
    double timeTaken;
    long totalSize;

	void insert(string name, int pos, Node* init){
		int size = name.size();
		for(int i=0; i<size; i++){
			auto itr = init->children.find(name[i]);
			if(itr != init->children.end()){
				init = (*itr).second;
			} else {
				for(;i<size;i++){
					Node* node = new Node();
					node->value = name[i];
					init->children[name[i]] = node;
					init = node;
				}
			}
			if(i >= size-1){
				init->word_pos.push_back(pos);
			}
		}
	};

	void findEqual(vector<string> paths){
		bool f;
		int size = paths.size();
		map<int,vector<int>> files;
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

	void find(string name, Node* init, bool partial = false){
		int size = name.size();
		for(int i=0; i<size; i++){
			auto itr = init->children.find(name[i]);
			if(itr != init->children.end()){
				init = (*itr).second;
			} else {
				cout << "File not found\n";
				return;
			}
		}

		long idx = 0;
		vector<string> paths;
		if(partial){
			dfs(init, idx, paths);
		} else {
			ifstream infile("data.db");
			Record r;
			for(int pos:init->word_pos){
				infile.seekg(pos);
				infile.read((char*)&r, sizeof(Record));
				paths.push_back(r.name);
				cout << idx << ") " << r.name << '\n';
				idx++;
			}
		}

		findEqual(paths);
	}

	void dfs(Node* cur, long &idx, vector<string> &paths) {
        if(!cur) return;
        if(cur->children.empty()){
        	print_cur(cur, idx, paths);
        } 
        for(auto [ c, child ] : cur->children)
            dfs(child, idx, paths);
    }

    void dfs_size(Node* cur) {
        if(!cur) return;
        totalSize += cur->memsize();
        for(auto [ c, child ] : cur->children)
            dfs_size(child);
    }

    long memsize() {
        totalSize = 0;
        dfs_size(init);
        return totalSize + sizeof(long) + sizeof(init) + init->memsize();
    }

    void print_cur(Node* cur, long &idx, vector<string> &paths) {
        std::ifstream file("data.db", std::ios::binary);
        for(auto dir : cur->word_pos) {
            file.seekg(dir);
            Record r{};
            file.read((char*)&r, sizeof(r));
            paths.push_back(r.name);
            cout << idx++ << ") " << r.name << std::endl;
        }
    }

public:

	PrefixTree(){
		init = new Node();
		init->value = 0;
	};

	~PrefixTree(){};

	void insert(string name, int pos){
		insert(name, pos, init);
	};

	void find(string name, bool partial = false){
		find(name, init, partial);
	};

	void addFiles(){
		ifstream infile("data.db");
		Record r;
		int pos = 0;
		while (infile.read((char*)&r, sizeof(Record))){
			string name = r.name;
			name = string(name.rbegin(),name.rend());
			name.erase(0,name.find('.')+1);
			name.erase(name.find('/'),name.size());
			name = string(name.rbegin(),name.rend());
		    insert(name, pos);
			pos = infile.tellg();
		}
	};

	void startMeasures() {
        tStart = clock();
        totalSize = 0;
    };

    pair<double, long> endMeasures() {
        tEnd = clock();
        timeTaken = double(tEnd - tStart)/CLOCKS_PER_SEC; 
        totalSize = memsize();
        cout << "Time taken: " << timeTaken << " s , Total size: " << totalSize << " B" << endl;
        return {timeTaken, totalSize};
    };

    void findFiles(string filename, bool partial = false){
        ifstream infile(filename);
        string query;
        while(infile >> query) {
            find(query, partial);
        }
        infile.close();
    };
};