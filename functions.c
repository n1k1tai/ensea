#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>



void init_caractere ( CARACTERE* caractere, char ascii_code, OCCURENCE occurence, CHAINE chaine, SIZE size )
{
	 caractere->ascii_code=ascii_code;
	 caractere->occurence=occurence;
	 caractere->chaine=chaine;
	 strcpy(caractere->chaine, chaine);
 }

void compt_caractere ( CHAINE text, SIZE text_size, CARACTERE* liste)
{
    INDICE i,j;
	for (i=0; i<=text_size; i++)
	{
	    for (j=0; j<=NB_ASCII-1; j++)
	    {
	        if (text[i] == liste[j].ascii_code)
	        {
	            liste[j].occurence++;
	            break;
	        }
	    }

	}
}

void switch_caractere ( CARACTERE** tas, INDICE target1, INDICE target2 )
{
	CARACTERE* temp;
	temp=tas[target1];
	tas[target1]=tas[target2];
	tas[target2]=temp;
}


CARACTERE** entasser ( CARACTERE* list, SIZE list_size )
{
	CARACTERE** tas;
	tas=malloc((list_size)*sizeof(CARACTERE*));
	int i,j;
	INDICE node_up;


	for (i=0; i <= list_size-1; i++)
	{
		
		
		if (i == 0)  tas[i]=&list[i];
		if(i != 0)
		{
			tas[i]=&list[i];
			if(VERBOSE) printf("\n\n[n]noeud sélectionné : %d, caractère : %c, occurence : %d\n", i, tas[i]->ascii_code, tas[i]->occurence);  
			j=i;
			do
			{
				node_up=calc_node_up(j);
				if (VERBOSE) printf("[i]indice du noeud actuel : %d indice du noeud supérieur : %d\n",j, node_up);
				if (VERBOSE) printf("[i]occurence du noeud actuel : %d occurence du noeud supérieur : %d\n",tas[j]->occurence, tas[node_up]->occurence);
				if (tas[j]->occurence > tas[node_up]->occurence) 
				{
					switch_caractere(tas, j, node_up);
					if (VERBOSE) printf("[s]switch caracteres indice actuel : %d, indice up : %d\n\n", j, node_up);
					
				}
					
				else break;
				j=calc_node_up(j);

			}
			while(j!=0);

		}



	}


return tas;
}

INDICE calc_node_up(j)
{
	if (j & 1) return ( (j-1)/2 );
	else return ( (j-2)/2 );
}

void affichage_tas( CARACTERE** tas, SIZE tas_size)
{
	int i;
	for (i=0; i<=tas_size-1; i++)
	{
		printf("Tas[%d] : %c d'occurence : %d\n", i, tas[i]->ascii_code, tas[i]->occurence);
	}
}
 
CARACTERE** trier( CARACTERE** tas, SIZE tas_size )
{
	int i,j;
	INDICE* nodes_down;
	INDICE node_down;
	INDICE last_switched;
	BOOLEAN last_node = 0;
	for(i=tas_size-1; i!=0; i--)
	{
		switch_caractere(tas, i, 0);
		last_switched = i;
		if(VERBOSE) printf("\n\n[n]Après échange : noeud sélectionné : %d, caractère : %c, occurence : %d\n", 0, tas[0]->ascii_code, tas[0]->occurence);  
			j=0;
			
			do
			{
				last_node=0;
				nodes_down=calc_nodes_down(j,tas);
				if (tas[nodes_down[0]]->occurence >= tas[nodes_down[1]]->occurence) node_down=nodes_down[0];
				else node_down=nodes_down[1];
				
				if (VERBOSE) printf("[i]indice du noeud actuel : %d indice du noeud inférieur de plus grande occurence : %d\n",j, node_down);
				if (VERBOSE) printf("[i]occurence du noeud actuel : %d occurence du noeud inférieur : %d\n",tas[j]->occurence, tas[node_down]->occurence);
				if (tas[j]->occurence < tas[node_down]->occurence) 
				{
					switch_caractere(tas, j, node_down);
					if (VERBOSE) printf("[s]switch caracteres indice actuel : %d, indice down : %d\n\n", j, node_down);
					
				}
					
				else break;
				j=node_down;
				if (VERBOSE) printf("[i] Avant is last node, node_down : %d, last_switched : %d\n", node_down, last_switched);
				last_node=is_last_node(node_down,last_switched);

			}
			while(!last_node);
			
			
			}
return tas;
}

INDICE* calc_nodes_down(INDICE current_node, CARACTERE** tas)
{
	INDICE* nodes_down = malloc(2*sizeof(INDICE));
	
	nodes_down[0]=(current_node*2 + 1);
	nodes_down[1]=(current_node*2 + 2);
	if (VERBOSE) printf("Calcul de nodes_down, les indices sont : %d et %d, d'occurences respectives %d et %d\n", nodes_down[0], nodes_down[1], tas[nodes_down[0]]->occurence, tas[nodes_down[1]]->occurence);
	
	return nodes_down;
}

BOOLEAN is_last_node(INDICE particular_node, INDICE last_switched)
{
	BOOLEAN last_node = 0;
	if (particular_node == NB_ASCII-1 )
	{
		last_node =1;
		if (VERBOSE) printf("last_node = 1 due to max overcome\n Debug : particular node : %d\n", particular_node);
	}
	if ((particular_node*2+1) >= last_switched ) 
	{
		last_node = 1;
		if (VERBOSE) printf("last_node = 1 due to last switched overcome\n");
	}
	
	if (VERBOSE) printf("Is last node : %d", last_node);
	
	return last_node;
}

NODE creerNoeud(CARACTERE* node_caractere, BIT node_bit, OCCURENCE occurences_cumul, INDICE profondeur, NODE* father, NODE* left_son, NODE* right_son, NODE* list_next )
{
	NODE new_node;
	
	new_node.node_caractere=node_caractere;
	new_node.node_bit=node_bit;
	new_node.occurences_cumul=occurences_cumul;
	new_node.profondeur=profondeur;
	new_node.father=father;
	new_node.left_son=left_son;
	new_node.right_son=right_son;
	new_node.list_next=list_next;
	
	return new_node;
}

NODE construireArbreHuffman(CARACTERE** tas, SIZE size)
{
	NODE* current_node;
	NODE* former_node;
	CARACTERE* current_caractere;
	INDICE i;
	SIZE list_size=0;
	NODE_CHAIN CHAIN;
	CHAIN.chain_size=0;
	NODE* left_son;
	NODE* right_son;
	
	
	for (i=size-1; ( (tas[i]->occurence!= 0) && (i != 0) ) ; i--)
	{
		NODE* current_node;
		current_node=malloc(sizeof(NODE));
		*current_node = creerNoeud(tas[i], 0, tas[i]->occurence, 0, NULL, NULL, NULL, NULL);
		CHAIN.chain_size++;   
		if ( i == size-1 ) CHAIN.first_node = current_node;
		else former_node->list_next=current_node;
		former_node = current_node;
		list_size++;
	}
	
	while ( nodeChainCompt(CHAIN) >= 2 )
	{
		left_son=extractNodeFromChain(CHAIN, nodeChainCompt(CHAIN));
		right_son=extractNodeFromChain(CHAIN, nodeChainCompt(CHAIN)-1);
		NODE father = creerNoeud(NULL, 0, left_son->occurences_cumul + right_son->occurences_cumul, 0, NULL, left_son, right_son, NULL);
		left_son->father=&father;
		right_son->father=&father;
		right_son->list_next=NULL;
		left_son->node_bit=0;
		left_son->list_next=NULL;
		right_son->node_bit=1;
		deleteNodeFromChain(CHAIN, 0);
		deleteNodeFromChain(CHAIN, 1);
		insertNodeOnChain(CHAIN, father, nodeChainCompt(CHAIN));
	}
	
		
}

SIZE nodeChainCompt(NODE_CHAIN CHAIN)
{
	SIZE size=0;
	NODE current_node;
	
	if (CHAIN.first_node == NULL) return 0;
	current_node=*CHAIN.first_node;
	
	while ( current_node.list_next != NULL )
	{
		size++;
		current_node=*current_node.list_next;
	}
	
	return size;
}
		
NODE* extractNodeFromChain( NODE_CHAIN CHAIN, INDICE target )
{
	NODE* current_node;
	INDICE i=1;
	
	if (CHAIN.first_node == NULL) return NULL;
	current_node=CHAIN.first_node;
	
	while ( current_node->list_next != NULL )
	{
		if ( i == target ) return current_node;
		i++;
		current_node=current_node->list_next;
		
	}
	
	return NULL;
	
}		
		
void deleteNodeFromChain( NODE_CHAIN CHAIN, INDICE target)
{
	NODE* current_node;
	NODE* former_node;
	INDICE i;
	
	current_node=CHAIN.first_node;
	for (i=1; i!= target; i++)
	{
		former_node=current_node;
		current_node=current_node->list_next;
		 
	}
	
	former_node->list_next=current_node->list_next;
}
	
void insertNodeOnChain ( NODE_CHAIN CHAIN, NODE node, INDICE target)
{
	NODE current_node;
	NODE former_node;
	INDICE i;
	
	current_node=*(CHAIN.first_node);
	for (i=1; i!= target; i++)
	{
		former_node=current_node;
		current_node=*(current_node.list_next);
		 
	}
	former_node.list_next=&node;
	node.list_next=&current_node;
}
