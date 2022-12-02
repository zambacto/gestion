
/* Fonction qui prend en paramètre le numero du médicament a chercher et qui :
	- Retourne -1 si aucun medicament trouvé
	- Retourne la quantité en stock du médicament trouvé  */
int rechercherProduitOrd(Produit *ProdTab, int n, int prodNum, int *indice){
	int numEl = n, i = 0;
	
	
	if(prodNum>ProdTab[numEl-1].num || prodNum <ProdTab[0].num){
		return -1;
	}else{
		while((ProdTab[i].num != prodNum) && (i < n)){
			i++;
		}
		if (i > (numEl-1)){
			return -1;
		}else{
			*indice = i;
			return ProdTab[i].quantiteStock;
		}	
	}
}


/* --------------------------------------------------------------------------------------------------------------------------------------------*/



/* Fonction qui permet a l'utilisateur de saisir la liste des médicaments a vendre et qui affiche les informations
	des médicaments et calcul et affiche le total */
void servirCommande (Produit *ProdTab, int n){
	int i,comm,quantite,resultatRecherche,compteur=0;
	int tabNumProduit[100];
	int tabQuantiteProduit[100];
	float total;
	int indice;
	
	do{
		printf("\nDonner le(s) numero(s) du produit a acheter ou -1 pour terminer la commande : ");
		scanf("%d",&comm);
		resultatRecherche = rechercherProduitOrd(&*ProdTab,n,comm,&indice); /* Appel de la fonction rechercherMedicamentOrd et stockage du variable retourné dans resultatRecherche */
		if(comm != -1){
			if(resultatRecherche != -1){
				 if(resultatRecherche == 0){
					printf("\nProduit Hors Stock !");
				}else{
					tabNumProduit[compteur]=indice; /* Sauvegarde du numero de la case du medicament dans tabNumMedicament  */
					do{
						printf("Donner la quantite du produit a acheter : ");
						fflush(stdin);
						scanf("%d",&quantite);
					}while(quantite > resultatRecherche || quantite <= 0);
					tabQuantiteProduit[compteur]=quantite; /* Sauvegarde de la quantité du medicament acheter dans tabQuantiteMedicament   */
					compteur++;
				}
				
			
			}else{
				printf("Produit introuvable ! s il vous plait saisir un numero valide.");
			}
		}
		
	}while(comm != -1);
	printf("\n-------------------Commande-----------------------");
	printf("\nNum\tNom\tQuantite\tPrix Unitaire");
	printf("\n----------------------------------------------------");
	total = 0;
	for(i=0;i<compteur;i++){
		printf("\n%6d\t%s\t%6d\t%.3f",ProdTab[tabNumProduit[i]].num,ProdTab[tabNumProduit[i]].nom,tabQuantiteProduit[i],ProdTab[tabNumProduit[i]].prix);
		total += ProdTab[tabNumProduit[i]].prix * tabQuantiteProduit[i]; 
		ProdTab[tabNumProduit[i]].quantiteStock = ProdTab[tabNumProduit[i]].quantiteStock - tabQuantiteProduit[i]; /* Soustraction du quantité acheter de la quantité en stock */
	}
	printf("\n\t\t\t---------------------");
	printf("\n\t\tTOTAL : \t %.3f \tTND",total);
	printf("\n\n");
	
	
	FILE *FProd = fopen("FProd.txt","wb");
	if(FProd == NULL){
	printf("\nERREUR: Impossible d ouvrir le fichier.");
	exit(1);}
	
	fwrite (ProdTab, sizeof(Produit),n, FProd );
	fclose(FProd);
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/

