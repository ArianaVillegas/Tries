#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

struct Record{
	char name[3000];
};

void insertRecords(){
	std::ifstream infile("files.txt");
	system("rm data.db");
	std::ofstream outfile("data.db", std::ios::binary | std::ios::app);
	std::string line;
	while (std::getline(infile, line)){
		Record r;
		strcpy(r.name, line.c_str());
	    outfile.write((char*)&r, sizeof(Record));
	}
	infile.close();
	outfile.close();
	//system("rm files.txt");
};