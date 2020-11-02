#include <iostream>
#include "utilities.cpp"
#include "PrefixTree.h"
#include "TSTrie.h"

using namespace std;

int main () {
  
	//system("find \"$HOME/Documents/Laptop\" -type f -name \"*.pdf\" > files.txt");

	findFiles("Documents/","pdf");
	insertRecords();

	PrefixTree prefixTree;
	prefixTree.addFiles();
	prefixTree.find("book");
	prefixTree.find("book2");

	TSTrie tsTrie;
	tsTrie.addFiles();
	tsTrie.find("book");
	tsTrie.find("book2");
	tsTrie.find("booka");


	return 0;
}