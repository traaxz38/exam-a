#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRILLE_TAILLE 9 //taille de la grille (9 par 9)
#define LIST_TAILLE 9 //taille de la liste





/*
Pour l'exercice vous aurez besoin de generer des entiers aléatoire : rand() renvoit un entier aléatoire.
il s'utilise : rand() % NOMBREMAX + 1 
Pour un entier aléatoire entre 0 et 1 il faut donc faire rand() %2
voir dans la methode main.
*/

int nbA(){
    int n = rand()%10;
}

// Ecrire la fonction generer(), elle prend en paramètre la grille et renvoie le nombre d'éléments non nuls
int generer(int grille[GRILLE_TAILLE][GRILLE_TAILLE]){
    int tmp = 0;
    for (int i = 0; i < GRILLE_TAILLE; i++) {
        for (int j = 0; j <  GRILLE_TAILLE; j++) {
            if (grille[i][j] != 0)
            {
                tmp++;
            }  
        }
    }
    return tmp;
}
// Ce lien vous sera utile : https://www.geeksforgeeks.org/pass-2d-array-parameter-c/


/*Écrire une fonction saisir() qui demande à l’utilisateur de saisir au clavier les indices i et j et la valeur v à placer à l’emplacement (i,j).
La fonction doit vérifier la validité des indices et de la valeur.
Si la case n’est pas occupée, la valeur doit être placée dans la grille. remplissage est alors incrémentée*/
int saisir(int (*grille)[GRILLE_TAILLE]){
    int i,j,v = 0;
    printf("---------------------------------");
    printf("\n");
    for(i=0;i<9; ++i) 
    {
        for(j=0; j<9; ++j)
            printf("%d ", grille[i][j]);
        printf("\n");  
    }
    printf("---------------------------------");  
    printf("\n");

    
    printf("rentrer la ligne voulu \n");
    scanf("%d", &i-1);
    if (i<0 && i>9)
    {
        printf("mauvaise ligne\n");
        return 0;
    }
    printf("rentrer la colonne voulu \n");
    scanf("%d", &j-1);
    if (j<0 && j>9)
    {
        printf("mauvaise colonne\n");
        return 0;
    }

    printf("rentrer la valeur voulu \n");
    scanf("%d", &v);
    if (v<0 && v>9)
    {
        printf("mauvaise valeur\n");
        return 0;
    }

    if (grille[i][j] == 0)
    {
        grille[i][j] = v;
        verifierLigneColonne(v,i,j,grille[GRILLE_TAILLE][GRILLE_TAILLE],0);
        verifierLigneColonne(v,i,j,grille[GRILLE_TAILLE][GRILLE_TAILLE],0);
    }else{
        printf("il y a déjà une valeur ici");
        saisir(grille[GRILLE_TAILLE][GRILLE_TAILLE]);
    }
    
    return i,j,v;
}

/*
Écrire la fonction verifierLigneColonne() qui prend en paramètre un numéro et un sens (HORIZ ou VERT)
qui vérifie que la ligne ou la colonne (suivant les cas) numéro est bien remplie.
On pourra utiliser un tableau intermédiaire pour vérifier cela. La fonction retournera 1 si tout s’est bien passé, 0 sinon.
 Les constantes HORIZ de valeur 0 et VERT de valeur 1 sont à définir.
*/
int verifierLigneColonne(int valeur, int ligne, int colonne,int (*grille)[GRILLE_TAILLE], int sens){
    int a = sens;
    if (a == 0)
    {
        int tmp = 0;
        for (int i = 0; i < GRILLE_TAILLE; i++)
        {
            if (grille[i][colonne] == valeur)
            {
                tmp++;
            } 
        }
        if (tmp > 1)
        {
            printf("il y a déjà un %d sur cette colonne",valeur);
            grille[ligne][colonne] = 0;
            saisir(grille[GRILLE_TAILLE][GRILLE_TAILLE]);
        }else
        {
            return 1;
        }
    }else if (a == 1)
    {
        int tmp = 0;
        for (int i = 0; i < GRILLE_TAILLE; i++)
        {
            if (grille[ligne][i] == valeur)
            {
                tmp++;
            }    
        }
        if (tmp > 1)
        {
            printf("il y a déjà un %d sur cette ligne",valeur);
            grille[ligne][colonne] = 0;
            saisir(grille[GRILLE_TAILLE][GRILLE_TAILLE]);
        }else
        {
            return 1;
        }
    }
}

/*
Écrire la fonction verifierRegion() qui prend en paramètre deux indices k et l qui correspondent à la région (k,l)
et qui renvoie 1 si la région est correctement remplie, 0 sinon.
*/
int verifierRegion(int valeur, int ligne, int colonne,int (*grille)[GRILLE_TAILLE]){
    int tmp = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <  3; j++) {
            if (grille[i][j] == valeur)
            {
                tmp++;
            }
            
        }
    }
    if (tmp > 1)
        {
            printf("il y a déjà un %d dans cette region",valeur);
            grille[ligne][colonne] = 0;
            saisir(grille[GRILLE_TAILLE][GRILLE_TAILLE]);
        }else
        {
            return 1;
        }
    
}

//Écrire la fonction verifierGrille() qui renvoie 1 si la grille est correctement remplie et 0 sinon
int verifiergrille(int (*grille)[GRILLE_TAILLE]){
    int tmp = generer((*grille)[GRILLE_TAILLE]);
    int tmp1 = 0;
    if (tmp != 81)
    {
        printf("il reste des cases à remplir");
        return 0;
    }else 
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j <  3; j++) {
                int test = grille[i][j];
                tmp1 += verifierLigneColonne(test, i,j,grille[9][9],1);
                tmp1 += verifierLigneColonne(test, i,j,grille[9][9],0);
            }
        }
    }
    if (tmp1 == 162)
    {
        printf("la partie est reussi");
        return 1;
    }
    
}

//Écrire le programme principal, en supposant que la seule condition d’arrêt est la réussite du sudoku (ce test ne devra être fait que si nécessaire)
int final(int (*grille)[GRILLE_TAILLE]){
    int jeu = 1;
    while (jeu == 1)
    {
        saisir(grille[GRILLE_TAILLE][GRILLE_TAILLE]);
        if (generer(grille[GRILLE_TAILLE][GRILLE_TAILLE]))
        {
            if (verifiergrille((*grille)[GRILLE_TAILLE]) == 1)
        {
            printf("bravo !!!");
            return 0;
        }
        }
        
        
        
        
    }
    
}

int main(){
    // Ne pas toucher le code entre les commentaires
    srand( time( NULL ) );


    int i, j, k;
    int solution[9][9];
    printf("SOLUTION");  
    printf("\n");  
    printf("---------------------------------");  
    printf("\n");  
    for(j=0;j<9; ++j) 
    {
        for(i=0; i<9; ++i)
            solution[j][i] = (i + j*3 +j /3) %9 +1 ; 
    }
    
    for(i=0;i<9; ++i) 
    {
        for(j=0; j<9; ++j)
            printf("%d ", solution[i][j]);
        printf("\n");  
    }
    printf("---------------------------------");  
    printf("\n");  
    //toucher le code entre les commentaires 
    
    
      
    int grille[][GRILLE_TAILLE] = {0}; //création du tableau en 2D
    for (i = 0; i < GRILLE_TAILLE; i++){
        for (j = 0; j < GRILLE_TAILLE; j++) {
            int t = rand() % 2;
            if (t == 0)
            {
                grille[i][j] = 0;
            }else
            {
                grille[i][j] = solution[i][j];
            }
        }
    }
    printf("---------------------------------");
    printf("\n");
    for(i=0;i<9; ++i) 
    {
        for(j=0; j<9; ++j)
            printf("%d ", grille[i][j]);
        printf("\n");  
    }
    printf("---------------------------------");  
    printf("\n");
    final((*grille)[GRILLE_TAILLE]);
  



    //Ne pas toucher au code ci dessous
    system("pause");
    return 0;
}
