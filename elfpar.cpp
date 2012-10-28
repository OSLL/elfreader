#include <stdio.h>
#include <iostream>
#include <elf.h>
#include <fstream>
int main(int argc, char* argv[])
{

	FILE* file;
	Elf32_Ehdr filehdr;
	Elf32_Shdr sechdr;
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
			printf("%14s\n", "NO MACHINE");  
			break;
	        case 1: 
			printf("%14s\n", "AT&T WE 32100");
			break;
	        case 2: 
			printf("%14s\n", "SPARC"); 
			break;
	        case 3: 
			printf("%14s\n", "Intel 80386");			
			break;
	        case 4: 
			printf("%14s\n", "MOTOROLA 68000"); 
			break;
		case 5: 
			printf("%14s\n", "MOTOROLA 88000");  
			break;
		case 7: 
			printf("%14s\n", "INTEL 80860"); 
			break;
	        case 8: 
			printf("%14s\n", "MIPS RS3000");  
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
	printf("\n");

	int position = filehdr.e_shoff + filehdr.e_shstrndx*filehdr.e_shentsize;
	fseek(file, position, SEEK_SET);
	fread(&sechdr, sizeof(Elf32_Shdr), 1, file);
	int offset = sechdr.sh_offset;
	char* sectab;
	sectab = new char[sechdr.sh_size];
	fseek(file, sechdr.sh_offset, SEEK_SET);
	fread(sectab, sechdr.sh_size, 1, file);
	position = filehdr.e_shoff;
	printf("\n                  Section information\n");
	for (int i=0; i < filehdr.e_shnum; i++)
	{
		fseek(file, position, SEEK_SET);
		fread(&sechdr, sizeof(Elf32_Shdr), 1, file);
		fseek(file, offset + sechdr.sh_name, SEEK_SET);
		printf("%20s %#12x %#12x %12d\n", sectab + sechdr.sh_name, sechdr.sh_addr, sechdr.sh_offset, sechdr.sh_size);
		position = position + filehdr.e_shentsize;
	}
	delete [] sectab;	
	fclose(file);	
	return 0;
}
