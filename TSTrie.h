#include <iostream>
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
        unsigned long position = -1;

        void show(int pos) {
            if (isTerminal && !middle) {
                cout << " @" << endl;
            } else {
                if (isTerminal) cout << "@";
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

    void insert(string name, Node* node, unsigned long position) {
        int size = (int) name.size();
        for (int i = 0; i < size; i++) {
            if (node->isTerminal && !node->middle) {
                    node->value = name[i];
                    node->isTerminal = false;
                    node->position = -1;
                    Node* terminal = new Node();
                    terminal->position = position;
                    node->middle = terminal;
                    node = node->middle;
            } else if (node->value < name[i]) {
                if (!node->right) {
                    Node* newNode = new Node();
                    newNode->value = name[i];
                    newNode->isTerminal = false;
                    node->right = newNode;
                    Node* terminal = new Node();
                    terminal->position = position;
                    newNode->middle = terminal;
                    node = newNode->middle;
                } else {
                    node = node->right;
                    i--;
                }
                
            } else if (node->value > name[i]) {
                if (!node->left) {
                    Node* newNode = new Node();
                    newNode->value = name[i];
                    newNode->isTerminal = false;
                    node->left = newNode;
                    Node* terminal = new Node();
                    terminal->position = position;
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
            node->position = position;
            }
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
        if (!node->isTerminal) cout << "File not found\n";
		else {
            fstream infile("data.db");
            Record r;
            infile.seekg(node->position);
            infile.read((char*)&r, sizeof(Record));
            cout << node->position << ") " << r.name << '\n';           
        }
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

    void find(string name) {
        find(name, root);
    } 

    void show() {
        root->show(0);
    }

    ~TSTrie() {

    };
};
