#include "gestionPharmacie.h"
#include "ajouterMedicament.c"
#include "servirOrdonnance.c"
#include "afficherMedRechercher.c"


void ajouterNouveauProduit();
void afficherProduitQuiCommence();
void ajouterFournisseur();
void ajouterLot();
void ajouterNouveauProduit();
void dateControle();
void numProdCorresp();
void QauntiteProd();
int rechercheReference();
int rechercherProduittOrd();
void servirCommande();
int string_compare();
void suppMedic();


int main(){
	int numElements,n,i=0; /* variables locales de main */
	Produit tabProd[taille];
	
	/* Ouverture du fichier FMed.txt qui contient les informations des produit */
	FILE *FProd = fopen("FProd.txt","rb");
	if(FProd == NULL){
		printf("\nERREUR: Impossible d ouvrir le fichier.");
		exit(1);
	}
	
	/* Chargement des informations dans un tableau tabProd */
	fread(&tabProd,sizeof(tabProd) , 1 , FProd);
	fclose(FProd);
	
	/* Boucle qui permet de calculer le nombre des produit enregistr? */
	while(strcmp(tabProd[i].nom,"")){
		i++;
	}
	
	numElements = i;
	
	while(1){
		int choix;
		printf("\t\t\t\t ___________________________________________________\n");
		printf("\t\t\t\t| -------- Base de donnees de X --------            | \n");
		printf("\t\t\t\t| 1  : Afficher la liste des Produits               | \n");
		printf("\t\t\t\t| 2  : Ajouter Produit                              | \n");
		printf("\t\t\t\t| 3  : Consulter la quantite d'un Produit           | \n");
		printf("\t\t\t\t| 4  : Consulter les fournisseur d'un Produit       | \n");
		printf("\t\t\t\t| 5  : Servir une commande                          | \n");
		printf("\t\t\t\t| 6  : Supprimer un Produit du stock                | \n");
		printf("\t\t\t\t| 7  : Chercher un Produit                          | \n");
		printf("\t\t\t\t| 8 : Chercher le numero du Produit                 | \n");
		printf("\t\t\t\t| 0  : Quitter la base de donnes                    | \n");
		printf("\t\t\t\t|___________________________________________________| \n");
		printf("\n");
	do{
		printf("Donner votre choix : ");
		scanf("%d",&choix);
		printf("\n");
	}while(choix<0 || choix >8);	
	
	switch(choix){
			case 1: 
				affichProduit(tabProd,numElements);
				break;
			case 2: 
				ajouterNouveauProduit(tabProd, &numElements);
				break;
			case 3:
				QauntiteProd(tabProd,numElements);
				break; 
			case 4:
				affichFournisseurProd(tabProd,numElements);
				break;
			case 5:
				servirCommande(tabProd,numElements);
				break;
			case 6:
				suppProd(tabProd,&numElements);
				break;
			case 7:
				afficherProduitQuiCommence(tabProd, numElements);
				break;
			case 8:
				numProdCorresp(tabProd, numElements);
				break;
			case 0: 
				exit(0);
		}
	}

	system("pause");
	return 0;

}










void affichProduit(Produit *Prodtab, int n)
{ 
	int i;  

	printf ("---------------------------------------------------------------------------------------------------------------\n");
	printf("  Num\t\tNom\t\tmodel\t\tRefLot\t\tPrix\t\tQuantite\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{
			if(Prodtab[i].quantiteStock != 0){
				printf ("%3d\t\t%s\t\t%s\t\t%s\t\t%-5.3f\t\t%d\n",Prodtab[i].num,Prodtab[i].nom,Prodtab[i].model,Prodtab[i].lot.reference,Prodtab[i].prix,Prodtab[i].quantiteStock);	
			}
		}
		
}




void affichFournisseurProd(Produit *Prodtab,int n){
	int num;
	do{
		printf("Donner le numero du produit : ");
		scanf("%d",&num);
	}while(num<=0);
	int i;
	int j;
	int trouve=0;
	printf ("------------------------------------------------------------------------\n");
	printf("  Num_Produit\tNom\t\tAdresse\t\tTelephone\n");
	printf("-------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{	
			if(Prodtab[i].num==num){
				for(j=0;j<Prodtab[i].nombreFournisseur;j++){
					printf("\t%d \t\t%s \t\t%s \t%d\n",Prodtab[i].num,Prodtab[i].listeFournisseur[j].nom,Prodtab[i].listeFournisseur[j].adresse,Prodtab[i].listeFournisseur[j].telephone);
					trouve=1;
				}	
			}	
		}
		printf("\n\n");	
		
	if (trouve==0){
		printf("\nProdusanconnu!\n");
	}
}

