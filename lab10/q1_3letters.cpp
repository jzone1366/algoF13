#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <set>

using namespace std;

// This will contain the list of the words read from the
// input file
list<string> words[26];

// This will contain the output matrix
string out[3];

// This function finds whether the string exits
// in the given dictionary, it searches based on the 
// first character of the string

bool findString(string in)
{
    list<string> strings = words[(int)(in[0]-'a')];
    list<string>:: iterator p;

    p = find(strings.begin(),strings.end(),in);
    if(p!=strings.end())
        return true;
}

// Since we have already chosen valid strings for all the rows
// and first column we just need to check the diagnol and the 
// 2 and 3rd column

bool checkMatrix()
{
    // Column 2
    string c2;
    c2.push_back(out[0][1]);
    c2.push_back(out[1][1]);
    c2.push_back(out[2][1]);

    if(!(findString(c2)))
        return false;

    // Column 3
    string c3;
    c3.push_back(out[0][2]);
    c3.push_back(out[1][2]);
    c3.push_back(out[2][2]);


    if(!(findString(c3)))
        return false;
    else
        return true;
    // If all match then return true
}

// It finds all the strings begining with a particular character

list<string> findAll(int i)
{
    // It will contain the possible strings
    list<string> possible;
    list<string>:: iterator it;

    it = words[i].begin();
    while(it!=words[i].end())
    {
        possible.push_back(*it);
        it++;
    }

    return possible;
}

// It is the function which is called on each string in the dictionary

bool findMatrix(string in)
{
    // contains the current set of strings
    set<string> current;

    // set the first row as the input string
    out[0]=in;
    current.insert(in);

    // find out the character for the column
    char first = out[0][0];

    // find possible strings for the column
    list<string> col1 = findAll((int)(first-'a'));
    list<string>::iterator it;

    for(it = col1.begin();it!=col1.end();it++)
    {
        // If this string is not in the current set
        if(current.find(*it) == current.end())
        {
            // Insert the string in the set of current strings
            current.insert(*it);

            // The characters for second and third rows
            char second = (*it)[1];
            char third = (*it)[2];

            // find the possible row contenders using the column string
            list<string> secondRow = findAll((int)(second-'a'));
            list<string> thirdRow = findAll((int)(third-'a'));

            // Iterators
            list<string>::iterator it1;
            list<string>::iterator it2;


            for(it1= secondRow.begin();it1!=secondRow.end();it1++)
            {
                // If this string is not in the current set
                if(current.find(*it1) == current.end())
                {

                    // Use it as the string for row 2 and insert in the current set
                    current.insert(*it1);

                    for(it2 = thirdRow.begin();it2!=thirdRow.end();it2++)
                    {
                        // If this string is not in the current set
                        if(current.find(*it2) == current.end())
                        {   

                            // Insert it in the current set and use it as Row 3
                            current.insert(*it2);

                            out[1]=*it1;
                            out[2]=*it2;

                            // Check ifthe matrix is a valid matrix
                            bool result = checkMatrix();

                            // if yes the return true
                            if(result == true)
                                return result;

                            // If not then remove the row 3 string from current set
                            current.erase(*it2);
                        }
                    }
                    // Remove the row 2 string from current set
                    current.erase(*it1);
                }
            }
            // Remove the row 1 string from current set
            current.erase(*it);
        }
    }
    // If we come out of these 3 loops then it means there was no 
    // possible match for this string
    return false;           
}

int main()
{
    const char* file = "input.txt";
    ifstream inFile(file);

    string word;

    // Read the words and store them in array of lists
    // Basically radix sort them based on their first character
    // so all the words with 'a' appear in the same list 
    // i.e. words[0]

    if(inFile.is_open())
    {
        while(inFile.good())
        {
            inFile >> word;
            if(word[0] >= 'a' && word[0] <= 'z')
            {
                int index1 = word[0]-'a';
                words[index1].push_back(word);
            }
        }
    }
    else
        cout<<"The file could not be opened"<<endl;


    // Call the findMatrix function for each string in the list and
    // stop when a true value is returned

    int i;
    for(i=0;i < 26;i++)
    {
        list<string>::iterator it = words[i].begin();
        while(it!=words[i].end())
        {
            if(findMatrix(*it))
            {
                // Output the matrix
                for(int j=0;j<3;j++)
                    cout<<out[j]<<endl;

                // break out of both the loops
                i=27;
                break;
            }
            it++;
        }
    }

    // If i ==26 then the loop ran the whole time and no break was
    // called which means no match was found

    if(i==26)
        cout<<"Matrix does not exist"<<endl;

    return 0;
}