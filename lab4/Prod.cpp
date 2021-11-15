#include "Prod.h"
#include <fstream>
#include <bits/stdc++.h>

void
Prod::readFile(const char* in)
{
	ifstream infile(in);	/**< Input file stream. */
	string line;		/**< One line of the file. */

	while(getline(infile, line)) {
		/** Split a line. */
		stringstream chk(line);
		vector<string> tokens;
		string inter;
		while(getline(chk, inter, ' '))
			tokens.push_back(inter);

		/** Create an edge for a line. */
		if(tokens.size() == 1) {
			m_vecRules.push_back( pair<char, string>(tokens[0][0], string("")) );
		} else if(tokens.size() == 2) {
			m_vecRules.push_back( pair<char, string>(tokens[0][0], tokens[1]) );
		} else {
			cout<<"Format error"<<endl;
			exit(0);
		}
	}
}

void
Prod::print(ostream& os) const
{
	for(int i=0; i<m_vecRules.size(); i++) {
		cout << m_vecRules[i].first;
		cout << " => ";
		cout << m_vecRules[i].second;
		cout << endl;
	}
}

void
Prod::computeFirst(void)
{
	for(int i=0; i<m_vecRules.size(); i++) {
		cout << "FIRST(";
		cout << m_vecRules[i].second;
		cout << ") = ";
		cout << getFirst(m_vecRules[i].second);
	}	
}

void
Prod::computeFollow(void)
{
	Set nonterminal;
	for(int i=0; i<m_vecRules.size(); i++)
		nonterminal.insert(m_vecRules[i].first);
	for(Set::iterator it=nonterminal.begin(); it!=nonterminal.end(); ++it) {
		cout << "FOLLOW(";
		cout << *it;
		cout << ") = ";
		cout << getFollow(*it);
	}
}

Set
Prod::getFirst(string a)
{
	/** TODO: Implement this function. */
	Set ret;
	if(a.size()==0){
		ret.insert('\0');
		return ret;
	}
	for(int i=0;i<a.size();i++){
		if(isNonterminal(a[i])){
			Set tmp;
			for(auto k:m_vecRules){
				if(a[i]==k.first){
					tmp|=getFirst(k.second);
				}
			}
			if(tmp.find('\0')==tmp.end()){
				ret|=tmp;
				break;
			}
			else{
				if(i!=a.size()-1){
					tmp.erase('\0');
				}
				ret|=tmp;
			}
		}
		else{
			ret.insert(a[i]);
			break;
		}
	}
	return ret;
}

Set
Prod::getFollow(char A)
{
	/** TODO: Implement this function. */
	Set ret;
	for(auto k:m_vecRules){
		for(int i=0;i<k.second.size();i++){
			if(A==k.second[i]){
				if(i!=k.second.size()-1){
					Set tmp=getFirst(k.second.substr(i+1));
					if(tmp.find('\0')!=tmp.end()){
						if(A!=k.first){
							ret|=getFollow(k.first);
						}
						tmp.erase('\0');
					}
					ret|=tmp;
				}
				else{
					if(A!=k.first){
						ret|=getFollow(k.first);
					}
				}

			}
		}
	}
	if(A==m_vecRules[0].first){
		ret.insert('$');
	}
	return ret;
}
