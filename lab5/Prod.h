#ifndef	__PROD_H__
#define	__PROD_H__

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "Set.h"
using namespace std;

/**
 * A class to manage production rules.
 */
class Prod {
public:
	/**
	 * An empty constructor.
	 */
	Prod() {};
	/**
	 * A constructor reading an input file.
	 *
	 * @param in	The input file name.
	 */
	Prod(const char* in) { readFile(in); }

	/**
	 * Read an input file.
	 *
	 * @param in	The input file name. Each line of the file represents a rule.
	 *		The format of a rule is "L R" which means a derivation L=>R.
	 *		All tokens are single characters.
	 *		Captial letters are non-terminals and others are terminals.
	 *		Epsilon is denoted by an empty string.
	 */
	void readFile(const char* in);

        /**
         * Print all production rules.
         *
         * @param os    The output stream the rules are printed to.
         */
	void print(ostream& os) const;
	/**
	 * The overloaded operator to print the rules.
	 */
	friend ostream& operator<<(ostream& os, const Prod& prod) { prod.print(os); return os; }


	/**
	 * Compute FIRST of production rules.
	 * This function is only for testing getFirst.
	 */
	void computeFirst(void);
	/**
	 * Compute FOLLOW of production rules.
	 * This function is only for testing getFollow.
	 */
	void computeFollow(void);

	/**
	 * Get FIRST of the given string.
	 *
	 * @param a	The right-hand string of the production rule.
	 * @return	FIRST(a).
	 */
	Set getFirst(string a);
	/**
	 * Get FIRST of the given character.
	 *
	 * @param A	The terminal or non-terminal character.
	 * @return	FIRST(A).
	 */
	Set getFirst(char A);
	/**
	 * Get FOLLOW of the given non-terminal.
	 *
	 * @param A	The non-terminal character.
	 * @return	FOLLOW(A).
	 */
	Set getFollow(char A);

	/**
	 * Get the number of non-terminals.
	 *
	 * @return	The number of non-terminals.
	 */
	int getNonTerminalSize(void) { return m_setNonTerminal.size(); }
	/**
	 * Get the number of terminals.
	 *
	 * @return	The number of terminals.
	 */
	int getTerminalSize(void) { return m_setTerminal.size(); }
	/**
	 * Get the index of the non-terminal.
	 *
	 * @param A	The non-terminal.
	 * @return	The index of the non-terminal.
	 */
	int getNonTerminalIndex(char A);
	/**
	 * Get the index of the terminal.
	 *
	 * @param a	The terminal.
	 * @return	The index of the terminal.
	 */
	int getTerminalIndex(char a);
	/**
	 * Get the non-terminal symbol at the index.
	 *
	 * @param index	The index of the non-terminal.
	 * @return	The symbol of the non-terminal.
	 */
	char getNonTerminalSymbol(int index);
	/**
	 * Get the terminal symbol at the index.
	 *
	 * @param index	The index of the terminal.
	 * @return	The symbol of the terminal.
	 */
	char getTerminalSymbol(int index);
	/**
	 * Get the number of production rules.
	 *
	 * @return	The number of production rules.
	 */
	int getRuleSize(void) { return m_vecRules.size(); }
	/**
	 * Get a rule at the index.
	 *
	 * @param index	The index of the rule.
	 * @return	The rule at the index.
	 */
	pair<char, string>* getRule(int index) { return &(m_vecRules[index]); }
	

protected:
	/** Production rules. */
	vector< pair<char, string> > m_vecRules;
	/** A set of non-terminals found in the given grammar. */
	Set m_setNonTerminal;
	/** A set of terminals found in the given grammar. */
	Set m_setTerminal;

	/**
	 * Check whether the character is non-terminal or not.
	 *
	 * @param n	The character.
	 * @return	True if the character is captial meaning it is a non-terminal.
	 *		False otherwise.
	 */
	inline bool isNonTerminal(char n) { return ('A'<=n && n<='Z'); }
};

#endif
