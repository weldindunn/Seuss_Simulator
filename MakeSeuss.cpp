
#include "makeSeuss.hpp"
#include "hashMap.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

makeSeuss::makeSeuss(string f1,string f2,bool hash1, bool coll1) {
	cout << "Creating" << endl;
	ht = new hashMap(hash1,coll1);
	newfile = f2;
	fn = f1;

	readFile();
	writeFile();
	cout << "All done!" << endl;
	cout << endl;
}
void makeSeuss::readFile() {
	cout << "Reading" << endl;
	ifstream infile(fn.c_str(),ios::in);     // open file
	string key = "";
	string value="";
	infile >> key;

	infile >> key;
	ht->first = key;

	while (infile >> value) {          // loop getting single characters
		//cout << key <<": " << value << endl;
		ht->addKeyValue(key,value);
		key = value;
		value = "";
	}
	ht->addKeyValue(key,value);
	//cout << endl;
	infile.close();
	cout << "Read" << endl;

	//ht->printMap();
}
void makeSeuss::writeFile() {
	cout << "Writing" << endl;
	ofstream outfile(newfile.c_str(),ios::out);
	float hashfloat = (float)ht->hashcoll/(float)ht->numKeys;
	float collfloat =  (float)ht->collisions/(float)ht->numKeys;
	if (ht->hashfn && ht->collfn) {
		outfile << "Collisions using hash 1: "<< hashfloat << ", and collision handling 1: " << collfloat <<endl;
	}
	else if (ht->hashfn) {
		outfile << "Collisions using hash 1: "<< hashfloat << ", and collision handling 2: " << collfloat<<endl;
	}
	else if (ht->collfn) {
		outfile << "Collisions using hash 2: "<< hashfloat << ", and collision handling 1: " << collfloat<<endl;
	}
	else {
		outfile << "Collisions using hash 2: "<< hashfloat << ", and collision handling 2: " << collfloat<<endl;
	}
	outfile<<endl;
	outfile << ht->first << " ";
	string key = "";
	//cout << ht->map[ht->getIndex(ht->first)] << endl;
	string value = ht->map[ht->getIndex(ht->first)]->getRandValue();
	//cout << ht->first << " " << value << endl;
	int ct = 0;
	int len = 0;
	//cout << key << endl;
	while (ct < 500 && value != "") {
		key = value;
		//cout << key << endl;
		outfile << key << " ";
		if (len == 11) {
			outfile << "\n";
			len = 0;
		}
		else len++;
		//cout << "Before: " << value << endl;
		//cout << ht->getIndex(key) << endl;
		value = ht->map[ht->getIndex(key)]->getRandValue(); //THE CULPRIT!
		//cout << "After: " << value << endl;
		//cout << "(" << ct << ") " << value << endl;
		ct++;
	}
	outfile.close();
	cout << "Written" << endl;
}


