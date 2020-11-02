#include <iostream>
#include "utilities.cpp"
#include "PrefixTree.h"
#include "TSTrie.h"

using namespace std;

int main () {
  
	//system("find \"$HOME/Documents/Laptop\" -type f -name \"*.pdf\" > files.txt");

	findFiles("Documents/","txt");
	insertRecords();

	PrefixTree prefixTree;
	prefixTree.addFiles();
	prefixTree.find("CMakeCache");
	prefixTree.find("link");

	TSTrie tsTrie;
	tsTrie.addFiles();
	tsTrie.find("CMakeCache");
	tsTrie.find("link");
	tsTrie.find("linka");


	return 0;
}