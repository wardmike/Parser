#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

void print_parse(std::string, int)
{

}

void look_for_keywords(char line[], int pos)
{
	
}

void parse_line(char line[])
{
	for (int i = 0; i < 999 &line[i] != '\0'; ++i)
	{
		if (line[i] == '#') //ignore the comments
		{
			break;
		}
		
		std::cout << line[i] << " ";
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

