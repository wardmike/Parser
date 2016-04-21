#include "parser.h"


void Parser::print_parse(std::string word, int val)
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
	else if (val == 3)
	{
		result = "(ID \"" + word + "\")";
	}
	else if (val == 4)
	{
		result = "(LIT \"" + word + "\")";
	}
	std::cout << result << std::endl;
}

int Parser::find_literal(char* c)
{
	int len = 1;
	while (*(c + len) != '"')
	{
		++len;
	}
	return len;
}

int Parser::punctuation_check(char* c)
{
	if (*c == '=' && *(c + 1) == '=')
	{
		return 2;
	}
	else if (*c == '\"')
	{
		return 3;
	}
	else if (*c == ':' || *c == '-' || *c == '+' || *c == '*' || *c == '/'
		|| *c == '(' || *c == ')' || *c == '=')
	{
		return 1;
	}
	return -1;
}

int Parser::word_length(char* c)
{
	int len = 0;
	while (*(c + len) != ' ' && *(c + len) != '\0' && punctuation_check(&(*(c + len))) == -1)
	{
		++len;
	}
	return len;
}

int Parser::keyword_check(std::string word)
{
	if (word == "and" || word == "as" || word == "assert" || word == "break" || word == "class"
		|| word == "continue" || word == "def" || word == "del" || word == "elif" || word == "else"
		|| word == "except" || word == "exec" || word == "finally" || word == "for" || word == "from"
		|| word == "global" || word == "if" || word == "import" || word == "in" || word == "is"
		|| word == "lambda" || word == "not" || word == "or" || word == "pass" || word == "print"
		|| word == "raise" || word == "return" || word == "try" || word == "while" || word == "with"
		|| word == "yield")
	{
		return 1;
	}
	return -1;
}

int Parser::string_check(char* c)
{
	return -1;
}

void Parser::parse_line(char line[])
{
	for (int i = 0; i < 999 & line[i] != '\0'; ++i)
	{
		int x = punctuation_check(&line[i]);
		if (line[i] == '#') //ignore the comments
		{
			break;
		}
		if (line[i] == '	' || line[i] == '    ') //char is a tab
		{
			//do tab stuff
		}
		else if (x != -1)
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
				++i;
			}
			else if (x == 3)
			{
				int q = find_literal(&line[i]);;
				char *d = new char[q];
				for (int w = 1; w < q; ++w)
				{
					d[w - 1] = line[i + w];
				}
				d[q] = '\0';
				i += q + 1;
				print_parse(std::string(d), 4);
			}
		}
		else if (line[i] != ' ')
		{
			int len = word_length(&line[i]);
			//make the word
			char* word = new char[len + 1];
			for (int w = 0; w < len; ++w)
			{
				word[w] = line[i + w];
			}
			word[len] = '\0';
			std::string wordstr(word);
			if (keyword_check(wordstr) == 1) //it's a keyword
			{
				print_parse(wordstr, 1);
			}
			else // it's an ID
			{
				print_parse(wordstr, 3);
			}
			i += word_length(&line[i]) - 1;
		}
	}
}


void Parser::read_file(std::string filename)
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