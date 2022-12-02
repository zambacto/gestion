#define Color_Red "\33[0:31m\\]"
#define Color_end "\33[0m\\]"	
	
	
	
int string_compare(char str1[], char str2[])
{
    int ctr=0;

    while(toupper(str1[ctr])==toupper(str2[ctr]))
    {
        if(str1[ctr]=='\0'||str2[ctr]=='\0')
            break;
        ctr++;
    }
    if(str1[ctr]=='\0' || str2[ctr]=='\0')
        return 0;
    else
        return -1;
}




void afficherProduitQuiCommence (Produit *Prodtab, int n){
	char recherche[100];
	int i=0;
	printf("Donner le/les produit(s) rechercher : ");
	fflush(stdin);
	gets(recherche);
	
	printf ("\n----------------------------------------------------------------------------------------\n");
	printf("Num\tNom\tModel\tRefLot\tPrix\tQuantite\n");
	printf("-----------------------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{
			if(string_compare(Prodtab[i].nom,recherche) == 0){
				printf ("%d\t%s\t%s\t%s\t%.3f\t%d\n",Prodtab[i].num,Prodtab[i].nom,Prodtab[i].model,Prodtab[i].lot.reference,Prodtab[i].prix,Prodtab[i].quantiteStock);
			}	
		}
		printf("\n\n");
}



void numProdCorresp(Produit *Prodtab,int n)
{
	char produitRecherche[100];
	int i=0;
	
	printf("Donner le nom du produit : ");
	fflush(stdin);
	gets(produitRecherche);
	
	printf ("\n----------------------------------------------------------------------------------------\n");
	printf("Num\tNom\tModel\tRefLot\tPrix\tQuantite\n");
	printf("-----------------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++){
		if(strcmp(Prodtab[i].nom,produitRecherche)==0)
		{
			printf ("%d\t%s\t%s\t%s\t%.3f\t%d\n",Prodtab[i].num,Prodtab[i].nom,Prodtab[i].model,Prodtab[i].lot.reference,Prodtab[i].prix,Prodtab[i].quantiteStock);
		}
	}
}



void QauntiteProd(Produit *Prodtab,int n){
	char produitRecherche[100];
	fflush(stdin);
	printf("Donner le nom du produit : ");
	gets(produitRecherche);
	int i;
	int trouve=0;
	printf ("----------------------------------------------------------------------------------------\n");
	printf(" Num\tNom\tModel\tRefLot\tPrix\tQuantite\n");
	printf("-----------------------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{	if(string_compare(Prodtab[i].nom,produitRecherche)==0){
			
			printf ("%d\t%s\t%s\t%s\t%.3f\t%d\n",Prodtab[i].num,Prodtab[i].nom,Prodtab[i].model,Prodtab[i].lot.reference,Prodtab[i].prix,Prodtab[i].quantiteStock);
			trouve=1;
			}	
		}
	if (trouve==0){
		printf("\nProduit inconnu!\n");
	}

}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/



//fonction qui efface un medicament si il est périmé ou a une quantité null
void suppProd(Produit *Prodtab , int *n)
{
	char reference[100];
	fflush(stdin);
	printf("\nDonner une reference : ");
	gets(reference);
	int i;
	int j;
	int trouve = 0;
	
	for(i=0;i<*n;i++)
	{
		
		if(strcmp(Prodtab[i].lot.reference,reference)==0){
			
			if(Prodtab[i].quantiteStock==0)
			{
				for(j=i;j<*n;j++)
				{
					Prodtab[j]=Prodtab[j+1];
				}
				*n=*n-1;
				printf("\nSuppression effectuer ! \n");
			}
			else{
				printf("Impossible de supprimer le produit %s de reference %s \n",Prodtab[i].nom,Prodtab[i].lot.reference);
				printf("Quantite restante est : %d \n",Prodtab[i].quantiteStock);
			}
			trouve = 1;
		}	
	}
	if (trouve == 0){
		printf("\nReference introuvable!\n");
	}
		
	FILE *FProd = fopen("FProd.txt","wb");
	if(FProd == NULL){
	printf("\nERREUR: Impossible d ouvrir le fichier.");
	exit(1);}
	
	fwrite (Prodtab, sizeof(Produit),*n, FProd );
	fclose(FProd);
}



