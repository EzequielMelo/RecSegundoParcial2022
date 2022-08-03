#include "pokemonGo.h"
#include "LinkedList.h"
#include "Controller.h"
#include "utn_get.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ePokemones* Pokemon_new()
{
	ePokemones* newPokemon = NULL;
	newPokemon= (ePokemones*)malloc(sizeof(ePokemones));
	return newPokemon;
}

ePokemones* Pokemon_newParametros(char* numeroStr,char* nombreStr,char* tipoStr,char*tamanioStr,char*ataqueCargadoStr,char*valorAtaqueStr,char*esVarioColorStr)
{
	ePokemones* newPokemon = NULL;
	newPokemon= Pokemon_new();

	if(newPokemon!=NULL)
	{
		newPokemon->numero=atoi(numeroStr);
		strcpy(newPokemon->nombre, nombreStr);
		strcpy(newPokemon->tipo, tipoStr);
		strcpy(newPokemon->tamanio, tamanioStr);
		strcpy(newPokemon->ataqueCargado, ataqueCargadoStr);
		newPokemon->valorAtaque=atoi(valorAtaqueStr);
		newPokemon->esVarioColor=atoi(esVarioColorStr);
	}
	return newPokemon;
}

int Pokemon_getNumero(ePokemones* this,int* numero)
{
	int errorCode=-1;
	if(this!=NULL)
	{
		*numero=this->numero;
		errorCode=0;
	}
	return errorCode;
}

int Pokemon_getNombre(ePokemones* this,char* nombre)
{
	int errorCode=-1;
	if(this!=NULL && nombre!=NULL)
	{
		strcpy(nombre, this->nombre);
		errorCode=0;
	}
	return errorCode;
}

int Pokemon_getTipo(ePokemones* this,char* tipo)
{
	int errorCode=-1;
	if(this!=NULL && tipo!=NULL)
	{
		strcpy(tipo, this->tipo);
		errorCode=0;
	}
	return errorCode;
}

int Pokemon_getTamanio(ePokemones* this,char* tamanio)
{
	int errorCode=-1;
	if(this!=NULL && tamanio!=NULL)
	{
		strcpy(tamanio, this->tamanio);
		errorCode=0;
	}
	return errorCode;
}

int Pokemon_getAtaqueCargado(ePokemones* this,char* ataqueCargado)
{
	int errorCode=-1;
	if(this!=NULL && ataqueCargado!=NULL)
	{
		strcpy(ataqueCargado, this->ataqueCargado);
		errorCode=0;
	}
	return errorCode;
}

int Pokemon_getValorAtaque(ePokemones* this,int* valorAtaque)
{
	int errorCode=-1;
	if(this!=NULL)
	{
		*valorAtaque=this->valorAtaque;
		errorCode=0;
	}
	return errorCode;
}

int Pokemon_getEsVarioColor(ePokemones* this,int* esVarioColor)
{
	int errorCode=-1;
	if(this!=NULL)
	{
		*esVarioColor=this->esVarioColor;
		errorCode=0;
	}
	return errorCode;
}

int Pokemon_setValorAtaque(ePokemones* this, int valorAtaque)
{
	int rtn=-1;
	if(this!=NULL && valorAtaque>0)
	{
		this->valorAtaque = valorAtaque;
		rtn=0;
	}
	return rtn;
}

int Pokemon_filterShinyAndWater(void* pok)
{
	int filter=0;
	char tipo[25];
	int esVarioColor;
	ePokemones* pokemon;

	pokemon=pok;

	if(pok!=NULL && !Pokemon_getTipo(pokemon, tipo) && !Pokemon_getEsVarioColor(pokemon,&esVarioColor))
	{
		if((strcmp(tipo,"Water")==0) && esVarioColor==1)
		{
			filter=1;
		}
	}
	return filter;
}

void Pokemon_mapAtaqueDiaDespejado(void* pok)
{
	ePokemones* pokemon=pok;
	int ataque;
	char tipo[25];

	if(pok!=NULL && !Pokemon_getValorAtaque(pokemon,&ataque) && !Pokemon_getTipo(pokemon, tipo))
	{
		if((strcmp(tipo,"Fire")==0) || (strcmp(tipo,"Ground")==0) || (strcmp(tipo,"Grass")==0))
		{
			ataque = ataque * 1.10;
			Pokemon_setValorAtaque(pok, ataque);
		}
	}
}
/*
6) Mapear ataque cargado: Con motivo del evento Kanto, los pokemenos que
cumplan con las siguientes características incrementaron su poder:
Los pokemones de tipo Bug, Fire y Grass aumentarán su poder un 20%
siempre y cuando el tamaño sea XL, un 10% si es L y sino un 5 para cualquier otro
tamaño.
*/
void Pokemon_mapEventoKanto(void* pok)
{
	ePokemones* pokemon=pok;
	int ataque;
	char tipo[25];
	char tamanio[25];

	if(pok!=NULL && !Pokemon_getValorAtaque(pokemon,&ataque) && !Pokemon_getTipo(pokemon, tipo) && !Pokemon_getTamanio(pokemon, tamanio))
	{
		if((strcmp(tipo,"Bug")==0) || (strcmp(tipo,"Fire")==0) || (strcmp(tipo,"Grass")==0))
		{
			if(strcmp(tamanio,"XL")==0)
			{
				ataque = ataque * 1.20;
				Pokemon_setValorAtaque(pok, ataque);
			}else
			{
				if(strcmp(tamanio,"L")==0)
				{
					ataque = ataque * 1.10;
					Pokemon_setValorAtaque(pok, ataque);
				}else
				{
					ataque = ataque * 1.05;
					Pokemon_setValorAtaque(pok, ataque);
				}
			}
		}
	}
}
/*
 7) Batalla pokemon: Nos hemos encontrado con el jefe del team Rocket, Giovanni. El
malvado jugará su batalla final con Lugia, pokémon de tipo Psíquico. La única forma
de ganarle será formando un equipo con las siguientes características: un pokémon
de tipo Fire de tamaño XL, con ataque Lanzallamas y cuyo valor de ataque sea
superior a 80 o de tipo Water tamaño L, con ataque hidrobomba entre superior a 80.
Determinar cuántos pokemones cumplen con dichas características y anunciar si
ganamos la batalla o no. Tener en cuenta que necesitamos mínimo 3 pokemones
para vencer a este pokémon legendario.

tipo fire
tamanio xl
ataque lanzallamas
valorAtaque >80

water
L
Hidrobomba
>80
 */
int Pokemon_countPokemonToDefeatBoss(void* pok)
{
	ePokemones* pokemon=pok;
	char tipo[25];
	char tamanio[25];
	char ataqueCargado[50];
	int ataque;
	int count=-1;

	if(pok!=NULL && !Pokemon_getTipo(pokemon, tipo) && !Pokemon_getTamanio(pokemon, tamanio) && !Pokemon_getAtaqueCargado(pokemon, ataqueCargado) && !Pokemon_getValorAtaque(pokemon,&ataque))
	{
		if(((strcmp(tipo,"Fire")==0) && (strcmp(tamanio,"XL")==0) && (strcmp(ataqueCargado,"Lanzallamas")==0) && ataque>80) || ((strcmp(tipo,"Water")==0) && (strcmp(tamanio,"L")==0) && (strcmp(ataqueCargado,"Hidrobomba")==0) && ataque>80))
		{
			count=1;
		}
	}
	return count;
}

void Pokemon_showPokemon(LinkedList* pArrayList, int min, int max)
{
	int i;
	ePokemones* this;

	PokemonHeader();
	for(i=0; i<max; i++)
	{
		this=ll_get(pArrayList, i);
		printf("|%5d  |%10s     |%10s    |%5s   |%15s   |%5d  |%5d   |\n", this->numero,
																				this->nombre,
																				this->tipo,
																				this->tamanio,
																				this->ataqueCargado,
																				this->valorAtaque,
																				this->esVarioColor);
	}
}

void showSimplePokemon(int numero, char nombre[], char tipo[], char tamanio[], char ataqueCargado[], int valorAtaque, int esVarioColor)
{
	PokemonHeader();
	printf("|%5d  |%10s     |%10s    |%5s   |%15s   |%5d  |%5d   |\n", numero, nombre, tipo, tamanio, ataqueCargado, valorAtaque, esVarioColor);
}


void PokemonHeader()
{
	puts("_____________________________________________________________________________________");
	puts("|Numero |     Nombre    |     Tipo     |Tamanio |  Ataque Cargado  |   VA  | Shiny  |");
	puts("|_______|_______________|______________|________|__________________|_______|________|");
}

