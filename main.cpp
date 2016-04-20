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
	else if (val == 2)
	{
		result = "(PUNCT \"" + word + "\")";
	}
	std::cout << result << std::endl;
}

int punctuation_check(char* c)
{
	if (*c == '=' && *(c + 1) == '=')
	{
		return 1;
	}
	else if (*c == ':' || *c == '-' || *c == '+' || *c == '*' || *c == '/'
		|| *c == '(' || *c == ')')
	{
		return 1;
	}
	return -1;
}

int word_length(char* c)
{
	int len = 0;
	while (*(c + len) != ' ' && *(c + len) != '\0' && punctuation_check(&(*(c + len))) == -1)
	{
		++len;
	}
	return len;
}

int keyword_check(std::string word)
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
		return 1;
	}
	return -1;
}

int string_check(char* c)
{
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
		}
		else if (int x = punctuation_check(&line[i]) != -1)
		{
			if (x == 1)
			{
				char d[2] = { line[i], '\0' };
				print_parse(std::string(d), 2);
			}
			else if (x == 2)
			{
				char d[3] = { line[i], line[i + 1], '\0' };
				print_parse(std::string(d), 2);
			}
		}
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
			keyword_check(wordstr);
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

