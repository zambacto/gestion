void ajouterFournisseur(Produit *prod){
	int nbFour,i;
	Fournisseur fournisseur;
	
	/* Boucle pour permette au utilisateur d'ajouter au max 3 fournisseurs et au min 1 */
	do{
		printf("Donner le nombre des fournisseurs a ajouter : ");
		scanf("%d",&nbFour);
	}while(nbFour < 1 || nbFour >3);
	
	for(i=0;i<nbFour;i++){
		printf("Donner le nom du fournisseur %d : ", i+1);
		fflush(stdin);
		gets(fournisseur.nom);
		printf("Donner l adresse du fournisseur : ");
		fflush(stdin);
		gets(fournisseur.adresse);
		printf("Donner le numero du fournisseur : ");
		scanf("%d",&fournisseur.telephone);
		prod->listeFournisseur[i]=fournisseur; /* Sauvegarde du fournisseur saisit dans la case correspondate du tableau listeFournisseur */ 
	}
	prod->nombreFournisseur = nbFour; /* Sauvegarde du nombre des fournisseurs saisient dans la variable nombreFournisseur du medicament */
	printf("\nFournisseur ajouter avec succes\n");
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/



/* Fonction qui permet de rechercher la reference d'un produit pass? en param?tre dans la liste : 
	- Retourne 0 si aucune reference trouv?
	- Retourne 1 cas contraire */
	
int rechercheReference(Produit *ProdTab, int *n, char ref[100]){
	int i=0;
	
	while(strcmp(ProdTab[i].lot.reference,ref)!=0 && i<=*n){
		i++;
	}
	
	if(i>*n){
		return 0;
	}else{
		return 1;
	}
}



/* Fonction qui permet la controle de saisie des date:
	* Condition d'acception : 
		- Date de fabrication valide
		- Date de preemption valide et plus grande que la date de fabrication */
void dateControle(Lot *lot){
	int correct=1;
	
	do{
	
		printf("Donner le jour du fabrication : ");
		scanf("%d",&lot->dateFabrication.jour);
		printf("Donner le mois du fabrication : ");
		scanf("%d",&lot->dateFabrication.mois);
		printf("Donner l'annee du fabrication : ");
		scanf("%d",&lot->dateFabrication.annee);
		
		switch(lot->dateFabrication.mois)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 12:
			if(lot->dateFabrication.jour>31){
				correct=0;
			}else{
				correct=1;
			}
			break;
			
			case 4:
			case 6:
			case 9:
			case 10:
			case 11:
				if(lot->dateFabrication.jour>30)
				{
					correct=0;
				}else{
					correct=1;
				}	
				
			break;
			
		case 2 :
		
   			if(((lot->dateFabrication.annee/4==0)&&(lot->dateFabrication.annee/100!=0))||((lot->dateFabrication.annee/400)==0)){
   				if(lot->dateFabrication.jour>29){
   					correct=0;
				}else{
					correct = 1;
				}  
			}
			else{
				if(lot->dateFabrication.jour>28){
					correct=0;
				}else{
					correct = 1;
				}
			}	
		break;
		default:
			correct=0;		
		}
		
	}while(correct==0);
	
	int correctP=1;
	int correctPDat=1;

}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/


void ajouterLot(Produit *prod,Produit *ProdTab, int *n){
	Lot lot;
	if(*n == 0 ){ /* Si c est le premier médicament a ajouter il est inutile de chercher la reference si'il est valide ou non */
		printf("Donner le lot du produit : ");
		fflush(stdin);
		gets(lot.reference);
		dateControle(&lot); /* Appel de la fonction dateControle() */
	}else{
		do{
			printf("Donner le lot du produit : ");
			fflush(stdin);
			gets(lot.reference);
		}while(rechercheReference(&*ProdTab,n,lot.reference)!=0); /* Appel de la fonction rechercheReference() */
		dateControle(&lot); /* Appel de la fonction dateControle() */
	}
	
	printf("\nLot ajouter avec succes\n");
	prod->lot=lot;
	
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/




void ajouterNouveauProduit(Produit *ProdTab,int *n){
	Produit prod;
	int i;
	/* Ouverture du fichier FMed.txt en mode ecriture binaire */
	FILE * FProd = fopen("FProd.txt","wb");
	if(FProd == NULL){
		printf("\nERREUR : Impossible d ouvrir le fichier.");
		exit(1);
	}

		if(*n == 0){
			prod.num=*n+1;
		}else{
			prod.num=ProdTab[*n-1].num+1;
	
		}
		
	
		printf("Donner le nom du produit : ");
		fflush(stdin);//?
		gets(prod.nom);
		printf("Donner le modell du produit : ");
		gets(prod.model);	
		
		ajouterLot(&prod,&*ProdTab,n); /* Appel de la fonction ajouterLot */ 
		
		printf("Donner le prix du produit : ");
		scanf("%f",&prod.prix);
		printf("Donner la quantite en stock du produit : ");
		scanf("%d",&prod.quantiteStock);
		
		ajouterFournisseur(&prod); /* Appel de la fonction ajouterFournisseur */
		do{
			printf("Donner le secteur de stockage du produit : ");
			scanf("%d",&prod.secteurStockage);
		}while(prod.secteurStockage<1 || prod.secteurStockage > 5);
		
	
		ProdTab[*n]=prod; /* Sauvegarde du médicament dans la case correspondante  */ 
		*n=*n+1;

	printf("\nProduit ajouter avec succees\n");
	fwrite (ProdTab, sizeof(Produit),*n, FProd ); /* Sauvegrade des informations de tout les medicaments dans le ficher FMed.txt */
	fclose(FProd);

}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/


