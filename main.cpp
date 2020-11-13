#include <iostream>
#include "utilities.cpp"
#include "PrefixTree.h"
#include "TSTrie.h"
#include "radixtree.hh"

using namespace std;

int main () {
  
	findFiles("Documents/","pdf");
	insertRecords();
//    std::cout << "PREFIX" << std::endl;
//	PrefixTree prefixTree;
//	prefixTree.addFiles();
//	// prefixTree.find("CMakeCache");
//	prefixTree.find("Informe");
//    std::cout << "\nTERNARY" << std::endl;
//	TSTrie tsTrie;
//	tsTrie.addFiles();
//	// tsTrie.find("CMakeCache");
//	tsTrie.find("Informe");
//    std::cout << "\nRADIX" << std::endl;
	RadixTree radixTree("data.db");
	radixTree.addFiles();
	// radixTree.find("CMakeCache");
    radixTree.find("Inf", true);

	return 0;
}