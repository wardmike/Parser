#include "lexicalanalyzer.h"
#include "syntaxanalyzer.h"


int main(int argc, char* argv[])
{
	printf("Enter the filename: ");
	std::string filename;
	std::cin >> filename;
	LexialAnalyzer* la = new LexialAnalyzer("output.txt");
	la->read_file(filename);
	//SyntaxAnalyzer* sa = new SyntaxAnalyzer();
}
