#include <iostream>
#include "utilities.cpp"
#include "PrefixTree.h"

using namespace std;

int main () {
  
	//system("find \"$HOME/Documents/Laptop\" -type f -name \"*.pdf\" > files.txt");

	findFiles("Documents/Laptop/UTEC","txt");
	insertRecords();

	PrefixTree prefixTree;
	prefixTree.addFiles();
	prefixTree.find("asdfghjkl");

	return 0;
}