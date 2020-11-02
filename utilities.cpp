#ifndef UTILITIES
#define UTILITIES

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;


void findFiles(string init_path, string ext){
	string command = "find \"$HOME/" + init_path + "\" -type f -name \"*." + ext + "\" > files.txt";
	system(command.c_str());
}

bool cmpFiles(string file_a, string file_b){
	string command = "diff -w \"" + file_a + "\" \"" + file_b + "\" > cmp.txt";
	system(command.c_str());
	ifstream infile("cmp.txt",std::ifstream::ate | std::ifstream::binary);
	int size = infile.tellg(); 
	system("rm cmp.txt");

	return (size)?0:1;
}

#endif