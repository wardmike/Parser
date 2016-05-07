#include <fstream>
#include <iostream>

#include "syntaxanalyzer.h"

std::string SyntaxAnalyzer::getWord(char w[])
{
	int i = 0;
	bool capture = false;
	std::string x;
	while (w[i] != '\0')
	{
		if (capture)
		{
			if (w[i] == '"') //we're done
			{
				return x;
			}
			else //capture the letter
			{
				std::cout << w[i] << std::endl;
				x.push_back(w[i]);
				printf("%s\n", x);
				
			}
		}
		else
		{
			if (w[i] == '"') //reach the first quote
			{
				capture = true;
			}
		}
		++i;
	}
	return x;
}


SyntaxAnalyzer::SyntaxAnalyzer(std::string filename)
{
	std::ifstream fin;
	fin.open(filename);
	if (fin.is_open())
	{
		int lineTypes[100]; //0 for whitespace, 1 for ID, 2 for LIT, 3 for KEYWORD, 4 for DELIMITER, 5 for OPERATOR
		std::string lineVals[100];
		int iterator = 0;
		while (!fin.eof())
		{
			char line[1000];
			fin.getline(line, 999);
			if (line[1] == 'W')
			{
				lineTypes[iterator] = 0;
				lineVals[iterator] = getWord(line);
			}
			else if (line[1] == 'I')
			{
				lineTypes[iterator] = 1;
				lineVals[iterator] = getWord(line);
			}
			else if (line[1] == 'L')
			{
				lineTypes[iterator] = 2;
				lineVals[iterator] = getWord(line);
			}
			else if (line[1] == 'K')
			{
				lineTypes[iterator] = 3;
				lineVals[iterator] = getWord(line);
			}
			else if (line[1] == 'D')
			{
				lineTypes[iterator] = 4;
				lineVals[iterator] = getWord(line);
			}
			else if (line[1] == 'O')
			{
				lineTypes[iterator] = 5;
				lineVals[iterator] = getWord(line);
			}
			else
			{
				lineTypes[iterator] = 6;
				lineVals[iterator] = getWord(line);
			}
			std::string ln(line);
			if (ln == "(PUNCT \"\\n\")")
			{
				lineTypes[iterator] = -1;
				int z = 0;
				while (lineTypes[z] != -1)
				{
					if (lineTypes[z] == 0)
					{
						//std::cout << "<whitespace> ";
					}
					else if (lineTypes[z] == 1)
					{
						std::cout << "<id> ";
						printf("%s ", lineVals[z]);
					}
					else if (lineTypes[z] == 2)
					{
						std::cout << "<literal> ";
						printf("%s ", lineVals[z]);
					}
					else if (lineTypes[z] == 3)
					{
						std::cout << "<keyword> ";
						printf("%s ", lineVals[z]);
					}
					else if (lineTypes[z] == 4)
					{
						std::cout << "<delimiter> ";
						printf("%s ", lineVals[z]);
					}
					else if (lineTypes[z] == 5)
					{
						std::cout << "<operator> ";
						printf("%s ", lineVals[z]);
					}
					else if (lineTypes[z] == 6)
					{
						std::cout << "<other> ";
						printf("%s ", lineVals[z]);
					}
					++z;
				}
				std::cout << std::endl;
				iterator = 0;
			}
			else
			{
				lineVals[iterator] = ln;
				++iterator;
			}
			
		}
	}
	else
	{
		std::cout << "Could not open file.\n";
	}
}