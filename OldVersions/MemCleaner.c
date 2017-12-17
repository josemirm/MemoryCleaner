#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#define __MEMORIA_OCUPADA printf("Memoria ocupada: %I64u MB de RAM\n", ((size_t) cuenta)*32);
  #define __MEMORIA_LIBERADA printf("Memoria liberada: %I64u MB de RAM\n", ((size_t) elim)*32);
#endif

#ifdef __unix
	#define __MEMORIA_OCUPADA printf("Memoria ocupada: %llu MB de RAM\n", (size_t) cuenta*32);
  #define __MEMORIA_LIBERADA printf("Memoria liberada: %llu MB de RAM\n", (size_t) elim*32);
#endif

//  Bloques a ocupar: 32MB por bloque.
//	Se pone un máximo de 1024GB de máximo a ocupar.
#define MILLON 1000000
const size_t TAM_BLOQUE = 32 * MILLON;
const size_t MAX_OCUPAR = 1024000;

void ocupar(size_t mb);

int main(int argc, char const *argv[])
{
  unsigned long memSelec = 0;

  if (argc < 2)
  {
  	printf("%s: Ocupa la cantidad de RAM en MB asignada\n\n", argv[0]);
    printf("Uso del programa:\n");
    printf("%s <num de mb a ocupar>\n", argv[0]);
    printf("En caso de poner \"0\" en la cantidad de MB a ocupar, ocupara toda");
    printf(" la cantidad disponible.\n");
    printf("Esto puede causar inestabilidad del sistema.");
    printf("\n\n");
    exit(0);
  }
	memSelec = atol(argv[1]);
	if (memSelec == 0)
	{
		memSelec = MAX_OCUPAR;
		printf("Cantidad de memoria a ocupar seleccionada: Todo lo posible.");
	}
	else
	{
		printf("Cantidad de memoria a ocupar seleccionada: %lu MB\n", memSelec);
	}

  if (memSelec != 0)
  {
      ocupar(memSelec);
      return 0;
  }

  return 0;
}

void ocupar(size_t mb)
{    //  Se intentan reservar "mb" MB de espacio en bloques de 32MB
    if (mb%32 == 0)
    {
      mb = mb/32;
    }
    else
    {
      mb = (mb/32) + 1;
    }

    size_t cuenta;
    unsigned char** memArray;

    memArray = (unsigned char**) calloc(mb, sizeof(char*));
    if (memArray == NULL)
    {
    	while (memArray == NULL)
    	{
    		mb--;
    		memArray = (unsigned char**) calloc(mb, sizeof(char*));
    	}
    }

    cuenta = 0;
    for (cuenta = 0; cuenta < mb; ++cuenta)
    {
      memArray[cuenta] =
      (unsigned char*) calloc(TAM_BLOQUE/sizeof(unsigned char),
                              sizeof(unsigned char));

      if (memArray[cuenta] == NULL)
      {
        break;
      }
      else
      {
        size_t i;
        for (i=0; i<TAM_BLOQUE; ++i)
        {
          memArray[cuenta][i] = ~0;
        }
      }
    }

    __MEMORIA_OCUPADA
		printf("- Pulse Enter para continual\n");
		int a = getchar();

    size_t elim;
    for (elim=0; elim<cuenta; ++elim)
    {
      free(memArray[elim]);
      memArray[elim]=NULL;
    }

    __MEMORIA_LIBERADA

     free(memArray);
}
