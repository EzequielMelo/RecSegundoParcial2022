int controller_loadFromText(char* path , LinkedList* pArrayListPassenger);
int controller_removePokemon(LinkedList* pArrayList, int max);
void selectPage(LinkedList* pArrayListPassenger, int option, int showMax, int* inicio, int* final, int* flag);
void showFromTo(LinkedList* pArrayListPassenger, int max);
void listPokemon(LinkedList* pArrayList);
int controller_ListPokemon(LinkedList* pArrayList, int max);
int controller_filterPokemon(LinkedList* pArrayList, int max);
int controller_mapAtaque(LinkedList* pArrayList, int max, int option, int* mod1, int* mod2);
int controller_countPokemons(LinkedList* pArrayList, int max);
