#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

void print_parse(std::string, int)
{

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

int look_for_keywords(char* c)
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
		else if (line[i] != ' ')
		{
			std::cout << word_length(&line[i]) << std::endl;
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

