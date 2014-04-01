#include <stdlib.h>
# define NB_ASCII 128
#define VERBOSE 1

typedef char* CHAINE;
typedef int OCCURENCE;
typedef int SIZE;
typedef int INDICE;
typedef int BOOLEAN;

typedef struct caractere
{
	char ascii_code;
	OCCURENCE occurence;
	CHAINE chaine;
	SIZE size;
}CARACTERE;

void init_caractere ( CARACTERE* caractere, char ascii_code, OCCURENCE occurence, CHAINE chaine, SIZE size );
void compt_caractere ( CHAINE text, SIZE text_size, CARACTERE* liste);
void switch_caractere ( CARACTERE** tas, INDICE target1, INDICE target2 );
CARACTERE** entasser ( CARACTERE* liste, SIZE liste_size );
INDICE calc_node_up ( INDICE current_node);
void affichage_tas( CARACTERE** tas, SIZE tas_size);
CARACTERE** trier ( CARACTERE** tas, SIZE tas_size );
INDICE* calc_nodes_down ( INDICE current_node);
BOOLEAN is_last_node( INDICE particular_node );

