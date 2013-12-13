#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

int nverts = 0;
class SetOfSets;

// Just a list of vertices that correspond to a cover set.
// Objects of this type can be placed into a linked list via the 'next'
// field (this is managed by a SetOfSets object - see below)
class CoverSet {
   friend class SetOfSets;
   friend ostream &operator<<(ostream&, SetOfSets*);
   friend ostream &operator<<(ostream&, CoverSet*);
   int *vertex, nvertices;
   CoverSet *next;

public:
   CoverSet () { vertex = new int[nverts];  nvertices = 0;  next = NULL; }

   // Add a vertex to the cover
   CoverSet *add (int i) { vertex[nvertices++] = i; return this; }

   // Return a copy of this cover
   CoverSet *getCopy () {
      CoverSet *newset = new CoverSet();
      for (int i=0 ; i < nvertices ; i++) newset->add(vertex[i]);
      return newset;
   }

   // Return true if and only if vertex v is in this cover
   bool member (int v) {
      for (int i=0 ; i < nvertices ; i++) if (vertex[i] == v) return true;
      return false;
   }
};

ostream &operator<<(ostream &out, CoverSet *cs) {
   if (cs->nvertices == 0)
      out << "{ }";
   else {
      out << "{";
      for (int i=0 ; i < cs->nvertices ; i++) out << cs->vertex[i] << ",";
      out << "\b}";
   }
   return out;
}

// Stores a linked list of cover sets - a SetOfSets object is an entry 
// in the dynamic programming table
class SetOfSets {
   friend ostream &operator<<(ostream&, SetOfSets*);
   CoverSet *set, *cursor;
   
public:
   SetOfSets () { set = cursor = NULL; }

   // Return true iff there are no covers stored in this object
   bool empty () { return set == NULL; }

   // Add a cover to this list of covers
   void add (CoverSet *s) {
      if (s == NULL) return;
      s->next = set; set = s;
   }

   // Move the cursor to the first cover, return the first cover.
   // Used to begin iterating though the stored list of covers.
   CoverSet *getFirst() { cursor = set; return set; }

   // Move the cursor to the next cover, return the next cover.
   // Used to continue iterating though the stored list of covers
   // and to identify the end of the list of covers.
   CoverSet *getNext() { 
      if (cursor == NULL) return NULL;
      return cursor = cursor->next;
   }
};

ostream &operator<<(ostream &out, SetOfSets *set) {
   out << " ";
   for (CoverSet *s=set->set ; s != NULL ; s=s->next) out << s << ",";
   out << "\b ";
   return out;
}

// Holds a graph for which the minimum vertex cover is to be found
class Graph {
   friend ostream& operator<<(ostream&, Graph*);
   int **vertex, *nvertex, nedges;

public:
   Graph () { vertex = NULL; }

   // Read the input file representing a graph - create an adjacency 
   // list for each vertex
   // File format:
   //   <number-of-vertices> <number-of-edges>
   //   <vertex-1> <vertex-2>
   //   ...
   //   <vertex-1> <vertex-2>
   void readFile (char *filename) {
      int v1, v2;
      fstream fin(filename, ios::in);
      if (fin.fail()) {
         cout << "Error in File Read\n";
         exit(0);
      }
      fin >> nverts >> nedges;
      vertex = new int*[nverts];
      nvertex = new int[nverts];
      for (int i=0 ; i < nverts ; i++) {
         vertex[i] = new int[nedges];
         nvertex[i] = 0;
      }
      for (int i=0 ; i < nedges ; i++) {
         fin >> v1 >> v2;
         vertex[v1][nvertex[v1]++] = v2;
         vertex[v2][nvertex[v2]++] = v1;
      }
   }

   // Returns true if and only if all vertices with ids between 0 and v-1
   // that are adjacent to v are in the cover cs.  Parameter cs is supposed
   // to be a cover for the subgraph that includes vertices 0...v-1.  If 
   // true is returned then cs is still a cover for the subgraph that 
   // includes vertices 0...v.
   bool allAdjCovered (int v, CoverSet *cs) {
      for (int i=0 ; i < nvertex[v] ; i++) {
         int vv = vertex[v][i];
         if (vv >= v) continue;
         if (!cs->member(vv)) return false;
      }
      return true;
   }
};

ostream &operator<<(ostream &out, Graph *g) {
   out << "Graph, adjacency lists:\n";
   for (int i=0 ; i < nverts ; i++) {
      out << "\t" << i << ": ";
      for (int j=0 ; j < g->nvertex[i] ; j++) out << g->vertex[i][j] << ",";
      out << "\b \n";
   }
   out << "\n";
   return out;
}

// Display sets of covers in row k of the table DP
void showRow(SetOfSets ***DP, int k) {
   for (int i=0 ; i <= nverts ; i++) {
      if (DP[k][i]->empty()) continue;
      cout << "[" << k << "," << i << "]:\n" << DP[k][i] << "\n";
   }
   cout << "----------------------------------------------\n";
}

int main (int argc, char **argv) {
   if (argc < 2) {
      cout << "Not enough arguments.\n";
      exit(0);
   }

   bool showrows = (argc > 2) ? true : false;

   // Grab a graph and read edges from file
   Graph *graph = new Graph();
   graph->readFile(argv[1]);
   if (showrows) cout << graph;

   // Initialize the table
   // DP[i][j] - covers of size j for subgraph induced by vertices 0...i
   SetOfSets ***DP = new SetOfSets**[nverts];
   for (int i=0 ; i < nverts ; i++) {
      DP[i] = new SetOfSets*[nverts+1];
      for (int j=0 ; j <= nverts ; j++) DP[i][j] = new SetOfSets();
   }
           
   // Complete the 0th row - vertex 0 - { }, {0} for all graphs
   DP[0][0]->add(new CoverSet());
   DP[0][1]->add((new CoverSet())->add(0));

   if (showrows) showRow(DP, 0);

   CoverSet *cs;
   // Complete all remaining rows - 
   for (int k=0 ; k < nverts-1 ; k++) {
      for (int i=0 ; i < nverts ; i++) {
         if (!DP[k][i]->empty()) {
            // For each cover set in row k, column i do this:
            // Add the new vertex (k+1) to a copy of the cover set and 
            // stick the copy into row k+1, column i+1.
            // Then stick a copy of the cover set into row k+1, column i
            // unless vertex (k+1) is connected to some vertex with id
            // between 0 and k that is not in the cover.
            for (cs=DP[k][i]->getFirst(); cs != NULL; cs=DP[k][i]->getNext()) {
               DP[k+1][i+1]->add((cs->getCopy())->add(k+1));
               if (graph->allAdjCovered(k+1,cs)) DP[k+1][i]->add(cs->getCopy());
            }
         }
      }
      if (showrows) showRow(DP, k+1);
   }

   // Walk through top row from column 0 until some sets are found
   // then output those sets
   for (int i=0 ; i < nverts ; i++) {
      if (DP[nverts-1][i]->empty()) continue;
      cout << "Covers:" << DP[nverts-1][i] << "\n";
      break;
   }
}