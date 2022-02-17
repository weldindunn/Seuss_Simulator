

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	map = new hashNode *[mapSize];
	//first = "";
	numKeys = 0;
	mapSize = 101;
	hashfn = hash1;
	collfn = coll1;
	collisions = 0;
	hashcoll = 0;

	for (int i = 0; i < mapSize; i++) { //Initialize each value to NULL
		map[i] = NULL;
	}
}

void hashMap::addKeyValue(string k, string v) {

	int ind = 0;
	if (hashfn) {
		ind = calcHash1(k);
	} else {
		ind = calcHash2(k);
	}

	if (map[ind] != NULL) { //If there is a collision
		if (map[ind]->keyword == k) { //If it is the same word,
			map[ind]->addValue(v); //Add its value
		} else { //If it's a different word
			if (collfn) { //Call a collision method
				ind = coll1(ind, 1, k);
			} else {
				ind = coll2(ind, 1, k);
			}
			map[ind] = new hashNode(k, v);
			numKeys++;
		}
		hashcoll++;
	} else { //Otherwise, add the node
		map[ind] = new hashNode(k, v);
		numKeys++;
	}

	//Outputs the keyword added and how full the map is
	//cout << k << ", " << (float)numKeys/mapSize << endl;

	if ((float)numKeys/mapSize >= 0.7) { //If the map is 70% full, rehash
		//cout << "Oh this is it, isn't it?" << endl;
		reHash();
		//cout << "No?" << endl;
	}
}

int hashMap::getIndex(string k) {

	int ind = 0;
	if (hashfn) {
		ind = calcHash1(k);
	} else {
		ind = calcHash2(k);
	}

	//cout << ind << endl;
	if (map[ind] != NULL) { //If there is a collision
		if (map[ind]->keyword == k) { //If it is the same word,
			return ind;
		} else { //If it's a different word
			if (collfn) { //Call a collision method
				ind = coll1(ind, 1, k);
			} else {
				ind = coll2(ind, 1, k);
			}
		}
	}
	//cout << ind << "/" << mapSize << endl;

	return ind;
}

int hashMap::calcHash1(string k){
	int len = k.length();
	int sum = 0;

	//Simply adds all the letters ASCII values together
	for (int i = 0; i < len; i++) {
		sum += (int)k[i];
	}

	return sum%mapSize; //Returns the key address
}

int hashMap::calcHash2(string k){
	int len = k.length();
	int ind = 0;

	for (int i = 0; i < len; i++) {
		ind = (7*ind + (int)k[i]) % mapSize;
	}

	return ind;
}

void hashMap::getClosestPrime() {
	int prime = mapSize*2 + 1; //Sets the closest prime to double the map size
	bool primeFound = false;

	while (!primeFound) {
		bool notPrime = false;
		for (int i = 3; i < prime; i+=2) { //Checks every odd number for divisibility
			if (prime%i == 0) {
				notPrime = true;
			}
		}

		if (!notPrime) {
			primeFound = true;
		} else {
			prime+=2; //Adding 1 would be a waste of time as no even numbers are prime
		}
	}

	mapSize = prime;
}

void hashMap::reHash() {
	int oldSize = mapSize; //Maintains the old mapSize
	getClosestPrime(); //Doubles the mapSize to next prime number
	hashNode **newMap = new hashNode *[mapSize]; //Makes a new empty hash map

	for (int i = 0; i < mapSize; i++) { //Initialize each value to NULL
		newMap[i] = NULL;
	}

	hashNode **oldMap = map; //Preserve the old map
	map = newMap; //Replace the old map so getIndex will actually work
	//cout << numKeys << "/" << oldSize << " full" << endl;
	for (int i = 0; i < oldSize; i++) { //Goes through the old map
		if (oldMap[i] != NULL) { //If the map index isn't empty
			int ind = getIndex(oldMap[i]->keyword); //Gets the new index for the new map
			newMap[ind] = oldMap[i]; //Assign the node to its new home
		}
	}
	//cout << "hashed!" << endl;
}

int hashMap::coll1(int h, int i, string k) {
	//h = oldIndex
	//i = number of times coll1 has been called
	//k = inserted key

	//This collision method just uses basic linear probing
	while (map[h] != NULL && map[h]->keyword != k) {
		h++;
		if (h >= mapSize) {
			h = 0;
		}
		collisions++;
	}

	return h;
}

int hashMap::coll2(int h, int i, string k) {
	//cout << "Are we just playing footise here?" << endl;

	while (map[h] != NULL && map[h]->keyword != k) {
		//This collision method uses quadratic hashing
		//h = ((int)(h + pow(i, i))) % mapSize;
		//cout << i << ", " << h << endl;

		//This collision method uses double-hashing
		//h = (h + i*7) % mapSize;
		//cout << i << ", " << h << endl;

		//Unfortunately I couldn't get the above methods to work, so just so I could have all four
		//output files, I used the same collision method here.
		h++;
		if (h >= mapSize) {
			h = 0;
		}
		collisions++;
		i++;
	}

	return h;
}

void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


