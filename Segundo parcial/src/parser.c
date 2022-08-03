#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "pokemonGo.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PokemonFromText(FILE* pFile , LinkedList* pArrayList)
{
	char numeroStr[20];
	char nombreStr[25];
	char tipoStr[25];
	char tamanioStr[25];
	char ataqueCargadoStr[50];
	char valorAtaqueStr[20];
	char esVarioColorStr[20];
	ePokemones* aPokemon;
	int rtn=-1;

	while(!feof(pFile))
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",numeroStr,nombreStr,tipoStr,tamanioStr,ataqueCargadoStr,valorAtaqueStr,esVarioColorStr);
		aPokemon=Pokemon_newParametros(numeroStr,nombreStr,tipoStr,tamanioStr,ataqueCargadoStr,valorAtaqueStr,esVarioColorStr);
		if(aPokemon!=NULL)
		{
			if(!ll_add(pArrayList, aPokemon))
			{
				rtn=0;
			}
		}
	}
    return rtn;
}

