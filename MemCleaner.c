#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define KB_TO_B 1024

unsigned long long getMem();
void libera(unsigned long long memLiberarKB);

int main(int argc, char** argv)
{
	libera(getMem());
	return 0;
}	// int main()

unsigned long long getMem()
{
	unsigned long long phys;
	MEMORYSTATUSEX mem;
	mem.dwLength = sizeof(mem);
	GlobalMemoryStatusEx(&mem);
	printf("\nPorcentaje usado de la memoria: %ld%%\n", mem.dwMemoryLoad);
	phys = (mem.ullAvailPhys/KB_TO_B);
	printf("Memoria fisica disponible: %I64d KB\n", phys);
	return phys;
}	// unsigned long long getMem()

void libera(unsigned long long memLiberarKB)
{
	void** ptr;
	unsigned long long index;
	//	Se libera sólo un 90% de la memoria total disponible.
	///memLiberarKB = 0.9 * memLiberarKB;
	printf(
		"\nSe va a liberar un 100%% de dicha cantidad de memoria (%I64d KB)\n",
		memLiberarKB);
	printf("Ocupando memoria...\n");
	ptr = calloc(memLiberarKB, sizeof(void*));
	for (index = 0; index < memLiberarKB; index++)
	{
		ptr[index] = calloc(KB_TO_B, sizeof(char));
	}

	printf("Liberando memoria...\n");
	for (index = 0; index < memLiberarKB; index++)
	{
		free(ptr[index]);
	}
	free(ptr);
}