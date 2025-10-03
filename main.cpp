#include <iostream>
#include <string>
using namespace std;
// Arbre binaire de recherche
//creation d'un arbre binaire de recherche
struct noeud
{
    int cle;
    noeud* gauche;
    noeud* droite;
    noeud* pere;
};
void createUser(noeud** racine)
{
    noeud* newNode = new noeud;
    newNode->pere = NULL;
    newNode->gauche = NULL;
    newNode->droite = NULL;
    cout << "Entrer une valeur : ";
    cin >> newNode->cle;
    *racine = newNode;
    char reponse;
    cout << "Voulez vous d'un fils gauche O/N: ";
    cin >> reponse;
    if (reponse == 'o' || reponse == 'O' )
    {
        createUser(&(*racine)->gauche);
        (*racine)->gauche->pere = *racine;
    }
    cout << "Voulez vous d'un fils droite O/N: ";
    cin >> reponse;
    if (reponse == 'o' || reponse == 'O')
    {
        createUser(&(*racine)->droite);
        (*racine)->droite->pere = *racine;
    }
}
void AfficheArbre(noeud* racine)
{
    if (racine == NULL) return;
    
    AfficheArbre(racine->gauche);
    cout << racine->cle << " -> ";
    AfficheArbre(racine->droite);
    cout << endl;
}
//Requetes
noeud* noeudValue(noeud* racine, int cleRecherche)
{
    if(racine == NULL) return NULL;
    if (racine->cle == cleRecherche)
    {
        return racine;
    }
    if (racine->cle > cleRecherche)
    {
        return  noeudValue(racine->gauche, cleRecherche);
    }
    return noeudValue(racine->droite, cleRecherche);
}
noeud* rechercheCleMin(noeud* racine)
{
    if (racine == NULL) return NULL;
    if (racine->gauche == NULL)
    {
        return racine;
    }
    return rechercheCleMin(racine->gauche);
    
}
noeud* rechercheCleMax(noeud* racine)
{
    if (racine == NULL) return NULL;
    if (racine->droite == NULL)
    {
        return racine;
    }
    return rechercheCleMax(racine->droite);
}
// le predecesseur est le maximum de sa sous arbre gauche
// si le noeud n'a pas de sous arbre gauche son predecesseur est le premier ancetre dont son sous arbre droite contient le noeud
noeud* recherchePre(noeud* racine)
{
    if (racine == NULL)return  NULL;
    if (racine->gauche != NULL)
    {
        return rechercheCleMax(racine->gauche);
        noeud* father = racine->pere;
        while (father != NULL && father->gauche == racine)
        {
            racine = father;
            father = father->pere;
        }
        return father;
    }
    return racine;
    
}

int main(int argc, const char * argv[])
{
    int cle;
    cout << "Entrer le cle recherche : ";
    cin >> cle;
    noeud* newNode = NULL;
    createUser(&newNode);
    AfficheArbre(newNode);
    noeud* recherche = noeudValue(newNode, cle);
    cout << " L'adresse du cle est : " << recherche << endl;
    cout << endl;
    //noeud* result1 = rechercheCleMin(newNode);
    //noeud* result2 = rechercheCleMax(newNode);
    //cout << " le min de l'arbre est : " << result1->cle << " et le max de l'arbre est : " << result2->cle << endl;
    
    
    
    
    return 0;
}
