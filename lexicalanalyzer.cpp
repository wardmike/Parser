/*
Michael Ward A01755332
Robert Jacobson A01386891
Kris Mygrant A01962860
*/

#include "lexicalanalyzer.h"

LexialAnalyzer::LexialAnalyzer(std::string filename)
{
	this->fout = new std::ofstream();
	fout->open(filename);
}

void LexialAnalyzer::print_parse_whitespace(int val, int count = 0)
{
	std::string result;
	if (val == 1) //it's whitespace
	{
		if (count > 0)
		{
			result = "(WHITESPACE " + count + ')';
			std::cout << "(WHITESPACE " << count << ")\n";
		}
	}
	if (val == 2) //it's a tab
	{
		result = "(WHITESPACE TAB)";
		std::cout << result << std::endl;
	}
	//*(this->fout) << result << std::endl;
}

bool LexialAnalyzer::valid_id(std::string word)
{
	if (isalpha(word[0]) || (word[0] == '_' && word[1] == '_' && word[2] != '_'))
	{
		for (int i = 0; i < word.length(); ++i)
		{
			if (word[i] != '_' && !(isalnum(word[i])))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void LexialAnalyzer::print_parse(int val, std::string word = "")
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
	else if (val == 5)
	{
		result = "(ERROR - \"" + word + "\" invalid punctuation)";
	}
	else if (val == 6)
	{
		result = "(OPERATOR \"" + word + "\")";
	}
	else if (val == 7)
	{
		result = "(DELIMITER \"" + word + "\")";
	}
	else if (val == 8)
	{
		result = "(ERROR - \"" + word + "\" is an invalid phrase)";
	}
	std::cout << result << std::endl;
	//*(this->fout) << result << std::endl;
}

int LexialAnalyzer::find_literal(char* c)
{
	int len = 1;
	bool go = true;
	while (go)
	{
		if (*(c + len) == '"' && *(c + len - 1) != '\\')
		{
			go = false;
			break;
		}
		else
		{
			++len;
		}
	}
	return len;
}

int LexialAnalyzer::find_boolean(std::string c)
{
	if (c == "True" || c == "False") //it's a boolean
	{
		return 1;
	}
	else
	{
		return -1; //it's not a boolean
	}
}

int LexialAnalyzer::find_number(std::string c)
{
	bool period = false;
	bool e = false;
	bool j = false;
	int len = c.length();
	for (int i = 0; i < len; ++i)
	{
		if (c[i] == 'e' || c[i] == 'E')
		{
			if (e) //we've already had an e
			{
				return -1;
			}
			e = true;
		}
		if (c[i] == '.')
		{
			if (period) //we've already had a period
			{
				return -1;
			}
			period = true;
		}
		if (c[i] == 'j' || c[i] == 'J')
		{
			if (j) //we've already had a j
			{
				return -1;
			}
			j = true;
		}
		if ((c[i] == '-' && c[i] == '+') && i > 0)
		{
			if (c[i - 1] != 'e' || c[i - 1] != 'E')
			{
				return -1;
			}
		}
		if (!std::isdigit(c[i]) && c[i] != '-' && c[i] != 'E' && c[i] != '+' &&c[i] != '.' && c[i] != 'J' && c[i] != 'j' && c[i] != 'e' && c[i] != '\0')
		{
			return -1;
		}
	}
	return 1;
}

int LexialAnalyzer::punctuation_check(char* c)
{
	if (*c == '\"') //if it's a quote
	{
		return 3;
	}
	else if (*c == '.')
	{
		if (this->whiteCount > 0)
		{
			if (isdigit(*(c - 1)))
			{
				return -1;
			}
		}
		 if ( isdigit(*(c + 1)))
		{
			return -1; //period is part of a number
		}
	}
	else if (*c == '-' || *c == '+')
	{
		if (this->whiteCount > 0)
		{
			if (*(c - 1) == 'e' || *(c - 1) == 'E')
			{
				return -1;
			}
		}
	}
	else if (isalnum(*c) || *c == ' ' || *c == '\t' || *c == '\0' || *c == '_') //it's a letter or number or invalid
	{
		return -1;
	}
	else if (*c == '$' || *c == '?' || *c == '`') //bad punctuation
	{
		print_parse(5, std::string(c));
		return -1;
	}
	else
	{
		return 1;
	}
}

int LexialAnalyzer::punctuation_valid(std::string word)
{
	if (word == "+" || word == "-" || word == "*" || word == "**" || word == "/" || word == "//" || word == "%" || word == "@"
		|| word == "<<" || word == ">>" || word == "&" || word == "|" || word == "^" || word == "~" || word == "<" 
		|| word == ">" || word == "<=" || word == ">=" || word == "==" || word == "!=")
	{
		return 1; //operator
	}
	else if (word == "(" || word == ")" || word == "[" || word == "]" || word == "{" || word == "}" || word == ","
		|| word == ":" || word == "." || word == ";" || word == "@" || word == "=" || word == "->" || word == "+="
		|| word == "-=" || word == "*=" || word == "/=" || word == "//=" || word == "%=" || word == "@=" || word == "&="
		|| word == "|=" || word == "^=" || word == ">>=" || word == "<<=" || word == "**=")
	{
		return 2; // it's a delimiter
	}
	else
	{
		return -1;
	}
}

int LexialAnalyzer::punctuation_length(char* c)
{
	int len = 0;
	if (*c == '(' || *c == ')' || *c == '[' || *c == ']' || *c == '{' || *c == '}')
	{
		return 1;
	}
	while (*(c + len) != ' ' && *(c + len) != '\t' && *(c + len) != '\0' && punctuation_check(&(*(c + len))) != -1
		&& *(c + len) != '(' && *(c + len) != ')' && *(c + len) != '[' && *(c + len) != ']' && *(c + len) != '{' && *(c + len) != '}')
	{
		++len;
	}
	return len;
}

int LexialAnalyzer::word_length(char* c)
{
	int len = 0;
	while (*(c + len) != ' ' && *(c + len) != '\t' && *(c + len) != '\0' && punctuation_check(&(*(c + len))) == -1)
	{
		++len;
	}
	return len;
}

int LexialAnalyzer::keyword_check(std::string word)
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
	else
	{
		return -1;
	}
}

int LexialAnalyzer::string_check(char* c)
{
	return -1;
}

void LexialAnalyzer::parse_line(char line[])
{
	bool whitespace = true;
	this->whiteCount = 0;
	for (int i = 0; i < 999 & line[i] != '\0'; ++i)
	{
		if (this->comment)
		{
			if (line[i] == '\'' && line[i + 1] == '\'' && line[i + 2] == '\'')
			{
				this->comment = false;
				i += 2;
				continue;
			}
		}
		else
		{
			if (line[i] == '\'' && line[i + 1] == '\'' && line[i + 2] == '\'')
			{
				this->comment = true;
				i += 2;
				continue;
			}
			else if (whitespace)
			{
				if (line[i] == ' ') //blank space
				{
					++whiteCount;
				}
				else if (line[i] == '	') //tab
				{
					print_parse_whitespace(1, whiteCount);
					whiteCount = 0;
					print_parse_whitespace(2);
				}
				else //end of whitespace
				{
					print_parse_whitespace(1, whiteCount);
					whitespace = false;
					--i; //check the same character again
				}
			}
			else
			{
				int x = punctuation_check(&line[i]);
				if (line[i] == '#') //ignore the comments
				{
					break;
				}
					if (x != -1)
					{
						if (x == 3) //it's a word in quotes
						{
							int q = find_literal(&line[i]);
							char *d = new char[q - 1];
							for (int w = 1; w < q; ++w)
							{
								d[w - 1] = line[i + w];
							}
							d[q - 1] = '\0';
							i += q;
							print_parse(4, std::string(d));
						}
						else
						{
							int len = punctuation_length(&line[i]);
							if (len > 0)
							{
								//make the word
								char* word = new char[len + 1];
								for (int w = 0; w < len; ++w)
								{
									word[w] = line[i + w];
								}
								word[len] = '\0';
								std::string wordstr(word);
								int y = punctuation_valid(wordstr);
								if (y == 1)
								{
									print_parse(6, wordstr); //operator
								}
								else if (y == 2)
								{
									print_parse(7, wordstr); //delimiter
								}
								else if (y == -1)
								{
										print_parse(5, wordstr); //invalid punctuation
								}
								i += len - 1;
							}
						}
					}
					else if (line[i] != ' ') // it's a word not in quotes
					{
						int len = word_length(&line[i]);
						if (len > 0)
						{
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
								print_parse(1, wordstr);
							}
							else if (find_boolean(wordstr) == 1) //it's a boolean
							{
								print_parse(4, wordstr);
							}
							else if (find_number(wordstr) == 1) //it's a number
							{
								print_parse(4, wordstr);
							}
							else // it's an ID
							{
								if (valid_id(wordstr))
								{
									print_parse(3, wordstr);
								}
								else
								{
									print_parse(8, wordstr);
								}
							
							}
							i += len - 1;
						}
					
					}
			}
		}
	}
	if (!this->comment)
	{
		print_parse(2, "\\n");
	}
}


void LexialAnalyzer::read_file(std::string filename)
{
	std::ifstream fin;
	for (int i = 0; i < filename.length(); ++i)
	{
		if (filename[i] == '.')
		{
			if (filename[i + 1] != 'p' || filename[i + 2] != 'y' || filename[i + 3] != '\0')
			{
				std::cout << "Please enter the path to a valid Python file.\n";
				return;
			}
		}
	}
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
	else
	{
		std::cout << "Could not open file.\n";
	}
}

/*
Michael Ward A01755332
Robert Jacobson A01386891
Kris Mygrant A01962860
*/