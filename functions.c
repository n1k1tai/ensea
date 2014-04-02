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
