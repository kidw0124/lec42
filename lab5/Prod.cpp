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
			if(isNonTerminal(tokens[0][0])) {
				m_setNonTerminal.insert(tokens[0][0]);
			} else {
				cout<<"Format error"<<endl;
				exit(0);
			}
			m_vecRules.push_back( pair<char, string>(tokens[0][0], string("")) );
		} else if(tokens.size() == 2) {
			if(isNonTerminal(tokens[0][0])) {
				m_setNonTerminal.insert(tokens[0][0]);
			} else {
				cout<<"Format error"<<endl;
				exit(0);
			}
			for(int i=0; i<tokens[1].size(); i++)
				if(isNonTerminal(tokens[1][i]))
					m_setNonTerminal.insert(tokens[1][i]);
				else
					m_setTerminal.insert(tokens[1][i]);
			m_vecRules.push_back( pair<char, string>(tokens[0][0], tokens[1]) );
		} else {
			cout<<"Format error"<<endl;
			exit(0);
		}
	}
	m_setTerminal.insert('$');
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
	Set ret;
	bool found_e = false;

	for(int i=0; i<a.size(); i++) {
		Set tmp = getFirst(a[i]);
		Set::iterator e = tmp.find(0);
		if(e == tmp.end()) {
			ret |= tmp;
			found_e = true;
			break;
		}
		tmp.erase(e);
		ret |= tmp;
	}
	if(!found_e)
		ret.insert(0);
	return ret;
}

Set
Prod::getFirst(char A)
{
	Set ret;
	if(!isNonTerminal(A)) {
		ret.insert(A);
		return ret;
	}
	for(int i=0; i<m_vecRules.size(); i++)
		if(m_vecRules[i].first==A)
			ret |= getFirst(m_vecRules[i].second);
	return ret;
}

Set
Prod::getFollow(char A)
{
	Set ret;

	for(int i=0; i<m_vecRules.size(); i++) {
		string rule = m_vecRules[i].second;
		for(int j=0; j<rule.size(); j++)
			if(rule[j] == A) {
				if(j < rule.size()-1) {
					Set tmp = getFirst(rule.substr(j+1));
					if(tmp.find(0)!=tmp.end()) {
						tmp.erase(0);
						if(m_vecRules[i].first != A)
							ret |= getFollow(m_vecRules[i].first);
					}
					ret |= tmp;
				} else {
					if(m_vecRules[i].first != A)
						ret |= getFollow(m_vecRules[i].first);
				}
			}
		}
	if(A == m_vecRules[0].first)
		ret.insert('$');

	return ret;
}

int
Prod::getNonTerminalIndex(char A)
{
	int index = 0;
	for(Set::iterator it=m_setNonTerminal.begin(); it!=m_setNonTerminal.end(); ++it) {
		if((*it) == A)
			return index;
		index++;
	}
	return -1;
}

int
Prod::getTerminalIndex(char a)
{
	int index = 0;
	for(Set::iterator it=m_setTerminal.begin(); it!=m_setTerminal.end(); ++it) {
		if((*it) == a)
			return index;
		index++;
	}
	return -1;
}

char
Prod::getNonTerminalSymbol(int index)
{
	int i = 0;
	for(Set::iterator it=m_setNonTerminal.begin(); it!=m_setNonTerminal.end(); ++it) {
		if(i == index)
			return *it;
		i++;
	}
	return 0;
}

char
Prod::getTerminalSymbol(int index)
{
	int i  = 0;
	for(Set::iterator it=m_setTerminal.begin(); it!=m_setTerminal.end(); ++it) {
		if(i == index)
			return *it;
		i++;
	}
	return 0;
}
