#include <iostream>
#include "utilities.cpp"
#include "PrefixTree.h"
#include "TSTrie.h"
#include "radixtree.hh"

using namespace std;

int main () {
  
	//system("find \"$HOME/Documents/Laptop\" -type f -name \"*.pdf\" > files.txt");

	findFiles("Downloads/","pdf");
	insertRecords();
    std::cout << "PREFIX" << std::endl;
	PrefixTree prefixTree;
	prefixTree.addFiles();
	prefixTree.find("ejercicios-5");
	prefixTree.find("Informe");
    std::cout << "\nTERNARY" << std::endl;
	TSTrie tsTrie;
	tsTrie.addFiles();
	tsTrie.find("ejercicios-5");
	tsTrie.find("Informe");
    std::cout << "\nRADIX" << std::endl;
	RadixTree radixTree("data.db");
	radixTree.addFiles();
	radixTree.find("ejercicios-5");
    radixTree.find("Informe");

	return 0;
}