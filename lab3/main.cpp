#include "Graph.h"
#include<algorithm>

int
main(int argc, char* argv[])
{
	Graph NFA;			/**< The input NFA. */
	Graph DFA;			/**< The output DFA. */
	char sigma[] = {'a', 'b'};	/**< The set of possible inputs. */
	vector<Set> Dstate;		/**< The set of states in DFA. */
	int T = 0;			/**< The state number in DFA. */

	if(argc<2) {
		cerr<<"Usage : "<<argv[0]<<" <input file>"<<endl;
		return 1;
	}

	NFA.readFile(argv[1]);
	Dstate.push_back(NFA.getEClosure(0));

	/** TODO: Implement the subset construction algorithm. */
	while(T<Dstate.size()){
		for(char a : sigma){
			Set U=NFA.getEClosure(NFA.move(Dstate[T],a));
			if(find(Dstate.begin(),Dstate.end(),U)==Dstate.end()){
				Dstate.push_back(U);
			}
			DFA.insertEdge(T,find(Dstate.begin(),Dstate.end(),U)-Dstate.begin(),a);
		}
		T++;
	}
	for(Set k:Dstate){
		cout<<k;
	}
	cout<<DFA;
	return 0;
}
