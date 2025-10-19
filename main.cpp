#include <iostream>
using namespace std;


// Structure d’un nœud d’ABR

struct noeud {
    int cle;
    noeud *gauche;
    noeud *droite;
    noeud *pere;
};
//creation de l'arbre
void createUser(noeud** racine)
{
    noeud* newNoeud = new noeud;
    cout << "Entrer un nombre : ";
    cin >> newNoeud->cle;
    *racine = newNoeud;
    char reponse;
    cout << "Voulez vous un fils gauche (O/N) : ";
    cin >> reponse;
    if (reponse == 'o' || reponse == 'O')
    {
        createUser(&(*racine)->gauche);
    }
    else if (reponse == 'n' || reponse == 'N')
    {
        createUser(&(*racine)->droite);
    }
    else
    {
        (*racine)->gauche = NULL;
        (*racine)->droite = NULL;
    }
}
noeud* rechercheMin(noeud* racine)
{
    if(racine == NULL) return NULL;
    if(racine->gauche == NULL) return racine;
   
    return rechercheMin(racine->gauche);
}
noeud* rechercheMax(noeud* racine)
{
    if(racine == NULL) return NULL;
    if(racine->droite == NULL) return racine;
   
    return rechercheMax(racine->gauche);
}

noeud* rechercheSucc(noeud* racine)
{
    if(racine == NULL) return NULL;
    if (racine->droite != NULL) return rechercheMin(racine->droite);
    noeud* father = racine->pere;
    while (father != NULL && racine == racine->pere)
    {
        racine = father;
        father = father->pere;
        return father;
    }
    return racine;
}
noeud* rechercheSuccRec(noeud* x)
{
    if(x->droite != NULL)
        return rechercheMin(x->droite);
    if(x->pere == NULL) return NULL;
    if(x->pere->gauche == x) return x->pere;
    return rechercheSuccRec(x->pere);
}

noeud* recherchePre(noeud* racine)
{
    if(racine == NULL) return NULL;
    if (racine->droite != NULL) return rechercheMax(racine->gauche);
    noeud* father = racine->pere;
    while(father!=NULL && racine == racine->pere)
    {
        racine = father;
        father = father->pere;
        return father;
    }
    return racine;
}
noeud* recherchePreRec(noeud* y)
{
    if(y->gauche != NULL)
        return rechercheMax(y->gauche);
    if(y->pere == NULL) return y->pere;
    if(y->pere->droite == y) return y->pere;
    return recherchePreRec(y->pere);
}
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
void insertRec(noeud* racine, noeud* insert)
{
    if (racine == NULL) insert = racine;
    else
    {
        if(insert->cle < racine->cle)
            insertRec(racine->gauche, insert);
        else if(insert->cle > racine->cle)
            insertRec(racine->droite, insert);
    }
    
}
bool supprimeIter(noeud** racine, noeud* courant)
{
    noeud* rattache;
    noeud* asupprimer;
    if(courant == NULL) return false;
    if (courant->gauche == NULL || courant->droite == NULL)
    {
        asupprimer = courant;
    }
    else
    {
        asupprimer = rechercheSucc(courant);
        courant->cle = asupprimer->cle;
    }
    if (asupprimer->gauche == NULL)
        rattache = asupprimer->droite;
    else
        rattache = asupprimer->gauche;
    if(rattache != NULL)
        rattache->pere = asupprimer->pere;
    if(rattache->pere == NULL) *racine = rattache;
    else
    {
        if(asupprimer->pere->droite == asupprimer)
            asupprimer->pere->droite = rattache;
        else
            asupprimer->pere->gauche = rattache;
    }
    return true;
}
bool supprimerRec(noeud** racine, noeud* x) {
    if (x == NULL) return false; // rien à supprimer

    // Cas 2 fils
    if (x->gauche != NULL && x->droite != NULL) {
        // Trouver le successeur (minimum du sous-arbre droit)
        noeud* succ = rechercheMin(x->droite);
        x->cle = succ->cle;                  // copier la valeur
        return supprimerRec(racine, succ);  // supprimer le successeur récursivement
    }

    // Cas 0 ou 1 fils
    noeud* fils;
    if (x->gauche != NULL)
        fils = x->gauche;
    else
        fils = x->droite;

    // Rattacher le fils au parent
    if (x->pere != NULL) {
        if (x->pere->gauche == x)
            x->pere->gauche = fils;
        else
            x->pere->droite = fils;
    } else {
        *racine = fils; // x est la racine
    }

    // Mettre à jour le parent du fils
    if (fils != NULL)
        fils->pere = x->pere;

    // Supprimer le nœud
    delete x;
    return true;
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
