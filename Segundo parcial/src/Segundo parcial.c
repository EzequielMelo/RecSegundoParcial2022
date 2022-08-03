#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "pokemonGo.h"
#include "Controller.h"
#include "utn_get.h"
#define SHOWMAX 20

int main()
{
	setbuf(stdout, NULL);
    int option = 0;
    int load = -1;
    int mod1=-1;
    int mod2=-1;
    LinkedList* listaPokemones = ll_newLinkedList();
    do{
    	puts("------------------------------------MENU------------------------------------");
    	puts("1- Cargar los datos de los pokemones desde el archivo pokemon.csv (modo texto).");
    	puts("2- Eliminar pokemon.");
    	puts("3- Imprimir pokemones.");
    	puts("4- Filtrar de tipo agua.");
    	puts("5- Mapear ataque cargado.(Dia despejado)");
    	puts("6- Mapear ataque cargado.(Evento Kanto)");
    	puts("7- Contar pokemons para el Jefe");
    	puts("8- Salir.");
		getIntNumber(&option, "Ingrese una opcion del menu:",
				"Error opcion invalida", 1, 8, 5);
        switch(option)
        {
            case 1:
				controller_loadFromText("Data_Pokemones.csv", listaPokemones);
				load = 0;
                break;
            case 2:
            	if(load==0)
            	{
            		controller_removePokemon(listaPokemones, SHOWMAX);
            	}else
            	{
            		puts("Aun no se han cargado los datos. Por favor ingreselos desde la primera opcion");
            	}
            	break;
            case 3:
            	if(load==0)
            	{
            		controller_ListPokemon(listaPokemones, SHOWMAX);
            	}
            	else
            	{
            		puts("Aun no se han cargado los datos. Por favor ingreselos desde la primera opcion");
            	}
            	break;
            case 4:
            	if(load==0)
            	{
            		controller_filterPokemon(listaPokemones, SHOWMAX);
            	}
            	else
            	{
            		puts("Aun no se han cargado los datos. Por favor ingreselos desde la primera opcion");
            	}
            	break;
            case 5:
            	if(load==0)
            	{
            		controller_mapAtaque(listaPokemones, SHOWMAX, 1, &mod1, &mod2);
            	}
            	else
            	{
            		puts("Aun no se han cargado los datos. Por favor ingreselos desde la primera opcion");
            	}
            	break;
            case 6:
            	if(load==0)
            	{
            		controller_mapAtaque(listaPokemones, SHOWMAX, 2, &mod1, &mod2);
            	}
            	else
            	{
            		puts("Aun no se han cargado los datos. Por favor ingreselos desde la primera opcion");
            	}
            	break;
            case 7:
            	if(load==0)
            	{
            		controller_countPokemons(listaPokemones, SHOWMAX);
            	}
            	else
            	{
            		puts("Aun no se han cargado los datos. Por favor ingreselos desde la primera opcion");
            	}
            	break;
        }
    }while(option != 8);
    return 0;
}
