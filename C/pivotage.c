#include <stdio.h>
#include <stdlib.h>

/**
 * Creation d'une matrice a n ligne et p colonne
*/
float** createMatrice(int n, int p);
/**
 * Creation d'un vecteur a n element
*/
float * createVecteur(int n);
/**
 * Affiche une matrice
*/
void displayMatrice(float**matrice,int n,int p,char name);
/**
 * Affiche le resultat du pivotage d'une matrice par rapport
 * au (n,p) element
*/
void showResults(float** matrice ,int n,int p , int n_element , int p_element);
/**
 * Faire le pivotage de la matrice A 
 * par rapport a l'element A[n_element][p_element]s
*/
void pivotageGaussJordan(float** A , int n , int p, int n_element,int p_element);
/**
 * Recuperation des donnees de la matrice dans un fichier
 * n : le nombre de ligne
 * p : le nombre de colonne
 * n_e : le numero de la ligne pivot
 * p_e : le numero de la colonne pivot
*/
void getData(int *n,int *p,int *n_e,int *p_e, float *** A );

int main(){
/// Presentation
    printf("Ce programme permet de faire le pivotage d'une matrice A donnee par rapport a un element de la matrice en n^eme ligne et p^eme colonne\n");

/// Data
    int     n = 4 , p = 8   ;           // Le nombre de ligne et de colonne
    float** matrice     = NULL;         // La matrice a pivoter
    int     n_element   = 0 ;           // Le numero de la ligne de l'element 
    int     p_element   = 1 ;           // Le numero du colonne de l'element

    getData(&n , &p ,&n_element ,&p_element,&matrice);

/// Traitement
    pivotageGaussJordan(matrice,n,p,n_element,p_element);
/// Resultats
    showResults(matrice,n,p,n_element,p_element);
}
/**
 * Recuperation des donnees de la matrice dans un fichier
 * n : le nombre de ligne
 * p : le nombre de colonne
 * n_e : le numero de la ligne pivot
 * p_e : le numero de la colonne pivot
*/
void getData(int *n,int *p,int *n_e,int *p_e, float *** A ){
    float **M = NULL ;
    FILE *pf = NULL; // Pointeur du fichier
    pf = fopen("pivotage.txt","r"); // Ouvrir le fichier et indiquer son mode d'ouverture read , write , rw , append
    if(pf != NULL){
        fscanf( pf ,"%d",n); // Recuperer le nombre de ligne
        fscanf( pf ,"%d",p); // Recuperer le nombre de colonne
        fscanf( pf ,"%d",n_e); // Recuperer le num de ligne du pivot
        fscanf( pf ,"%d",p_e); // Recuperer le num colonne du pivot 
        M =createMatrice(*n , *p);
        for(int i = 0; i < *n; i++){
            for(int j = 0; j < *p ;j++){ 
                fscanf( pf,"%f", &M[i][j] ); // data ligne par ligne
                printf( " %f ",M[i][j]);
            }
            printf("\n");
        }
        fclose( pf );
    }
    else{
        printf("Ne peut recuperer la data\n");
    }

    /// Renvoie des donnees
    *A = M;
}
/**
 * Faire le pivotage de la matrice A 
 * par rapport a l'element A[n_element][p_element]s
*/
void pivotageGaussJordan(float** A , int n , int p, int n_element,int p_element){
    float facteur = A[n_element][p_element];   // Facteur du pivot
    for (int i = 0; i < p; i++)
    {
        A[n_element][i] = A[n_element][i]/facteur;
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        // on ne transforme pas si c'est la ligne de l'element 
        if (i == n_element) {
            continue;
        }
        facteur = (-A[i][p_element] / (A[n_element][p_element]));
        printf("Facteur de la ligne[%i] = %f\n",i,facteur);
        for (int j = 0; j < p; j++) {
            A[i][j] = A[i][j] + (A[n_element][j] * facteur);
        }
    }
}

/**
 * Affiche une matrice
*/
void displayMatrice(float**matrice,int n , int p,char name){
    printf(">> [%c] (%i,%i)\n",name,n,p);
    for (int i = 0; i < n; i++)
    { 
        printf("\t|");
        for (int j = 0; j < p; j++)
        {
            printf("\t%.2f",matrice[i][j]);   
        }
        printf("\t|\n");
    }
}

/**
 * Creation d'un vecteur a n element
*/
float * createVecteur(int n){
    float * vect = malloc(n*sizeof(float));
    for (int i = 0; i < n; i++) {
        vect[i] = 0;
    }
    return vect;
}

/**
 * Creation d'une matrice a n ligne et p colonne
*/
float** createMatrice(int n, int p){
    float** matrice = malloc( n * sizeof(float*));
    for (int i = 0; i < n; i++)
    {
        matrice[i] = createVecteur(p);
    }
    return matrice;
}

/**
 * Affiche le resultat du pivotage d'une matrice par rapport
 * au (n,p) element
*/
void showResults(float** matrice , int n, int p , int n_element , int p_element){
    printf("Pour le pivotage de la matrice par rapport au (%i,%i)\n",n_element,p_element);
    displayMatrice(matrice,n,p,'A');
}
