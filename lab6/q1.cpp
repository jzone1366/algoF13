#include <iostream>
#include <fstream>
#include <limits.h>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <list>

using namespace std;

int INFINITY = INT_MAX;

class Vertex {
public:
    string           name;   // Vertex name
    vector<Vertex *> adj;    // Adjaecnt vertices
    int              dist;   // Cost
    Vertex          *path;   // Previous vertex on shortest path

    Vertex( const string & nm ) : name( nm )
      { reset( ); }

    void reset( )
      { dist = INFINITY; path = NULL; }
};


typedef map<string,Vertex *> vmap;
typedef pair<string,Vertex *> vpair;


class Graph
{
  public:
    Graph( ) { }
    ~Graph( );
    void addEdge( const string & sourceName, const string & destName );
    void printPath( const string & destName ) const;
    void unweighted( const string & startName );
    void printAll( );
    Vertex * addVertex(const string & vertexName);
    int vertexToEdge(string & node);
    void buildLadder();
    void longestLadder();
    void processPath(const string & destName) const;
      
  private: 
    void printPath( const Vertex & dest ) const;
    void clearAll( );
    void processPath(const Vertex & dest) const;
    Vertex * getVertex( const string & vertexName );

    vmap vertexMap;
    vector<Vertex *> allVertices;
};



void Graph::addEdge( const string & sourceName, const string & destName )
{
    Vertex * v = getVertex( sourceName );
    Vertex * w = getVertex( destName );
    v->adj.push_back( w );
}

void Graph::printPath( const string & destName ) const
{
    vmap::const_iterator itr = vertexMap.find( destName );

    if( itr == vertexMap.end( ) )
    {
        cout << "Destination vertex not found" << endl;
        return;
    }

    const Vertex & w = *(*itr).second;
    if( w.dist == INFINITY )
        cout << destName << " is unreachable";
    else
        printPath( w );
    cout << endl;
}

// If vertexName is not present, add it to vertexMap
// In either case, return the Vertex
Vertex * Graph::getVertex( const string & vertexName )
{
    vmap::iterator itr = vertexMap.find( vertexName );

    if( itr == vertexMap.end( ) )
    {
        Vertex *newv = new Vertex( vertexName );
        allVertices.push_back( newv );
        vertexMap.insert( vpair( vertexName, newv ) );
        return newv;
    }
    return (*itr).second;
}

Vertex * Graph::addVertex(const string & vertexName)
{
	Vertex *newv = new Vertex(vertexName);
	allVertices.push_back(newv);
	vertexMap.insert(vpair(vertexName, newv));
	return newv;
}

void Graph::printPath( const Vertex & dest ) const
{
    if( dest.path != NULL )
    {
        printPath( *dest.path );
        cout << " to ";
    }
    cout << dest.name;
}

void Graph::clearAll( )
{
    for( int i = 0; i < allVertices.size( ); i++ )
        allVertices[ i ]->reset( );
}

void Graph::printAll( )
{
	for(int i = 0; i < allVertices.size(); i++)
	{
		Vertex v = (*allVertices[i]);
		cout << v.name << endl;
	}
}
int Graph::vertexToEdge(string & node)
{
	char ch;
	unsigned j;
	int count = 0;
	for(j= 0; j < node.length(); j++)
	{
		string copy = node;
		for (ch = 'a'; ch <= 'z'; ch++)
		{
			if(ch != node[j])
			{
				copy[j] = ch;
				vmap::const_iterator itr = vertexMap.find(copy);
				if(itr != vertexMap.end())
				{
					if(copy != node)
					{
						addEdge(node, copy);
						count++;
					}
				}
			}
		}
	}
}

void Graph::buildLadder()
{
	int count = 0;
	for(int i = 0; i < allVertices.size(); i++)
	{
		vertexToEdge(allVertices[i]->name);
	}
}


Graph::~Graph( )
{
    for( int i = 0; i < allVertices.size( ); i++ )
        delete allVertices[ i ];
}


void Graph::unweighted( const string & startName )
{
    clearAll( );

    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) )
    {
        cout << startName << " is not a vertex in this graph" << endl;
        return;
    }

    Vertex *start = (*itr).second;
    list<Vertex *> q;
    q.push_back( start ); start->dist = 0;

    while( !q.empty( ) )
    {
        Vertex *v = q.front( );	q.pop_front( );

        for( int i = 0; i < v->adj.size( ); i++ )
        {
            Vertex *w = v->adj[ i ];
            if( w->dist == INFINITY )
            {
                w->dist = v->dist + 1;
                w->path = v;
                q.push_back( w );
            }
        }
    }
}
void Graph::longestLadder()
{
	vmap::iterator itr = vertexMap.begin();
	while(itr != vertexMap.end())
	{
		unweighted(itr->first);
		cout << itr->first;
		vmap::iterator itr2 = itr;
		int i = 0;
		while(itr2 != vertexMap.end())
		{
			cout << itr2->first;
			processPath(itr2->first);
			itr2++;
		}
		itr++;
	}
}

void Graph::processPath( const string & destName ) const
{
    vmap::const_iterator itr = vertexMap.find( destName );

    if( itr == vertexMap.end( ) )
    {
        cout << "Destination vertex not found" << endl;
        return;
    }

    const Vertex & w = *(*itr).second;
    if( w.dist == INFINITY )
        cout << destName << " is unreachable";
    else
        processPath( w );
    cout << endl;
}

void Graph::processPath( const Vertex & dest ) const
{
    if( dest.path != NULL )
    {
        processPath( *dest.path );
        cout << " to ";
    }
    cout << dest.name;
}


bool processRequest( istream & in, Graph & g )
{
    string startName;
    string destName;

    cout << "Enter start node: ";
    if( !( in >> startName ) )
        return false;
    cout << "Enter destination node: ";
    if( !( in >> destName ) )
        return false;

    g.unweighted( startName );
    g.printPath( destName );

    return true;
}


//
// A simple main that reads the file given by argv[1]
// and then calls processRequest to compute shortest paths.
// Skimpy error checking in order to concentrate on the basics.
//
int main( int argc, char *argv[ ] )
{
    Graph g;

    if( argc != 2 )
    {
        cerr << "Usage: " << argv[ 0 ] << " graphfile" << endl;
        return 1;
    }

    ifstream inFile( argv[ 1 ] );
    if( !inFile )
    {
        cerr << "Cannot open " << argv[ 1 ] << endl;
        return 1;
    }

    string source, dest;

    // Read the vertices; add them to vertexMap
    while( inFile >> source)
    {
    	cout << source << endl;
        g.addVertex(source);
    }
    g.buildLadder();
    //g.printAll();
    //processRequest( cin, g );
    g.longestLadder();

    return 0;
}