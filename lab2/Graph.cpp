#include "Graph.h"
#include <string>
#include <fstream>
#include <bits/stdc++.h>

void
Graph::readFile(const char* in)
{
	ifstream infile(in);	/**< Input file stream. */
	string line;		/**< One line of the file. */
	int from;		/**< Node number of where an edge starts. */
	int to;			/**< Node number of where an edge ends. */
	char input;		/**< The input that triggers the transition. */

	while(getline(infile, line)) {
		/** Split a line. */
		stringstream chk(line);
		vector<string> tokens;
		string inter;
		while(getline(chk, inter, ' '))
			tokens.push_back(inter);

		/** Create an edge for a line. */
		if(tokens.size() < 2) {
			cout<<"Format error"<<endl;
			exit(0);
		} else if(tokens.size() == 2) {
			insertEdge(atoi(tokens[0].c_str()), atoi(tokens[1].c_str()), 0);
		} else if(tokens.size() == 3) {
			insertEdge(atoi(tokens[0].c_str()), atoi(tokens[1].c_str()), tokens[2].c_str()[0]);
		} else {
			cout<<"Format error"<<endl;
			exit(0);
		}
	}
}

void
Graph::insertEdge(int from, int to, char input)
{
	Edge edge(from, to, input);
	m_vecEdges.push_back(edge);
}

void
Graph::print(ostream& os) const
{
	vector<Edge> sorted = m_vecEdges;
	sort(sorted.begin(), sorted.end());
	for(int i=0; i<sorted.size(); i++)
		os<<sorted[i];
}

Set
Graph::getEClosure(int s)
{
	/** TODO: Implement this function */
	Set eClosures;
	eClosures.insert(s);
	queue<int>que;
	que.push(s);
	while(!que.empty()){
		int now=que.front();
		que.pop();
		for(Edge k:m_vecEdges){
			if(k.getFrom()==now && k.getInput()=='\0' && eClosures.find(k.getTo())==eClosures.end()){
				que.push(k.getTo());
				eClosures.insert(k.getTo());
			}
		}
	}
	return eClosures;
}

Set
Graph::getEClosure(Set T)
{
	/** TODO: Implement this function */
	Set eClosures;
	for(int k:T){
		eClosures|=getEClosure(k);
	}
	return eClosures;
}

Set
Graph::move(Set T, char a)
{
	/** TODO: Implement this function */
	Set nextVertex;
	for(Edge k:m_vecEdges){
		if(T.find(k.getFrom())!=T.end()&&k.getInput()==a){
			nextVertex.insert(k.getTo());
		}
	}
	return nextVertex;
}
