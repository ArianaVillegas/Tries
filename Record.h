#ifndef RECORD_HH
#define RECORD_HH

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

struct Record{
	char name[3000];
};

void insertRecords(){
	ifstream infile("files.txt");
	system("rm data.db");
	ofstream outfile("data.db", ios::binary | ios::app);
	string line;
	while (getline(infile, line)){
		Record r;
		strcpy(r.name, line.c_str());
	    outfile.write((char*)&r, sizeof(Record));
	}
	infile.close();
	outfile.close();
	system("rm files.txt");
};

#endif