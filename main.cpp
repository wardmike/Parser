#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

void print_parse(std::string word, int val)
{
	std::string result;
	if (val == 1) //it's a keyword
	{
		result = "(KEYWORD " + word + ")";
	}
	std::cout << result << std::endl;
}

int word_length(char* c)
{
	int len = 0;
	while (*(c + len) != ' ' && *(c + len) != '\0')
	{
		++len;
	}
	return len;
}

int look_for_keywords(std::string word)
{
	if (word == "and" || word == "as" || word == "assert" || word == "break" || word == "class"
		|| word == "continue" || word == "def" || word == "del" || word == "elif" || word == "else"
		|| word == "except" || word == "exec" || word == "finally" || word == "for" || word == "from"
		|| word == "global" || word == "if" || word == "import" || word == "in" || word == "is"
		|| word == "lambda" || word == "not" || word == "or" || word == "pass" || word == "print"
		|| word == "raise" || word == "return" || word == "try" || word == "while" || word == "with"
		|| word == "yield")
	{
		print_parse(word, 1);
	}
	//check to see if it's a keyword
	//if it is, call print parse to print, return 1
	//if not, return -1
	return -1;
}

void parse_line(char line[])
{
	for (int i = 0; i < 999 &line[i] != '\0'; ++i)
	{
		if (line[i] == '#') //ignore the comments
		{
			break;
		}
		if (line[i] == '	' || line[i] == '    ') //char is a tab
		{
			std::cout << "tab!\n";
		} //add check for punctuation
		else if (line[i] != ' ')
		{
			int len = word_length(&line[i]);
			std::cout << len << std::endl;
			//make the word
			char* word = new char[len + 1];
			for (int w = 0; w < len; ++w)
			{
				word[w] = line[i + w];
			}
			word[len] = '\0';
			std::string wordstr(word);
			look_for_keywords(wordstr);
			i += word_length(&line[i]) - 1;
		}
	}
	printf("\n");
}


void read_file(std::string filename)
{
	std::ifstream fin;
	fin.open(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			char line[1000];
			fin.getline(line, 999);
			parse_line(line);
		}
	}
}


int main(int argc, char* argv[])
{
	printf("Enter the filename: ");
	std::string filename;
	std::cin >> filename;
	read_file(filename);
}

