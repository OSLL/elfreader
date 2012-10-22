#include <stdio.h>
#include <iostream>
#include <elf.h>
#include <fstream>
int main(int argc, char* argv[])
{

	FILE* file;
	Elf32_Ehdr filehdr;
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
	printf("\n");	
	std::cout << "Header of ELF" << std::endl;
	printf("\n");	
	file = fopen(argv[1], "rb");
	if (file == NULL)
	{
		std::cout << "Error! Can't open the file!" << std::endl;
		return 1;
	}	
	
	fread(&filehdr, sizeof(Elf32_Ehdr), 1, file);
	printf("Magic ");	
	printf("%22s", "");
	std::cout << filehdr.e_ident;
	printf("%12s", "");
	for (int i=0; i < EI_NIDENT; i++)	
		printf("%.2x ", filehdr.e_ident[i]);
	printf("\n");
	std::cout << "File type ";
	printf("%26d", filehdr.e_type);
	switch (filehdr.e_type) {
	        case 0: 
			printf("%15s\n", "NONE");  
			break;
	        case 1: 
			printf("%15s\n", "REL"); 
			break;
	        case 2: 
			printf("%15s\n", "EXEC");  
			break;
	        case 3: 
			printf("%15s\n", "DYN");  
			break;
	        case 4: 
			printf("%15s\n", "CORE");   
			break;
		default: 
			std::cout <<  " Error!" << std::endl; 
			break;
	}

		
	std::cout << "Machine type " ;
	printf("%23d", filehdr.e_machine);
	switch (filehdr.e_machine) {
	        case 0: 
			printf("%14s\n", "NONE");  
			break;
	        case 1: 
			printf("%14s\n", "M32");
			break;
	        case 2: 
			printf("%14s\n", "SPARC"); 
			break;
	        case 3: 
			printf("%14s\n", "386");			
			break;
	        case 4: 
			printf("%14s\n", "68K"); 
			break;
		case 5: 
			printf("%14s\n", "88K");  
			break;
		case 6: 
			printf("%14s\n", "486"); 
			break;
	        case 7: 
			printf("%14s\n", "860");  
			break;
		default: 
			std::cout <<  " Error!" << std::endl; 
			break;
	}

	printf("Version ");
	printf("%27s", "");
	std::cout << filehdr.e_version;
	printf("%#14x\n", filehdr.e_version);
	printf("Adress of enter point");
	printf("%14s", "");
	std::cout << filehdr.e_entry;
	printf("%#12x\n", filehdr.e_entry);
	printf("Flags");
	printf("%30s", "");
	std::cout << filehdr.e_flags;
	printf("%#12x\n", filehdr.e_flags);
		
	std::cout << "Program header table file offset" ; 
	printf("%3s", "");
	std::cout << filehdr.e_phoff; 
	printf("%12d\n", filehdr.e_phoff);	
	std::cout << "Section header table file offset";
	printf("%3s", "");
	std::cout << filehdr.e_shoff; 
	printf("%12d\n", filehdr.e_shoff);
	std::cout << "ELF header size in bytes ";
	printf("%10s", "");
	std::cout << filehdr.e_ehsize;
	printf("%12d\n", filehdr.e_ehsize);	
	std::cout << "Program header table entry size ";
	printf("%3s", "");
	std::cout << filehdr.e_phentsize;
	printf("%12d\n", filehdr.e_phentsize);	
	std::cout << "Program header table entry count ";
	printf("%2s", "");
	std::cout << filehdr.e_phnum; 
	printf("%12d\n", filehdr.e_phnum);	
	std::cout << "Section header table entry size " ;
	printf("%3s", "");
	std::cout << filehdr.e_shentsize;
	printf("%12d\n", filehdr.e_shentsize);	
	std::cout << "Section header table entry count " ;
	printf("%2s", "");
	std::cout << filehdr.e_shnum;
	printf("%12d\n", filehdr.e_shnum);
	std::cout << "Section header string table index ";
	printf("%1s", "");
	std::cout << filehdr.e_shstrndx; 	
	printf("%12d\n", filehdr.e_shstrndx);
	fclose(file);
	printf("\n");
	return 0;
}
