#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Windows.h>


#define CHUNKS 8
#define B_TO_KB(b) (b/1024)

typedef unsigned long long ULL;

ULL getMem(void);
char cleanMem(ULL freeMemInB);
void printUsage(char **argv);



// Main function
int main(int argc, char **argv) {
	char exitCode = -1;
	printf("Josemi's MemCleaner\n"
		   "https://github.com/josemirm/MemoryCleaner\n");

	ULL avail = getMem();

	// Only compile these lines if the machine is a 32-bit one
	#ifndef _WIN64
		const ULL MAX_4GB_IN_KB = (uint32_t) -1;
		if (avail > MAX_4GB_IN_KB) {
			printf("\nWARNING: For this amount of memory you should be using the 64-bit version of this program\n");

			char cont = 0;
			do {
				printf("Do you want to continue? (y/n): ");
				fflush(stdout);
				cont = tolower(getchar());
				getchar(); // This is to remove the '\n' after entering the key
			} while (cont != 'n' && cont != 'y');

			if (cont == 'n') {
				return 0;
			}
		}
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
					avail /= 100;
					avail *= perc;
					exitCode = cleanMem(avail);
					if (exitCode != 0) {
						printf("Warning: The program was not available to clean all the memory requested.\n");
					}
				}

				break;
			}

			// Only shows free memory (already done previously)
			case 'f':
				exitCode = 0;
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
		avail /= 10;
		avail *= 8;
		exitCode = cleanMem(avail);
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
ULL getMem(void) {
	ULL phys;
	MEMORYSTATUSEX mem;

	mem.dwLength = sizeof(mem);
	GlobalMemoryStatusEx(&mem);

	printf("\nPhysical memory used (percentage): %ld%%\n", mem.dwMemoryLoad);

	phys = mem.ullAvailPhys;
	printf("Physical memory available: \t%llu KB\n", B_TO_KB(phys));

	return phys;
}	// unsigned long long getMem()


// Clean the given amount of memory
char cleanMem(ULL freeMem) {
	if (freeMem < 1) {
		fprintf(stderr, "\n 0 KB available. No memory to clean\n");
		return -1;
	}

	char ret = 0;

	printf("\n%llu KB of the available memory will be cleaned up\n", B_TO_KB(freeMem));
	printf("Occupying  memory...\n");

	// The amount of memory to use would be divided in chunks
	char** ptr = (char**) calloc(CHUNKS, sizeof(char*));
	if (ptr) {
		ULL chunkSize = freeMem / CHUNKS;
		int i;
		for (i = 0; i < CHUNKS; ++i) {
			ptr[i] = calloc(1, chunkSize);

			// When there isn't available memory, the pointer returned is null. In
			// this case memory allocation must stop to start freeing memory.
			if ( !(ptr[i]) ) {
				ret = -1;
				fprintf(stderr, "Error: Only allocated %llu KB of RAM", chunkSize * i);
				break;
			}

			// Accessing some part of the memory, so the compiler won't optimize it
			ptr[i][chunkSize - 1] = 0xFF;
		}

		// This is to being able to watch the process in the Resourse Monitor
		Sleep(1000);

		printf("Freeing memory...\n");

		// If this try to free a non allocated part of memory (that would have 0x0 value due to
		// using "calloc") it won't have any kind of problem. Trying to free a null pointer have
		// no effect.
		for (i=0; i < CHUNKS; ++i) {
			free(ptr[i]);
		}

		free(ptr);
	} else {
		fprintf(stderr, "Error allocating %llu KB of memory\n", B_TO_KB(freeMem));
		return -1;
	}

	return ret;
}
