#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Windows.h>


#define KB_TO_B 1024


unsigned long long getMem();
char cleanMem(double fpMemInKB);
void printUsage(char **argv);


// Main function
int main(int argc, char **argv) {
	char exitCode = -1;
	printf("Josemi's MemCleaner\n"
		   "https://github.com/josemirm/MemoryCleaner\n");

	// To prevent OS malfunctioning, it will only clean the 90% of the memory
	// available
	double avail = (float) getMem();

	// Only compile these lines if the machine is a 32-bit one
#if _WIN32 || _WIN64
#if !_WIN64
	const double MAX_4GB_IN_KB = (double)((uint32_t)-1);
	if (avail > MAX_4GB_IN_KB) {
		printf("\nWARNING: For this amount of memory you should be using the 64-bit version of this program\n");
			   
		char cont = 0;
		do {
			printf("Do you want to continue? (y/n): ");
			fflush(stdout);
			cont = tolower(getchar());
			char other = getchar(); // This is to remove the '\n' after entering the key	
		} while (cont != 'n' && cont != 'y');

		if (cont == 'n') {
			return 0;
		}
	}
#endif
#endif
	
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
					exitCode = cleanMem(avail / 100.0 * ((double)perc));
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
		exitCode = cleanMem(avail*0.8);
	}

	return exitCode;
}	// int main()


// Prints help
void printUsage(char **argv) {
	printf("\nUsage: %s -p <percentage from 1 to 100 of memory to clean>\n"
		"Use %s -h to show this help.\n"
		"Use %s -f to get the free memory available.\n\n", argv[0], argv[0], argv[0]);
}	// void printUsage()


// Returns the amount of free memory and prints it on screen
unsigned long long getMem() {
	unsigned long long phys;
	MEMORYSTATUSEX mem;

	mem.dwLength = sizeof(mem);
	GlobalMemoryStatusEx(&mem);
	
	printf("\nPhysical memory used (percentage): %ld%%\n", mem.dwMemoryLoad);
	
	phys = (mem.ullAvailPhys/KB_TO_B);
	printf("Physical memory available: \t%I64d KB\n", phys);
	
	return phys;
}	// unsigned long long getMem()


// Clean the given amount of memory
char cleanMem(double fpMemInKB) {
	size_t index, memInKB = ((size_t) fpMemInKB);
	char** ptr = NULL;
	char ret = -1;
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
	
		ret = 0;
	}
	
	return ret;
}
