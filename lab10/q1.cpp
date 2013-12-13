#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <list>

using namespace std;

vector<string> words;

string out[5];

/**
 * Finds whether a string exists in the given dictionary
 * @param  string in String to search the dictionary for
 * @return bool TRUE if the given string exists in the given dictionary
 */
bool findString(string in) {
	vector<string>::iterator findItr;

	findItr = find(words.begin(),words.end(),in);
	if(findItr != words.end())
		return true;
}

/**
 * Function to check that all columns are words that are in the dictionary. 
 * @return TRUE if all column words are in the dictionary.
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

/**
 * Finds all the strings beginning with a particular character.
 */
/*vector<string> findAll(int i) {
	vector<string> possible;
	vector<string>::iterator itr;

	itr = words[i].begin();
	while(itr != words[i].end()) {
		possible.push_back(*itr);
		itr++;
	}

	return possible;
}*/


/*bool findMatrix(string in) {
	//The current set of strings to test.
	list<string> current;

	//insert first word into the first row.
	out[0]=in;
	current.insert(in);

	//first character in the first row to use to find the word for column 1.
	char first = out[0][0];

	vector<string> col1 = findAll((int)(first-'a'));
	vector<string>::iterator r1;

	for(r1 = col1.begin(); r1 != col1.end(); r1++) {
		//Check if the string is not in the current set
		if(current.find(*r1) == current.end()) {
			//Insert the string into the current set. 
			current.insert(*r1);

			//The characters for the 2nd, 3rd, 4th, and 5th rows.
			char second = (*r1)[1];
			char third = (*r1)[2];
			char fourth = (*r1)[3];
			char fifth = (*r1)[4];

			//Find all possible words for the rows
			vector<string> secondRow = findAll((int)(second-'a'));
			vector<string> thirdRow = findAll((int)(third-'a'));
			vector<string> fourthRow = findAll((int)(fourth-'a'));
			vector<string> fifthRow = findAll((int)(fifth-'a'));

			//Create iterators for all rows
			vector<string>::iterator r2;
			vector<string>::iterator r3;
			vector<string>::iterator r4;
			vector<string>::iterator r5;

			//Check words for row 2 and ensure the word isn't in the current set.
			//Then insert word into current set. 
			for(r2 = secondRow.begin(); r2!=secondRow.end(); r2++) {
				if(current.find(*r2) == current.end()){
					current.insert(*r2);
					//Check words possible for row 3 and ensure the word isn't in the current set.
					//Then insert word into current set. 
					for(r3 = thirdRow.begin(); r3 != thirdRow.end(); r3++) {
						if(current.find(*r3) == current.end()) {
							current.insert(*r3);
							//Check words possible for row 4 and ensure the word isn't in the current set.
							//Then insert word into current set.
							for(r4 = fourthRow.begin(); r4 != fourthRow.end(); r4++) {
								if(current.find(*r4) == current.end()) {
									current.insert(*r4);
									//Check words possible for row 5 and ensure the word isn't in the current set. 
									//Then insert word into current set. 
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
									//Remove row 4 string from current set to continue testing
									current.erase(*r4);
								}
							}
							//Remove row 3 string from current set to continue testing
							current.erase(*r3);
						}
					}
					//Remove row 2 string from current set to continue testing.
					current.erase(*r2);
				}
			}
			//Remove row 1 string from current set
			current.erase(*r1);
		}
	}
	//If we come out of all the loops then there is no match for that string. 
	return false;
}*/

/**
 * Print the dictionary to ensure that the dictionary is read in and sorted correctly
 * Used for Debugging
 */
void printDict() {
	vector<string>::iterator itr = words.begin();
	while(itr != words.end()) {
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

	/*for(int i =0; i < words.size(); i++) {
		vector<string>::iterator itr = words[i].begin();
		while(itr != words[i].end()) {
			if(findMatrix(*itr)) {
				for(int j = 0; j < out.size(); j++)
					cout << out[j] << endl;
				itr = words[i].end();
				break;
			}
			itr++;
		}
	}*/
}