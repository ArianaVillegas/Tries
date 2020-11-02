#include <iostream>
#include "utilities.cpp"
#include "PrefixTree.h"
#include "TSTrie.h"
#include "radixtree.hh"

using namespace std;

int main () {
  
	findFiles("Documents/","txt");
	insertRecords();
    std::cout << "PREFIX" << std::endl;
	PrefixTree prefixTree;
	prefixTree.addFiles();
	prefixTree.find("CMakeCache");
	prefixTree.find("link");
    std::cout << "\nTERNARY" << std::endl;
	TSTrie tsTrie;
	tsTrie.addFiles();
	tsTrie.find("CMakeCache");
	tsTrie.find("link");
    std::cout << "\nRADIX" << std::endl;
	RadixTree radixTree("data.db");
	radixTree.addFiles();
	radixTree.find("CMakeCache");
    radixTree.find("link");

	return 0;
}