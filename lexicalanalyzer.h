/*
Michael Ward A01755332
Robert Jacobson A01386891
Kris Mygrant A01962860
*/


#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>

class LexialAnalyzer
{
public:
	void print_parse(int, std::string);
	int punctuation_check(char*);
	int word_length(char*);
	int keyword_check(std::string);
	int string_check(char*);
	void parse_line(char*);
	void read_file(std::string);
	int find_literal(char*);
	int find_boolean(std::string);
	int find_number(std::string);
	void print_parse_whitespace(int, int);
	LexialAnalyzer(std::string);
	int punctuation_length(char *c);
	int punctuation_valid(std::string);
	bool valid_id(std::string);
	
private:
	std::ofstream* fout;
	int whiteCount;
	bool comment = false;
};

/*
Michael Ward A01755332
Robert Jacobson A01386891
Kris Mygrant A01962860
*/