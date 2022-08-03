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
    LinkedList* listaPokemones = ll_newLinkedList();
    do{
    	puts("------------------------------------MENU------------------------------------");
    	puts("1- Cargar los datos de los pokemones desde el archivo pokemon.csv (modo texto).");
    	puts("2- Eliminar pokemon.");
    	puts("3- Imprimir pokemones.");
    	puts("4- Filtrar de tipo agua.");
    	puts("5- Mapear ataque cargado.");
    	puts("6- Salir.");
		getIntNumber(&option, "Ingrese una opcion del menu:",
				"Error opcion invalida", 1, 6, 5);
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
            		controller_mapAtaque(listaPokemones, SHOWMAX);
            	}
            	else
            	{
            		puts("Aun no se han cargado los datos. Por favor ingreselos desde la primera opcion");
            	}
            	break;
        }
    }while(option != 6);
    return 0;
}
