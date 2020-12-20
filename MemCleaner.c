#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define KB_TO_B 1024

unsigned long long getMem();
void freeMem(unsigned long long memInKB);
void printUsage(char **argv);

int main(int argc, char **argv)
{
	printf("Josemi's MemCleaner\n");

	// To prevent OS malfunctioning, it will only clean the 90% of the memory
	// available
	unsigned long long avail = 10 * getMem() / 9;
	unsigned long long memToClean;

	if (argc == 2) {
		if (argv[1][0] == '-') {
			switch (argv[1][1]) {
				case 'f':
					break;
				
				case 'h':
				default:
					printUsage();
			}		
		} else {
			memToClean = atoll(argv[1]);
			if (memToClean == 0) {
				printUsage();
			}

			if (memToClean > avail) {
				freeMem(avail);
			} else {
				freeMem(memToClean);
			}
		}
	} else {
		printf("No options selected.\
				90%% of the available memory will be cleaned\n");
		freeMem(avail);
	}

	return 0;
}	// int main()

void printUsage(char **argv) {
	printf("Usage: %s <Mem. to free in KB>\
			Use %s -h to show this help.
			Use %s -f to get the free memory available.\n", argv[1], argv[1]);
}	// void printUsage()

unsigned long long getMem() {
	unsigned long long phys;
	MEMORYSTATUSEX mem;

	mem.dwLength = sizeof(mem);
	GlobalMemoryStatusEx(&mem);
	
	printf("\nPhysical memory used (percentage): %ld%%\n", mem.dwMemoryLoad);
	
	phys = (mem.ullAvailPhys/KB_TO_B);
	printf("Physical memory available: %I64d KB\n", phys);
	
	return phys;
}	// unsigned long long getMem()

void freeMem(unsigned long long memInKB);
{
	void** ptr;
	unsigned long long index;
	
	printf("\n%I64d KB of memory will be cleaned up\n", memInKB);
	printf("Occupying  memory...\n");

	ptr = calloc(memInKB, sizeof(void*));

	for (index = 0; index < memInKB; index++) {
		ptr[index] = calloc(KB_TO_B, sizeof(char));

		// When there isn't available memory, the pointer returned is null. In
		// this case memory allocation must stop to start freeing memory.
		if ( !(ptr[index]) ) {
			memInKB = index;
			break;
		}
	}

	printf("Freeing memory...\n");

	for (index = 0; index < memInKB; index++) {
		free(ptr[index]);
	}

	free(ptr);
}
