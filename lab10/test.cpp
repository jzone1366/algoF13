#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <list> 

using namespace std;
vector<string> words;
vector<string> possible;
string out[5];
/**
 * Find whether a string exists in the given dictionary
 * @param  string in String to search the dictionary for
 * @return nool TRUE if the given string exissts in the given dictionary.
 */
bool findString(string in) {
	vector<string>::iterator findItr;

	findItr = find(words.begin(), words.end(), in);
	if(findItr != words.end())
		return true;
}

/**
 * Find all the words in the given dictionary with the given char. 
 * Save them into global possble vector. 
 * @param c Character to limit by.
 */
void findAll(char c) {
	vector<string>::iterator wItr = words.begin();
	while(wItr != words.end()) {
		string single_word = *wItr;
		if(single_word[0] == c) {
			possible.push_back(single_word);
			//cout << single_word << endl;
		}
		wItr++;
	}
}

/**
 * Function to check that all columns are words that are in the dictionary.
 * @return TRUE if all columnar words are in the given dictionary.
 */
bool checkMatrix() {
	//Column 2
	string c2;
	c2.push_back(out[0][1]);
	c2.push_back(out[1][1]);
	c2.push_back(out[2][1]);
	c2.push_back(out[3][1]);
	c2.push_back(out[4][1]);

	if(!(findString(c2)))
		return false;

	//Column 3
	string c3;
	c3.push_back(out[0][2]);
	c3.push_back(out[1][2]);
	c3.push_back(out[2][2]);
	c3.push_back(out[3][2]);
	c3.push_back(out[4][2]);
	
	if(!(findString(c3)))
		return false;

	//Column 4
	string c4;
	c4.push_back(out[0][3]);
	c4.push_back(out[1][3]);
	c4.push_back(out[2][3]);
	c4.push_back(out[3][3]);
	c4.push_back(out[4][3]);

	if(!(findString(c4)))
		return false;

	//Column 5
	string c5;
	c5.push_back(out[0][4]);
	c5.push_back(out[1][4]);
	c5.push_back(out[2][4]);
	c5.push_back(out[3][4]);
	c5.push_back(out[4][4]);

	if(!(findString(c5)))
		return false;
}

bool findMatrix(string in) {
	//The current set of strings to test. 
	set<string> current;

	//insert first word into first row.
	out[0] = in;
	current.insert(in);

	//first character in the first row that is used to find all words for column 1.
	char first = out[0][0];
	findAll(first);
	vector<string> col1 = possible;
	possible.clear();
	vector<string>::iterator r1;

	for(r1 = col1.begin(); r1 != col1.end(); r1++) {
		//check that the string is not in the current set.
		if(current.find(*r1) == current.end()) {
			//Insert the string into the current set.
			current.insert(*r1);

			//Initialize the characters for the next 4 rows. 
			char second = (*r1)[1];
			char third = (*r1)[2];
			char fourth = (*r1)[3];
			char fifth = (*r1)[4];
			//Find all possible words for the rows.
			findAll(second);
			vector<string> secondRow = possible;
			possible.clear();
			findAll(third);
			vector<string> thirdRow = possible;
			possible.clear();
			findAll(fourth);
			vector<string> fourthRow = possible;
			possible.clear();
			findAll(fifth);
			vector<string> fifthRow = possible;
			possible.clear();

			//create row iterators
			vector<string>::iterator r2;
			vector<string>::iterator r3;
			vector<string>::iterator r4;
			vector<string>::iterator r5;

			//Check words for row 2 and ensure the word isn't in the current set.
			//Then insert word into current set.
			for(r2 = secondRow.begin(); r2 != secondRow.end(); r2++) {
				if(current.find(*r2) == current.end()) {
					current.insert(*r2);
					//Check words possible for row 3 and ensure the word is not in the set.
					//Then insert word into current set.
					for(r3 = thirdRow.begin(); r3 != thirdRow.end(); r3++) {
						if(current.find(*r3) == current.end()) {
							current.insert(*r3);
							//Check words possible for row 4 and ensure the word isn't in current set.
							//Then insert word into current set.
							for(r4 = fourthRow.begin(); r4 != fourthRow.end(); r4++) {
								if(current.find(*r4) == current.end()) {
									current.insert(*r4);
									//check words possible for row 5 and ensure the word isn't in current set. 
									//Insert word into current set. 
									for(r5 = fifthRow.begin(); r5 != fifthRow.end(); r5++) {
										if(current.find(*r5) == current.end()) {
											current.insert(*r5);

											out[1] = *r2;
											out[2] = *r3;
											out[3] = *r4;
											out[4] = *r5;

											bool result = checkMatrix();

											if(result == true)
												return result;

											current.erase(*r5);
										}
									}
									//Remove row 4 string from set to continue testing
									current.erase(*r4);
								}
							}
							//Remove row 3 string from set to continue testing.
							current.erase(*r3);
						}
					}
					//Remove row 2 string from set to continue testing
					current.erase(*r2);
				}	
			}
			//Remove row 1 string from current set to continue testing
			current.erase(*r1);
		}
	}
	//If we come out of all the loops there is no match for this current word.
	return false;
}

void printDict() {
	vector<string>::iterator itr = possible.begin();
	while(itr != possible.end()) {
		cout << *itr << endl;
		itr++;
	}
}
int main() {

	ifstream inFile("input5.txt");
	if(!inFile.is_open())
		cout << "Error opening the file." << endl;

	string word;
	while(getline(inFile, word)) {
		words.push_back(word);
	}
	sort(words.begin(), words.end());
	bool found = false;
	for(int i = 0; i < words.size(); i++) {
		bool matrix = findMatrix(words[i]);
		if(matrix) {
			for(int j = 0; j < 5; j++) 
				cout << out[j] << endl;
			bool found = true;
			break;
		}
		if(found == true)
			break;
	}
	if(found == false)
		cout << "Matrix does not exist!" << endl;
}
