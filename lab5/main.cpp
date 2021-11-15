#include "Parser.h"
#include "Prod.h"

int
main(int argc, char* argv[])
{
	Prod P;
	Parser LL;

	if(argc<2) {
		cerr<<"Usage : "<<argv[0]<<" <input file>"<<endl;
		return 1;
	}

	P.readFile(argv[1]);
	cout<<P;

	LL.initTable(&P);
	LL.printTable(cout);

	return 0;
}
