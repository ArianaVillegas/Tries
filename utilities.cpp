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
	ifstream infile_a(file_a,std::ifstream::ate | std::ifstream::binary);
	ifstream infile_b(file_b,std::ifstream::ate | std::ifstream::binary);
	int size_a = infile_a.tellg(); 
	int size_b = infile_b.tellg(); 
	if(size_a != size_b) return 0;

	string command = "diff -w \"" + file_a + "\" \"" + file_b + "\" > cmp.txt";
	system(command.c_str());
	ifstream infile("cmp.txt",std::ifstream::ate | std::ifstream::binary);
	int size = infile.tellg(); 
	system("rm cmp.txt");

	return (size)?0:1;
}

#endif