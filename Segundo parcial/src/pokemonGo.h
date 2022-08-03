#include "LinkedList.h"
typedef struct
{
	int numero;
	char nombre[25];
	char tipo[25];
	char tamanio[25];
	char ataqueCargado[50];
	int valorAtaque;
	int esVarioColor;
}ePokemones;

ePokemones* Pokemon_new();
ePokemones* Pokemon_newParametros(char* numeroStr,char* nombreStr,char* tipoStr,char*tamanioStr,char*ataqueCargadoStr,char*valorAtaqueStr,char*esVarioColorStr);
int Pokemon_getNumero(ePokemones* this,int* numero);
int Pokemon_getNombre(ePokemones* this,char* nombre);
int Pokemon_getTipo(ePokemones* this,char* tipo);
int Pokemon_getTamanio(ePokemones* this,char* tamanio);
int Pokemon_getAtaqueCargado(ePokemones* this,char* ataqueCargado);
int Pokemon_getValorAtaque(ePokemones* this,int* valorAtaque);
int Pokemon_getEsVarioColor(ePokemones* this,int* esVarioColor);
int Pokemon_setValorAtaque(ePokemones* this, int valorAtaque);

int Pokemon_filterShinyAndWater(void* pok);
void Pokemon_mapAtaqueDiaDespejado(void* pok);
void Pokemon_mapEventoKanto(void* pok);
int Pokemon_countPokemonToDefeatBoss(void* pok);

void Pokemon_showPokemon(LinkedList* pArrayList, int min, int max);
void showSimplePokemon(int numero, char nombre[], char tipo[], char tamanio[], char ataqueCargado[], int valorAtaque, int esVarioColor);
void PokemonHeader();
