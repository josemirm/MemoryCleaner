#include <iostream>

typedef unsigned long long ull;
const int MAX_PTRS = 1000000;
const size_t MAX_ULL = ~0;

void rellenar(ull** l)
{
	for (size_t i=0; i<MAX_PTRS; ++i)
	{
		(*l)[i] = MAX_ULL;
	}
}

void asigMem()
{
	bool ok = true;
	int cont=0;
	ull** l = new ull*[MAX_PTRS];

	while (ok)
	{
		try
		{
			l[cont] = new ull[MAX_PTRS];
			rellenar(&(l[cont]));
			++cont;
		}
		catch (const std::bad_alloc& e)
		{
			ok = false;
			std::cout << "Max of system memory reached.\n"
					  << "About " << (cont*MAX_PTRS*sizeof(ull))
					  << " bytes used.\n";
		}
	}

	for (int i=0; i<cont; ++i)
	{
		delete [] l[i];
	}

	delete [] l;

}

void about()
{
	std::cout << " -> MemoryCleaner by Josemicoronil\n"
			  << "License and more in "
			  << "https://github.com/josemicoronil/MemoryCleaner/\n\n";

}

int main()
{
	about();
	asigMem();
	return 0;
}
