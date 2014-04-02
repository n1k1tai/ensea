#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>



int main()
{

	INDICE i;
	CHAINE text = "Physics is like sex. Sure,it may give some practical results, but that’s not why we do it";
	SIZE text_size = strlen(text);
	CARACTERE* liste;
	liste=malloc( NB_ASCII*sizeof(CARACTERE) );
	for (i=0; i <= NB_ASCII-1; i++)
	{
		liste[i].ascii_code=i;
	}

CHAINE text2 = " 1 1 1 1 2 2 2 3 3 4 5 ";
SIZE text2_size = strlen(text2);

compt_caractere(text, text_size , liste);
CARACTERE** tas = entasser(liste, NB_ASCII);
tas = trier(tas, NB_ASCII);
affichage_tas(tas, NB_ASCII);

return 0;

}




