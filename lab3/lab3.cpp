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
    vector<Vertex *> adj;    // Adjacent vertices
    int              dist;   // Cost
    Vertex          *path;   // Previous vertex on shortest path
    int             prenum;
    int             postnum;
    bool            isVisited;
 
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
    map<int,string> tmap;
    void addEdge( const string & sourceName, const string & destName );
    void printPath( const string & destName ) const;
    void unweighted( const string & startName );
    void explore(Vertex* v, int & n);
    void dfs();
    void printtop();
    void reverse();
     
  private:
    Vertex * getVertex( const string & vertexName );
    void printPath( const Vertex & dest ) const;
    void clearAll( );
 
    vmap vertexMap;
    vector<Vertex *> allVertices;
};
 
void Graph::dfs(){
    int n = 1;
    for(int i = 0; i < allVertices.size(); i++)
    {
        (*allVertices[i]).isVisited = false;
    }
    for(int i = 0; i < allVertices.size(); i++)
    {
        if((*allVertices[i]).isVisited == false){
            explore(allVertices[i], n);
        }
    }
    for(int i = 0; i < allVertices.size(); i++)
    {
        cout << "vertex " << (*allVertices[i]).name << " prenum " << (*allVertices[i]).prenum
             << " postnum " << (*allVertices[i]).postnum << endl;
    }
    
 
}
 
void Graph::explore(Vertex * v, int & n){
    if((*v).isVisited == true)
    {
        return;
    }
    (*v).isVisited = true;
    (*v).prenum = n++;
    for(int i = 0; i < (*v).adj.size(); i++)
    {
        if((*(*v).adj[i]).isVisited == false)
        {
            explore((*v).adj[i],n);
        }
    }
    (*v).postnum = n;
    tmap.insert(pair<int,string>(n,(*v).name));
    n++;
}
void Graph::reverse()
{
    for(int i = 0; i < allVertices.size(); i++)
    {
        //cout << (*allVertices[i]).name << endl;
        cout << "Adj " << (*allVertices[i]).adj.`name << endl;
    }
}
 
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
        Vertex *v = q.front( ); q.pop_front( );
 
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
 
void Graph::printtop(){
    map<int,string>::reverse_iterator titr = tmap.rbegin();
    for(;titr!=tmap.rend();titr++){
        cout << "vertex " << titr->second << " " << "post num "
             << titr->first<< endl;
    }
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
    g.printtop();
 
    return true;
}
 
 
/**
 * A simple main that reads the file given by argv[1]
 * and then calls processRequest to compute shortest paths.
 * Skimpy error checking in order to concentrate on the basics.
 */
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
    while( inFile >> source >> dest )
    {
        g.addEdge( source, dest );
    }
 
    cout << "File read" << endl;
    //g.dfs();
    g.reverse();
 
    //while( processRequest( cin, g ) )
    //   ;
 
    return 0;
}