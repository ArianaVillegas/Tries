#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Record.h"

class PrefixTree{
private:

	// 26 letras may, 26 min, 4 caracteres especiales
	struct Node{
		char value;
		unordered_map<char,Node*> children;
		vector<int> word_pos;
	};	

	Node* init;

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
		int size = paths.size();
		for(int i=0; i<size-1; i++){
			for(int j=i+1; j<size; j++){
				if(cmpFiles(paths[i], paths[j])){
					cout << i << " and " << j << " are EQUAL.\n";
				}
			}
		}
	}

	void find(string name, Node* init){
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

		ifstream infile("data.db");
		Record r;
		vector<string> paths;
		int idx = 0;
		for(int pos:init->word_pos){
			infile.seekg(pos);
			infile.read((char*)&r, sizeof(Record));
			paths.push_back(r.name);
			cout << idx << ") " << r.name << '\n';
			idx++;
		}

		findEqual(paths);
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

	void find(string name){
		find(name, init);
	}

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
	
};