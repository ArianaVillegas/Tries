#include <iostream>
#include "utilities.cpp"
#include "PrefixTree.h"
#include "TSTrie.h"
#include "radixtree.hh"

using namespace std;

void tester() {
	insertRecords();
	std::cout << "====== INSERTION ======" << std::endl;
	std::cout << "PREFIX" << std::endl;
	PrefixTree prefixTree;
	prefixTree.startMeasures();
	prefixTree.addFiles();
	prefixTree.endMeasures();

	std::cout << "\nTERNARY" << std::endl;
	TSTrie tsTrie;
	tsTrie.startMeasures();
	tsTrie.addFiles();
	tsTrie.endMeasures();
	
	std::cout << "\nRADIX" << std::endl;
	RadixTree radixTree("data.db");
	radixTree.startMeasures();
	radixTree.addFiles();
	radixTree.endMeasures();

	std::cout << "====== FIND ======" << std::endl;
	std::cout << "PREFIX" << std::endl;
	prefixTree.startMeasures();
	prefixTree.findFiles("test.txt", true);
	prefixTree.endMeasures();

	std::cout << "\nTERNARY" << std::endl;
	tsTrie.startMeasures();
	tsTrie.findFiles("test.txt", true);
	tsTrie.endMeasures();
	
	std::cout << "\nRADIX" << std::endl;
    radixTree.startMeasures();
    radixTree.findFiles("test.txt", true);
    radixTree.endMeasures();
}

int main () {
	tester();
	return 0;
}