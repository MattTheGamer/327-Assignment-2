/*
 * functionstocomplete.cpp
 *
 *  Created on: Feb 2, 2018
 *      Author: Matt Passarelli
 */

//============================================================================
//	TODO add necessary includes here
#include "array_functions.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
//============================================================================

//============================================================================
//	stuff you will need
using namespace std;
//============================================================================
//TODO define a structure to track words and number of times they occur
struct entry {
	string word;
	int occurences;
};

//TODO add a global array of entry structs (global to this file)
entry *list = new entry[200];

//TODO add variable to keep track of next available slot in array
string filename;
int size = 0;
int index = 0;

entry createEntry(string s, int n) {
	entry word;
	word.word = s;
	word.occurences = n;
	return word;
}

//zero out array that tracks words and their occurrences
void clearArray() {
	//cout << "Clearing array" << endl;
	size = 0;
	//cout << "Array size is now " << size << endl;
}

//how many unique words are in array
int getArraySize() {
	//cout << "size of array is " << size << endl;
	return size;
}

//get data at a particular location
string getArrayWordAt(int i) {

	return "";
}

int getArrayWord_NumbOccur_At(int i) {

	return 0;
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(fstream &myfstream) {

	ifstream myInputFile;
	myInputFile.open(filename.c_str(), ios::in);

	if (myInputFile.is_open()) {
		string line;

		while (!myfstream.eof()) {
			getline(myfstream, line);
			processLine(line);
		}
		myInputFile.close();
		return true;
	} else {
		return false;
	}
}

/*take 1 line and extract all the tokens from it
 feed each token to processToken for recording*/
void processLine(string &myString) {
	istringstream iss(myString);
	string word;
	while (iss >> word) {
		//cout<<word<<endl;
		processToken(word);
	}

}

/*Keep track of how many times each token seen*/
void processToken(std::string &token) {

	cout << "Word is " << token << endl;

	//TODO I need to remove any periods and whitespaces from
	//these tokens

	for (unsigned int i = 0; i < sizeof(list); i++) {
		if (list[i].word == token) {
			cout << "CONTAINED" << endl;
			list[i].occurences++;
		} else {
			entry add = createEntry(token, 1);
			list[index] = add;
			index++;
			size++;
		}
	}
}

/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {

	filename = myFileName;
	ifstream myInputFile;
	myInputFile.open(myFileName.c_str(), ios::in);

	if (myInputFile.is_open()) {
		/*string line;

		 while (!myInputFile.eof()) {
		 getline(myInputFile, line);

		 cout << line;

		 }*/
		myInputFile.close();
		return true;
	} else {
		return false;
	}
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile) {

}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename) {

	return 0;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 * You are provided with a myentry compare function in the cpp file
 */
void sortArray(constants::sortOrder so) {

}

