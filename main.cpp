#include <iostream>
#include "utilities.h"
// #include "PrefixTree.h"
#include "radixtree.hh"

using namespace std;

int main () {
  
	//system("find \"$HOME/Documents/Laptop\" -type f -name \"*.pdf\" > files.txt");

	findFiles("","txt");
	insertRecords();

	// PrefixTree prefixTree;
	RadixTree radixtree("data.db");
	radixtree.addFiles();
	radixtree.find("pdist-chebyshev-ml-iris");

	return 0;
}