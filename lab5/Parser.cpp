#include "Parser.h"
#include "Prod.h"

Parser::~Parser()
{
	for(int i=0; i<m_pProd->getNonTerminalSize(); i++)
		delete [] M[i];
	delete [] M;
}

void
Parser::printTable(ostream& os)
{
	for(int i=0; i<m_pProd->getNonTerminalSize(); i++)
		for(int j=0; j<m_pProd->getTerminalSize(); j++)
			if(M[i][j]) {
				cout<<"M[";
				cout<<m_pProd->getNonTerminalSymbol(i);
				cout<<"][";
				cout<<m_pProd->getTerminalSymbol(j);
				cout<<"] ";
				cout<<M[i][j]->first;
				cout<<" => ";
				cout<<M[i][j]->second;
				cout<<endl;
			}
}

void
Parser::initTable(Prod* prod)
{
	m_pProd = prod;
	M = new pair<char, string>**[prod->getNonTerminalSize()];
	for(int i=0; i<prod->getNonTerminalSize(); i++) {
		M[i] = new pair<char, string>*[prod->getTerminalSize()];
		for(int j=0; j<prod->getTerminalSize(); j++)
			M[i][j] = NULL;
	}

	for(int i=0;i<prod->getRuleSize();i++){
		char A=prod->getRule(i)->first;
		string alpha=prod->getRule(i)->second;
		Set first_alpha=prod->getFirst(alpha);
		for(char a:first_alpha){
			if(a!='\0'){
				M[prod->getNonTerminalIndex(A)][prod->getTerminalIndex(a)]=prod->getRule(i);
			}
		}
		if(first_alpha.find('\0')!=first_alpha.end()){
			for(char b:prod->getFollow(A)){
				if(b!='\0'){
					M[prod->getNonTerminalIndex(A)][prod->getTerminalIndex(b)]=prod->getRule(i);
				}
			}
		}
	}
	/** TODO: Implement this function. */
}
