#include <stdio.h>
#include <iostream>
#include <elf.h>
int main(int argc, char* argv[])
{

	FILE* file;
	Elf32_Ehdr* filehdr;
	char* str[1000];
	if (argc > 2)
	{
		std::cout << "Error! Too much arguments!" << std::endl;
		return 1;
	}
	else
		if (argc < 2)
		{	
			std::cout << "Error! Not enough arguments!" << std::endl;
			return 1;
		}	
	std::cout << argv[1] << std::endl;	
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		std::cout << "Error! Can't open the file!" << std::endl;
		return 1;
	}	
	 fscanf(file, "%s\n", &str);
	std::cout << &str <<std::endl; 
	fread(filehdr, sizeof(filehdr), 1, file);
	std::cout << filehdr << std::endl;
	fclose(file);
	return 0;
}
