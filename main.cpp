#include <iostream>
using namespace std;


// Structure d’un nœud d’ABR

struct noeud {
    int cle;
    noeud *gauche;
    noeud *droite;
    noeud *pere;
};


// Insertion itérative dans un ABR

void insertNoeudIte(noeud **racine, noeud *insert) {
    noeud *tmp = *racine;
    noeud *father = NULL;

    while (tmp != NULL) {
        father = tmp;
        if (insert->cle < tmp->cle)
            tmp = tmp->gauche;
        else
            tmp = tmp->droite;
    }

    insert->pere = father;
    insert->gauche = NULL;
    insert->droite = NULL;

    if (father == NULL)
        *racine = insert; // arbre vide → racine
    else if (insert->cle < father->cle)
        father->gauche = insert;
    else
        father->droite = insert;
}

// Construire un ABR à partir d’un tableau
void createABRFromArray(noeud **racine, int tab[], int taille) {
    for (int i = 0; i < taille; i++) {
        noeud *n = new noeud;
        n->cle = tab[i];
        n->gauche = n->droite = n->pere = NULL;
        insertNoeudIte(racine, n);
    }
}

// Parcours infixe (affichage trié)
void AfficheArbre(noeud *racine) {
    if (racine == NULL) return;
    AfficheArbre(racine->gauche);
    cout << racine->cle << " ";
    AfficheArbre(racine->droite);
}

// Transformer un ABR → tableau trié
void arbreToArray(noeud *racine, int tab[], int *index) {
    if (racine == NULL) return;
    arbreToArray(racine->gauche, tab, index);
    tab[*index] = racine->cle;
    (*index)++;
    arbreToArray(racine->droite, tab, index);
}

void createArrayFromABR(noeud *racine, int tab[], int taille) {
    int index = 0;
    arbreToArray(racine, tab, &index);
}

// Tri d’un tableau avec un ABR
void triAvecABR(int tab[], int taille) {
    noeud *racine = NULL;
    createABRFromArray(&racine, tab, taille);
    createArrayFromABR(racine, tab, taille);
}


// Créer un ABR équilibré à partir d’un tableau trié

noeud* createABREquilibre(int tab[], int debut, int fin, noeud *pere = NULL) {
    if (debut > fin) return NULL;

    int milieu = (debut + fin) / 2;
    noeud *n = new noeud;
    n->cle = tab[milieu];
    n->pere = pere;
    n->gauche = createABREquilibre(tab, debut, milieu - 1, n);
    n->droite = createABREquilibre(tab, milieu + 1, fin, n);

    return n;
}


int main() {
    int tab[] = {12, 7, 15, 9, 3, 13, 17};
    int taille = 7;

    cout << "Tableau original : ";
    for (int i = 0; i < taille; i++) cout << tab[i] << " ";
    cout << "\n";

    //  Créer un ABR depuis le tableau
    noeud *racine = NULL;
    createABRFromArray(&racine, tab, taille);
    cout << "Affichage infixe (ABR trié) : ";
    AfficheArbre(racine);
    cout << "\n";

    //  Convertir ABR -> tableau trié
    int sorted[20];
    createArrayFromABR(racine, sorted, taille);
    cout << "Tableau trié via ABR : ";
    for (int i = 0; i < taille; i++) cout << sorted[i] << " ";
    cout << "\n";

    //  Trier directement un tableau via ABR
    int tab2[] = {5, 1, 8, 2, 9};
    int t2 = sizeof(tab2)/sizeof(tab2[0]);
    triAvecABR(tab2, t2);
    cout << "Tri avec ABR : ";
    for (int i = 0; i < t2; i++) cout << tab2[i] << " ";
    cout << "\n";

    //  Créer un ABR équilibré
    int tri[] = {1,2,3,4,5,6,7,8,9};
    int t3 = sizeof(tri)/sizeof(tri[0]);
    noeud *eq = createABREquilibre(tri, 0, t3 - 1);
    cout << "ABR équilibré (affichage infixe) : ";
    AfficheArbre(eq);
    cout << "\n";

    return 0;
}
