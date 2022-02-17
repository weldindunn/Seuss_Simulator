

#include "hashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;



hashNode::hashNode(string s){
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(){
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(string s, string v){
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}
void hashNode::addValue(string v) {
	// adding a value to the end of the value array associated
	// with a key
	values[currSize] = v; //Assigns the value to the end of the values array
	currSize++; //Increases the current size of the values array
}
void hashNode::dblArray() {
	// when the value array gets full, you need to make a new 
	// array twice the size of the old one (just double, no 
	//going to next prime) and then copy over the old values 
	//to the new values, then de-allocate the old array.  
	//Again, just copying over, no hash function involved
	//here.

	valuesSize *= 2; //Doubles the valuesSize
	string *tmp = new string[valuesSize]; //Creates the new array

	for (int i = 0; i < valuesSize/2; i++) {
		tmp[i] = values[i]; //Transfers over each value
	}

	values = tmp; //Assigns the values array to the new array
}

string hashNode::getRandValue() {
	//Every key has a values array - an array of words that 
	// follow that key in the text document.  You're going to 
	//randomly select one of those words and return it.  That 
	//will be the word that follows your key in your output 
	//function, and it will also be the next key.

	int index = rand()%currSize; //Picks a random number within the array's populated range
	return values[index]; //Returns the value at that index in the values array
}
