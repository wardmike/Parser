#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>

class LexialAnalyzer
{
public:
	void print_parse(std::string, int);
	int punctuation_check(char*);
	int word_length(char*);
	int keyword_check(std::string);
	int string_check(char*);
	void parse_line(char*);
	void read_file(std::string);
	int find_literal(char*);
	int find_boolean(std::string);
	int find_number(std::string);
	LexialAnalyzer(std::string);
private:
	std::ofstream* fout;
};