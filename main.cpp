#include "parser.h"

int main(int argc, char* argv[])
{
	printf("Enter the filename: ");
	std::string filename;
	std::cin >> filename;
	Parser* parser = new Parser();
	parser->read_file(filename);
}

