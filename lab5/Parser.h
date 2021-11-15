#ifndef	__PARSER_H__
#define	__PARSER_H__

#include <iostream>
#include <utility>
#include <string>
using namespace std;
class Prod;

/**
 * A class to implement the LL(1) parser from the given production rules.
 */
class Parser
{
public:
	/**
	 * An empty constructor.
	 */
	Parser() {}
	/**
	 * A destructor.
	 */
	~Parser();
	/**
	 * Initialize the parsing table from the given production rules.
	 *
	 * @param prod	Production rules;
	 */
	void initTable(Prod* prod);

        /**
         * Print the parsing table
         *
         * @param os    The output stream the table is printed to.
         */
	void printTable(ostream& os);

protected:
	/** A pointer to the production rules. */
	Prod* m_pProd;
	/** The parsing table. */
	pair<char, string>*** M;
};

#endif
