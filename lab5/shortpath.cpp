#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <queue>
#include <map>
#include <stack>

using namespace std;

class Graph{
		map< string, vector<string> > GraphAdList;
		map< string, bool> Nodes;
	public:
		Graph(string filename);
		void printGraph();
		void searchGraphBFS(string startnode);
		void searchGraphDFS(string startnode);
		void cleanVisitRecord();
		void find_shortest_path(string startnode, string endnode);
};

Graph::Graph(string filename){
	string line;
	fstream graphfile;
	graphfile.open(filename.c_str());
	if(!graphfile){
		cout<<"Error opening file!"<<endl;
	}
	while(getline(graphfile,line)){
		string node;
		vector<string> tmpvector;
		istringstream iss(line);
		string value;
		while(iss >> value){
			tmpvector.push_back(value);
		}
		node = tmpvector[0];
		tmpvector.erase(tmpvector.begin());
		GraphAdList[node]=tmpvector;
		Nodes[node] = false;
	}
	printGraph();
}

void Graph::printGraph(){
	cout<<"Graph adjacent list: "<<endl;
	for(map< string, vector<string> >::iterator i = GraphAdList.begin(); i!=GraphAdList.end(); i++){
		cout<<i->first<<" ";
		for(vector<string>::iterator j = i->second.begin(); j!=i->second.end();j++){
			cout<<" "<<*j;
		}
		cout<<endl;
	}
	cout<<endl;
	/*cout<<"Node visiting status: "<<endl;
	for(map<string, bool>::iterator k = Nodes.begin(); k != Nodes.end(); k++){
		cout<<k->first<<" "<<k->second<<endl;
	}
	cout<<endl;*/
}

void Graph::cleanVisitRecord(){
	for(map<string, bool>::iterator i = Nodes.begin(); i!=Nodes.end(); i++){
		i->second = false;
	}
}

void Graph::searchGraphBFS(string startnode){
	cleanVisitRecord();
	Nodes[startnode] = true;
	queue<string> nodesFIFO;
	vector<string> visitsequence;
	visitsequence.push_back(startnode);
	for(vector<string>::iterator i = GraphAdList[startnode].begin(); i !=GraphAdList[startnode].end(); i++){
		nodesFIFO.push(*i);
		Nodes[*i] = true;
	}
	while(!nodesFIFO.empty()){
		string s = nodesFIFO.front();
		nodesFIFO.pop();
		visitsequence.push_back(s);
		for(vector<string>::iterator i = GraphAdList[s].begin(); i !=GraphAdList[s].end(); i++){
			if(!Nodes[*i]){
				nodesFIFO.push(*i);
				Nodes[*i] = true;
			}
		}
	}
	cout<<"BFS searching sequence: ";
	for(vector<string>::iterator i = visitsequence.begin(); i!=visitsequence.end(); i++){
		cout<<*i<<" ";
	}
	cout<<endl;
}

void Graph::searchGraphDFS(string startnode){
	cleanVisitRecord();
	Nodes[startnode] = true;
	stack<string> nodesLIFO;
	vector<string> visitsequence;
	visitsequence.push_back(startnode);
	for(vector<string>::iterator i = GraphAdList[startnode].begin(); i != GraphAdList[startnode].end(); i++){
		nodesLIFO.push(*i);
		Nodes[*i] = true;
	}
	while(!nodesLIFO.empty()){
		string s = nodesLIFO.top();
		nodesLIFO.pop();
		visitsequence.push_back(s);
		for(vector<string>::iterator i = GraphAdList[s].begin(); i!=GraphAdList[s].end(); i++){
			if(!Nodes[*i]){
				nodesLIFO.push(*i);
				Nodes[*i] = true;
			}
		}
	}
	cout<<"DFS searching sequence: ";
	for(vector<string>::iterator i = visitsequence.begin(); i!=visitsequence.end(); i++){
		cout<<*i<<" ";
	}
	cout<<endl;
}

int main(){

	Graph G("g1.txt");
	G.searchGraphBFS("A", "D");
	//G.searchGraphDFS("1");

	return 0;
}
