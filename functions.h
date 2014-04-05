#include <stdlib.h>
# define NB_ASCII 128
#define VERBOSE 0

typedef char* CHAINE;
typedef int OCCURENCE;
typedef int SIZE;
typedef int INDICE;
typedef int BOOLEAN;
typedef char BIT;

typedef struct caractere
{
	char ascii_code;
	OCCURENCE occurence;
	CHAINE chaine;
	SIZE size;
	char* code;
}CARACTERE;

typedef struct NODE
{
	CARACTERE* node_caractere;
	char node_bit;
	OCCURENCE occurences_cumul;
	INDICE profondeur;
	struct NODE* father;
	struct NODE* left_son;
	struct NODE* right_son;
	struct NODE* list_next;
}NODE;

typedef struct NODE_CHAIN
{
	NODE* first_node;
	SIZE chain_size;	
}NODE_CHAIN;
	


void init_caractere ( CARACTERE* caractere, char ascii_code, OCCURENCE occurence, CHAINE chaine, SIZE size );
void compt_caractere ( CHAINE text, SIZE text_size, CARACTERE* liste);
void switch_caractere ( CARACTERE** tas, INDICE target1, INDICE target2 );
CARACTERE** entasser ( CARACTERE* liste, SIZE liste_size );
INDICE calc_node_up ( INDICE current_node);
void affichage_tas( CARACTERE** tas, SIZE tas_size);
CARACTERE** trier ( CARACTERE** tas, SIZE tas_size );
INDICE* calc_nodes_down ( INDICE current_node, CARACTERE** tas);
BOOLEAN is_last_node( INDICE particular_node, INDICE last_switched );
NODE creerNoeud(CARACTERE* node_caractere, BIT node_bit, OCCURENCE occurences_cumul, INDICE profondeur, NODE* father, NODE* left_son, NODE* right_son, NODE* list_next );
NODE construireArbreHuffman( CARACTERE** , SIZE );
SIZE nodeChainCompt(NODE_CHAIN);
NODE* extractNodeFromChain( NODE_CHAIN CHAIN, INDICE target );
void deleteNodeFromChain( NODE_CHAIN* CHAIN, INDICE target);
void insertNodeOnChain( NODE_CHAIN* CHAIN, NODE* node, INDICE target);
NODE chercherNoeud(NODE Arbre_root, char ascii_code);
void construireCodesHuffman(CARACTERE** tas, SIZE size, NODE Arbre__root);

