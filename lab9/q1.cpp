#include <iostream>
#include <string>
#include <vector>

using namespace std;
template <class T> unsigned int edit_distance(const T& s1, const T& s2) 
{
        const size_t len1 = s1.size(), len2 = s2.size();
        vector<vector<unsigned int> > d(len1 + 1, vector<unsigned int>(len2 + 1));
        d[0][0] = 0;
        for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
        for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;
 
        for(unsigned int i = 1; i <= len1; ++i)
                for(unsigned int j = 1; j <= len2; ++j)
 
                      d[i][j] = std::min( std::min(d[i - 1][j] + 1,d[i][j - 1] + 1),
                                          d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) );
        return d[len1][len2];

}

int main() 
{
    string s1, s2;
    int dist;
    cout << "Enter two strings:\n";
    while (cin >> s1 >> s2)
    {
        dist = edit_distance(s1, s2);
        cout << "Edit Distance is: " << dist << endl;
    }
    return 0;
}