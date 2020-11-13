#include <iostream>
#include <algorithm>
#include "Record.h"
using namespace std;
class TSTrie
{
    struct Node
    {
        char value;
        Node* left = nullptr; 
        Node* right = nullptr;
        Node* middle = nullptr;
        bool isTerminal = true;
        vector<unsigned long> paths_pos;
        void show(int pos) {
            if (isTerminal && !middle) {
                cout << " @" << paths_pos.size() << endl;
            } else {
                if (isTerminal) cout << "@" << paths_pos.size();
                if (right) {
                    right->show(pos + 1);
                }
                   
                for (int i = 0; i < pos; i++)
                    cout << " ";
      
                cout << value;

                if (middle) {
                    middle->show(1);
                }
                if (left) {
                    left->show(pos + 1);
                }
            }
        }
    };
    
    Node* root; //main node
    // Exection time and disk access
    clock_t tStart, tEnd;
    double timeTaken;
    long totalSize;

    void insert(string name, Node* node, unsigned long position) {
        int size = (int) name.size();
        totalSize += sizeof(size);
        for (int i = 0; i < size; i++) {
            if (node->isTerminal && !node->middle) {
                    node->value = name[i];
                    if (node->paths_pos.empty())
                        node->isTerminal = false;
                    Node* terminal = new Node();
                    totalSize += sizeof(terminal);
                    node->middle = terminal;
                    node = node->middle;
            } else if (node->value < name[i]) {
                if (!node->right) {
                    Node* newNode = new Node();
                    totalSize += sizeof(newNode);
                    newNode->value = name[i];
                    newNode->isTerminal = false;
                    node->right = newNode;
                    Node* terminal = new Node();
                    totalSize += sizeof(terminal);
                    newNode->middle = terminal;
                    node = newNode->middle;
                } else {
                    node = node->right;
                    i--;
                }
                
            } else if (node->value > name[i]) {
                if (!node->left) {
                    Node* newNode = new Node();
                    totalSize += sizeof(newNode);
                    newNode->value = name[i];
                    newNode->isTerminal = false;
                    node->left = newNode;
                    Node* terminal = new Node();
                    totalSize += sizeof(terminal);
                    newNode->middle = terminal;
                    node = newNode->middle;
                } else {
                    node = node->left;
                    i--;
                }
            } else node = node->middle;
        }
        if (!node->isTerminal) {
            node->isTerminal = true;
           
        } 
         node->paths_pos.push_back(position);
         totalSize += sizeof(position);
        
    }

	void find(string name, Node* node){
		int size = (int) name.size();
		for(int i = 0; i < size; i++) {
            if (!node) {
                cout << "File not  found\n";
                return;
            }
            if (node->value == name[i]) {
                node = node->middle;
            } else if (node->value < name[i]) {
                node = node->right;
                i--;

            } else if (node->value > name[i]) {
                node = node->left;
                i--;
            }
		}
        vector<string> paths;
        if (!node->isTerminal) cout << "File not found\n";
		else {
            fstream infile("data.db");
            int idx = 0;
            for (auto path:node->paths_pos) {
                Record r;
                infile.seekg(path);
                infile.read((char*)&r, sizeof(Record));
                paths.push_back(r.name);
                cout << idx << ") " << r.name << '\n';   
                idx++;
            }
            findEqual(paths);            
        }
	}

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

    void findPartially(string name, Node* node){
		int size = (int) name.size();
		for(int i = 0; i < size; i++) {
            if (node->value == name[i]) {
                node = node->middle;
            } else if (node->value < name[i]) {
                node = node->right;
                i--;

            } else if (node->value > name[i]) {
                node = node->left;
                i--;
            }
		}
        vector<string> paths;
        dfs(node, paths);
        findEqual(paths);
	}

    void dfs(Node* node, vector<string> &paths) {
        if (node->isTerminal) {
            fstream infile("data.db");
            int idx = 0;
            for (auto path:node->paths_pos) {
                Record r;
                infile.seekg(path);
                infile.read((char*)&r, sizeof(Record));
                paths.push_back(r.name);
                cout << idx << ") " << r.name << '\n';   
                idx++;
            }
        } 
        if (node->left) dfs(node->left, paths);
        if (node->middle) dfs(node->middle, paths);
        if (node->right) dfs(node->right, paths);  
        
    }

public:
    TSTrie() {
        root = new Node();
    };

    void insert(string name, unsigned position = -1) {
        insert(name, root, position);
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

    void find(string name, bool partial = false) {
        if (partial) findPartially(name, root);
        else find(name, root);
    }

    void findFiles(string filename, bool partial = false){
        ifstream infile(filename);
        string query;
        while(infile >> query) {
            find(query, partial);
        }
        infile.close();
    }

    void startMeasures() {
        tStart = clock();
        totalSize = sizeof(Node);
    }

    pair<double, long> endMeasures() {
        tEnd = clock();
        timeTaken = double(tEnd - tStart)/CLOCKS_PER_SEC; 
        cout << "Time taken: " << timeTaken << " s , Total size: " << totalSize << " B" << endl;
        return {timeTaken, totalSize};
    }

    void show() {
        root->show(0);
    }

    ~TSTrie() {

    };
};
