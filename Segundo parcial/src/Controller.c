#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "pokemonGo.h"
#include "parser.h"
#include "utn_get.h"
#include "Controller.h"


/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayList)
{
	FILE* pFile;
	int errorCode=-1;

	if((pFile=fopen(path, "r"))!=NULL)
	{
		ll_clear(pArrayList);

		if(!parser_PokemonFromText(pFile, pArrayList))
		{
			errorCode= 0;
			puts("Datos cargados correctamente...");
		}
	}
	fclose(pFile);
    return errorCode;
}


int controller_removePokemon(LinkedList* pArrayList, int max)
{

	int numero;
	char nombre[25];
	char tipo[25];
	char tamanio[25];
	char ataqueCargado[50];
	int valorAtaque;
	int esVarioColor;
	int idToGet;
	int len;
	int i;
	int option;
	ePokemones* pokemon;

	getIntNumber(&option,"Ingrese:\n1- Si desea ver la lista de pokemones\n2- Si desea ingresar el ID del pokemon a eliminar\n","Error. Opcion incorrecta\n",1,2,5);
	if(option==1)
	{
		controller_ListPokemon(pArrayList, max);
	}

	getIntNumber(&idToGet,"Ingrese el numero del pokemon que desea eliminar:\n","Error. Ha excedido el limite de id\n",1,100000,5);
	len=ll_len(pArrayList);
	for(i=0;i<len;i++)
	{
		pokemon=ll_get(pArrayList, i);
		if(pokemon->numero == idToGet)
		{
			pokemon=ll_pop(pArrayList,i);
			puts("Pokemon eliminado:");
			Pokemon_getNumero(pokemon, &numero);
			Pokemon_getNombre(pokemon, nombre);
			Pokemon_getTipo(pokemon, tipo);
			Pokemon_getTamanio(pokemon, tamanio);
			Pokemon_getAtaqueCargado(pokemon, ataqueCargado);
			Pokemon_getValorAtaque(pokemon, &valorAtaque);
			Pokemon_getEsVarioColor(pokemon, &esVarioColor);
			showSimplePokemon(numero, nombre, tipo, tamanio, ataqueCargado, valorAtaque, esVarioColor);
			break;
		}else if(i==len-1 && pokemon->numero!=idToGet)
		{
			puts("El pokemon ingresado no existe");
		}
	}
    return 0;
}
/** \brief Listar pokemones
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */

void selectPage(LinkedList* pArrayListPassenger, int option, int showMax, int* inicio, int* final, int* flag)
{
	int len;
	len = ll_len(pArrayListPassenger);

	switch(option)
	{
	case 2:
		if((len - *final)<showMax && *flag<len+1)
		{
			*inicio=*final;
			*final=len;
			*flag=*final+1;
			if(*inicio==0)
			{
				while((*final-*inicio)!=showMax)
				{
					*final=*final+1;
				}
			}
		}else if(*flag<len)
		{
			*final+=showMax;
			*inicio+=showMax;
			*flag=*final+1;
			*inicio=*flag-showMax-1;
		}
		else if(*final<showMax)
		{
			*inicio+=*final;
			*final=*inicio+showMax;
			*flag=*final+1;
			*flag=0;
		}
		break;
	case 1:
		if(*final>=showMax && *inicio>=1)
		{
			*final-=showMax;
			*inicio-=showMax;
			*flag=*final+1;
			while((*final-*inicio)!=showMax)
			{
				*inicio=*inicio-1;
			}
			if((len-*inicio)<showMax)
			{
				*final=*inicio;
				*inicio=0;
				*flag=*final+1;
			}
			if(*inicio<0)
			{
				*inicio=0;
			}
		}
		break;
	}
}

void showFromTo(LinkedList* pArrayList, int max)
{
	int option;
	int inicio=0;
	int final=max;
	int flag=0;

	LinkedList* listaPokemonAuxiliar = ll_newLinkedList();

	do
	{
		listaPokemonAuxiliar=ll_subList(pArrayList,inicio,final);
		listPokemon(listaPokemonAuxiliar);
		getIntNumber(&option,"Ingrese:\n1- Pagina Anterior(<---)           2- Pagina Siguiente(--->)\n3- Salir\n",
					"Error. Ha ingresado una opcion incorrecta\n",1,3,5);
		ll_clear(listaPokemonAuxiliar);
		selectPage(pArrayList, option, max, &inicio, &final, &flag);
	}while(option!=3);

	ll_deleteLinkedList(listaPokemonAuxiliar);
}

void listPokemon(LinkedList* pArrayList)
{
	int len;

	len=ll_len(pArrayList);
	Pokemon_showPokemon(pArrayList, 0, len);
}

int controller_ListPokemon(LinkedList* pArrayList, int max)
{
	int rtn=-1;
	int len;

	if(pArrayList != NULL)
	{
		len=ll_len(pArrayList);
		if(len<max+1)
		{
			Pokemon_showPokemon(pArrayList, 0, len);
		}
		else
		{
			showFromTo(pArrayList, max);
		}
		rtn=1;
	}
    return rtn;
}

int controller_filterPokemon(LinkedList* pArrayList, int max)
{
	int rtn=-1;
	LinkedList* listPokemonAux = ll_newLinkedList();
	if(pArrayList != NULL)
	{
		listPokemonAux = ll_filter(pArrayList, Pokemon_filterShinyAndWater);
		controller_ListPokemon(listPokemonAux, max);
		ll_deleteLinkedList(listPokemonAux);
		rtn=0;
	}
	return rtn;
}

int controller_mapAtaque(LinkedList* pArrayList, int max, int option, int* mod1, int* mod2)
{
	int rtn=-1;

	if(pArrayList != NULL)
	{
		if(option==1)
		{
			if(*mod1==-1)
			{
				ll_map(pArrayList, Pokemon_mapAtaqueDiaDespejado);
				puts("Mejoras aplicadas...");
				*mod1=0;
			}else
			{
				puts("No se puede volver a aplicar la mejora por dia despejado");
			}

		}else
		{
			if(*mod2==-1)
			{
				ll_map(pArrayList, Pokemon_mapEventoKanto);
				puts("Mejoras aplicadas...");
				*mod2=0;
			}else
			{
				puts("No se puede volver a aplicar la mejora por evento kanto");
			}
		}
		rtn=0;
	}
	return rtn;
}

int controller_countPokemons(LinkedList* pArrayList, int max)
{
	int rtn=-1;
	int pokemonsParaElBoss;

	if(pArrayList != NULL)
	{
		pokemonsParaElBoss=ll_count(pArrayList, Pokemon_countPokemonToDefeatBoss);
		if(pokemonsParaElBoss>=3)
		{
			printf("Disponemos de %d Pokemons en nuestra mochila para vencer al Boss\n!Hemos ganado\n",pokemonsParaElBoss);
		}else
		{
			printf("No disponemos de Pokemons suficientes para la batalla %d\n", pokemonsParaElBoss);
		}
		rtn=0;
	}
	return rtn;
}
