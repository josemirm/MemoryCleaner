#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define KB_TO_B 1024

unsigned long long getMem();
char freeMem(double fpMemInKB);
void printUsage(char **argv);

int main(int argc, char **argv) {
	char exitCode = -1;
	printf("Josemi's MemCleaner\n");

	// To prevent OS malfunctioning, it will only clean the 90% of the memory
	// available
	double avail = (float) getMem();
	
	if (argc > 1) {
		if (argv[1][0] == '-') {
			switch (argv[1][1]) {
			
			// Clean a determined percentage of memory
			case 'p': {
				int perc = atoi(argv[1] + 3);

				if (perc < 1 || perc > 100) {
					printf("%i is an invalid percentage.\n", perc);
					printUsage(argv);
					exit(-1);
				} else {
					printf("%i%% of the memory will be cleaned.\n\n", perc);
					exitCode = freeMem(avail / 100.0 * ((double)perc));
					if (exitCode != 0) {
						printf("Warning: The program was not available to clean all the memory requested.\n");
					}
				}

				break;
			}

			// Only shows free memory (already done previously)
			case 'f':
				break;

			// Show help
			case 'h':
				exitCode = 0;

			default:
				printUsage(argv);
			}
		} else {
			printUsage(argv);
		}
	} else {
		printf("No options selected.\n\n80%% of the available memory will be cleaned\n\n");
		exitCode = freeMem(avail*0.8);
	}

	system("pause");

	return exitCode;
}	// int main()

void printUsage(char **argv) {
	printf("\nUsage: %s -p <percentage from 1 to 100 of memory to clean>\n"
		"Use %s -h to show this help.\n"
		"Use %s -f to get the free memory available.\n\n", argv[0], argv[0], argv[0]);
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

char freeMem(double fpMemInKB) {
	size_t index, memInKB = ((size_t) fpMemInKB);
	char** ptr = NULL;
	char ret = 0;
	printf("\n%zu KB of the available memory will be cleaned up\n", memInKB);
	printf("Occupying  memory...\n");

	ptr = (char**) calloc(memInKB, sizeof(char*));

	if (ptr) {
		for (index = 0; index < memInKB; index++) {
			ptr[index] = calloc(KB_TO_B, sizeof(char));

			// When there isn't available memory, the pointer returned is null. In
			// this case memory allocation must stop to start freeing memory.
			if (!(ptr[index])) {
				memInKB = index;
				ret = -1;
				break;
			}
		}

		printf("Freeing memory...\n");

		for (index = 0; index < memInKB; index++) {
			free(ptr[index]);
		}

		free(ptr);
	} else {
		ret = -1;
	}
	
	return ret;
}
