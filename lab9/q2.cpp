#include<iostream>
#include<cstring>

using namespace std;

// A utility function to get max of two integers
int max (int x, int y) { return (x > y)? x : y; }

// Returns the length of the longest palindromic subsequence in seq
int lps(char *str,char *result)
{
   int n = strlen(str);
   int i, j, cl;
   int L[n][n];  // Create a table to store results of subproblems

   int Way[n][n];// Store the palindrome


   // Strings of length 1 are palindrome of length 1
   for (i = 0; i < n; i++)
   {
       L[i][i] = 1;
       Way[i][i]=0;
   }
    for (cl=2; cl<=n; cl++)
    {
        for (i=0; i<n-cl+1; i++)
        {
            j = i+cl-1;
            if (str[i] == str[j] && cl == 2)
            {
                   L[i][j] = 2;
                   Way[i][j]=0;     
            }

            else if (str[i] == str[j])
            {
                  L[i][j] = L[i+1][j-1] + 2;
                  Way[i][j]=0;
            }

            else
            {
                if(L[i][j-1]>L[i+1][j])
                {
                   L[i][j]=L[i][j-1];
                   Way[i][j]=1;                    
                }
                else
                {
                    L[i][j]=L[i+1][j];
                    Way[i][j]=2;  
                }

            }

        }
    }

    int index=0;
    int s=0,e=n-1;

    while(s<=e)
    {
         if(Way[s][e]==0)
         {
             result[index++]=str[s];
             s+=1;
             e-=1;

         }
         else if(Way[s][e]==1)e-=1;
         else if(Way[s][e]==2)s+=1;     
    }

    int endIndex=(L[0][n-1]%2)?index-1:index;

    for(int k=0;k<endIndex;++k)result[L[0][n-1]-1-k]=result[k];

    result[index+endIndex]='\0';


    return L[0][n-1];
}

/* Driver program to test above functions */
int main()
{
    char seq[20];
    char result[20];
    cout << "Enter a string: ";
    cin >> seq;
    int pal = lps(seq,result);
    cout<<"The length of the LPS is: "<< pal << endl;
    cout<<"Resulting String is: " << result <<endl;
    return 0;
}