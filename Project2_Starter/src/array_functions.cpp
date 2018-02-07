/*
 * functionstocomplete.cpp
 *
 *  Created on: Feb 2, 2018
 *      Author: Matt Passarelli
 */

//============================================================================
#include "array_functions.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "utilities.h"
//============================================================================

//============================================================================
//	stuff you will need
using namespace std;
using namespace constants;
//i understand it's bad practice to use this, but I know for a fact nothing is
//going to coincide with std for this project
//============================================================================

struct entry {
	string word;
	int occurences;
};

entry *list = new entry[MAX_WORDS];

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
	list = new entry[MAX_WORDS];
	size = 0;
	index = 0;
	//cout << "Array size is now " << size << endl;
}

//how many unique words are in array
int getArraySize() {
	//cout << "size of array is " << size << endl;
	return size;
}

//get data at a particular location
string getArrayWordAt(int i) {

	return list[i].word;
}

int getArrayWord_NumbOccur_At(int i) {

	return list[i].occurences;
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(fstream &myfstream) {

	if (myfstream.is_open()) {
		//cout<<"FILE OPEN"<<endl;
		string line;

		while (!myfstream.eof()) {
			getline(myfstream, line);
			processLine(line);
		}
		return true;
	} else {
		//cout<<"DID NOT OPEN FILE"<<endl;
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

bool checkPrevious(std::string &token)
{
	for(int i = 0; i<getArraySize(); i++)
	{

		string str1 = list[i].word;
		string str2 = token;

		toUpper(str1);
		toUpper(str2);

		if(str1==str2)
		{
			list[i].occurences++;
			return true;
		}
	}

	return false;
}

/*Keep track of how many times each token seen*/
void processToken(std::string &token) {

	strip_unwanted_chars(token);

	if (!token.empty())
	{
	if(!checkPrevious(token))
	{
		list[index].word=token;
		list[index].occurences=1;
		index++;
		size++;
	}
	}


//	for (unsigned int i = 0; i < sizeof(list); i++) {
//		cout<<sizeof(list)<<endl;
//		cout<<"Comparing: "<<token<<" and "<<list[i].word<<endl;
//		if (compare(list[i].word, token)) {
//			//cout << "CONTAINED" << endl;
//			list[i].occurences++;
//			//cout << "Duplicate word: " << list[i].word << endl;
//			//cout << "Occurrences: " << list[i].occurences << endl;
//			break;
//		}
//
//		else if (i == sizeof(list) - 1 && sizeof(token) > 0) {
//			//cout << "not in list" << endl;
//			entry add = createEntry(token, 1);
//			list[index] = add;
//			cout << "Added word: " << list[index].word << endl;
//			index++;
//			size++;
//			//cout << "Array size: " << size << endl;
//		}
//
//	}
	//cout << "Word is: " << token << endl;
}

/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {

	fstream myInputFile;
	myfile.open(myFileName.c_str(), ios::in);

	if (myfile.is_open()) {
		return true;
	} else {
		return false;
	}
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile) {

	if (myfile.is_open()) {
		myfile.close();
	}

}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename) {

	if (size == 0) {
		//cout << "FAIL NO DATA" << endl;
		return FAIL_NO_ARRAY_DATA;
	} else {
		ofstream output;
		output.open(outputfilename.c_str(), ios::out);

		if (!output.is_open()) {
			//cout << "FAIL DID NOT OPEN" << endl;
			return FAIL_FILE_DID_NOT_OPEN;
		} else {
			//cout << "FILE IS OPEN" << endl;

			for (int i = 0; i < size; i++) {
				output << list[i].word << " " << list[i].occurences << endl;
				//cout << list[i].word << " " << list[i].occurences << endl;
			}
			return SUCCESS;
		}
	}

	//return 0;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 * You are provided with a myentry compare function in the cpp file
 */
void sortArray(constants::sortOrder so) {

	switch (so) {
	case NONE:
		//cout << "NONE" << endl;
		break;
	case ASCENDING:
		for (int i = 0; i < size; i++) {

			for (int k = 0; k < size - i - 1; k++) {

				string str1= list[k].word;
				string str2 = list[k+1].word;

				toUpper(str1);
				toUpper(str2);

				if (str1 > str2) {
					//cout<<"Sorting: "<<list[k].word<< " and "<<list[k+1].word<<endl;
					entry temp;
					temp = list[k];
					list[k] = list[k + 1];
					list[k + 1] = temp;
				}
			}
		}
		break;
	case DESCENDING:
		for (int i = 0; i < size; i++) {

			for (int k = 0; k < size - i - 1; k++) {
				if (list[k].word < list[k + 1].word) {
					entry temp;
					temp = list[k];
					list[k] = list[k + 1];
					list[k + 1] = temp;
				}
			}
		}

		break;
	case NUMBER_OCCURRENCES:
		for (int i = 0; i < size; i++) {

			for (int k = 0; k < size - i - 1; k++) {
				if (list[k].occurences > list[k + 1].occurences) {
					entry temp;
					temp = list[k];
					list[k] = list[k + 1];
					list[k + 1] = temp;
				}
			}
		}
		break;
	default:
		break;
	}

}

