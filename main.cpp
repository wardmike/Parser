/*
Michael Ward A01755332
Robert Jacobson A01386891
Kris Mygrant A01962860
*/

#include "lexicalanalyzer.h"


int main(int argc, char* argv[])
{
	printf("Enter the filename: ");
	std::string filename;
	std::cin >> filename;
	LexialAnalyzer* la = new LexialAnalyzer("output.txt");
	la->read_file(filename);
	//SyntaxAnalyzer* sa = new SyntaxAnalyzer();
}


/*
Michael Ward A01755332
Robert Jacobson A01386891
Kris Mygrant A01962860
*/