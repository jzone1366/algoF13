#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <stdlib.h>

using namespace std;

class Graph{
		map<string, vector<string> > GraphAdList;	// Graph adjacent list
		map<string, vector<string> > RvGraphAdList;	// Graph adjacent list
		map<string, bool> Nodes;		// Visit status (true of false)
		map<unsigned long, string> FT;		// Finishing time	order | node
		map<unsigned long, vector<string> > Leaders;
		unsigned long sourceNode;
		unsigned long t;
		unsigned long nodeNum;
		string fs;
	public:
		Graph(string filename);		// Graph constructor
		void SCCs();
	private:
		void cleanVisitRecord();
		void printGraph(map<string, vector<string> > &G);	// Print graph adjacent list
		void loopDFS(map<string, vector<string> > &G);		// DFS loop
		void DFS(map<string, vector<string> > &G, string &startnode);		// DFS search graph starting at node "startnode"

};

Graph::Graph(string filename){
	cout<<"-- Constructing graph ......"<<endl;
	fs = filename;
	string line;
	fstream graphfile;
	graphfile.open(fs.c_str());
	if(!graphfile){
		cout<<"Error opening file!"<<endl;
		 exit(EXIT_FAILURE);
	}else{
		vector< vector<string> > edges;
		while(getline(graphfile,line)){
			vector<string> tmpvector;
			istringstream iss(line);
			string value;
			while(iss >> value){
				tmpvector.push_back(value);
			}
			edges.push_back(tmpvector);
		}
		for(vector< vector<string> >::const_iterator i =edges.begin(); i < edges.end(); i++){
			GraphAdList[(*i)[0]].push_back((*i)[1]);
			RvGraphAdList[(*i)[1]].push_back((*i)[0]);
			Nodes[(*i)[0]] = false;
			Nodes[(*i)[1]] = false;
		}
		edges.clear();
		unsigned long index = 1;
		for(map<string, bool >::const_iterator j = Nodes.begin(); j != Nodes.end(); j++){
			//cout<<j->first<<" "<<j->second<<endl;
			//index = atol((j->first).c_str());
			FT[index] = j->first;
			//cout<<index<<" "<<j->first<<endl;
			index++;
		}
		nodeNum = Nodes.size();
		//cout<<"-- Graph adjacent list: "<<endl;
		//map<string, vector<string> > &G = GraphAdList;
		//printGraph(G);
		cout<<"-- Graph construction complete!"<<endl;
		cout<<"-- Total number of node: "<<nodeNum<<endl;
		//printGraph(RvGraphAdList);
		}
}

void Graph::printGraph(map<string, vector<string> > &G){
	for(map< string, vector<string> >::const_iterator i = G.begin(); i!=G.end(); i++){
		cout<<i->first<<" ";
		for(vector<string>::const_iterator j = i->second.begin(); j!=i->second.end();j++){
			cout<<" "<<*j;
		}
		cout<<endl;
	}
	cout<<endl;
}

void Graph::cleanVisitRecord(){
	for(map<string, bool>::iterator i = Nodes.begin(); i!=Nodes.end(); i++){
		i->second = false;
	}
}

void Graph::DFS(map<string, vector<string> > &G, string &startnode){
	Nodes.at(startnode) = true;
	Leaders[sourceNode].push_back(startnode);
	for(vector<string>::const_iterator i = G[startnode].begin(); i!=G[startnode].end(); i++){
		if(!(Nodes.at(*i))){
			string newnode = *i;
			cout<<"------ visit node: "<< newnode <<endl;
				DFS(G,newnode);
			newnode.clear();
		}
	}
	t++;
	FT[t] = startnode;		// Order | node
	cout<<"------ Node "<<startnode<<" finishing time: "<<t<<endl;
	startnode.clear();
}

void Graph::loopDFS(map<string, vector<string> > &G){
	Leaders.clear();
	cleanVisitRecord();
	unsigned long n = nodeNum;
	map<unsigned long, string> FT_tmp = FT;
	FT.clear();
	t = 0;
	do{
		cout<<"---- loop: "<<n<<endl;
		string node = FT_tmp.at(n);
		cout<<"---- check node: "<<node<<endl;
		if(!(Nodes.at(node))){
			cout<<"---- new node "<<node<<endl;
			sourceNode = atoi(node.c_str());
			cout<<"---- visit node: "<< node<<endl;
			string &newnode = node;
			DFS(G,newnode);
		}else{
			cout<<"---- node: "<<node<<" already visited!"<<endl;
		}
		node.clear();
		n--;
	}while(n != 0);
	/*for(map<int, string>::const_iterator i = FT.begin(); i != FT.end(); i++){
		cout<< i->first <<" "<< i->second << endl;
	}*/
}

void Graph::SCCs(){
	cout<<"-- DFS loop on reverted graph adjacent list ......"<<endl;
	map<string, vector<string> > &RvG = RvGraphAdList;
	loopDFS(RvG);
	cout<<"-- DFS loop on original graph adjacent list ......"<<endl;
	map<string, vector<string> > &G = GraphAdList;
	loopDFS(G);

	cout<< "Graph clusters: "<<endl;
	for(map< unsigned long, vector<string> >::const_iterator i = Leaders.begin(); i!=Leaders.end(); i++){
		cout<<i->first<<" ";
		for(vector<string>::const_iterator j = i->second.begin(); j!=i->second.end();j++){
			cout<<" "<<*j;
		}
		cout<<endl;
	}
	cout<<"There are "<<Leaders.size()<<" clusters"<<endl;
	cout<<"Size of each clusters: "<<endl;
	for(map< unsigned long, vector<string> >::const_iterator i = Leaders.begin(); i!=Leaders.end(); i++){
		cout<<i->first<<": "<<i->second.size()<<endl;
	}

	ofstream myfile;
	myfile.open("Result.txt");
	myfile<<"There are "<<Leaders.size()<<" clusters"<<endl;
	myfile<<"Size of each clusters: "<<endl;
	for(map< unsigned long, vector<string> >::const_iterator i = Leaders.begin(); i!=Leaders.end(); i++){
			myfile<<i->first<<": "<<i->second.size()<<endl;
	}
}

int main() {
	cout<<"Calculating strongly connected points ......"<<endl;
	Graph G("Example.txt");
	G.SCCs();
	return 0;
}
