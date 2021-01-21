/*
 * TP3.cpp
 *
 */

#include "DocumentXML.hpp"
#include "ElementXML.hpp"
#include "Graphe.hpp"
#include "Lecteur.hpp"

#include <cassert>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

Graphe *
construireGraphe(string a_nomFichier)
{
    Graphe *resultat = new Graphe();
    DocumentXML *carteXML = lireFichierXML(a_nomFichier);

    assert(nullptr != carteXML);
    ElementXML *courant = carteXML->racine();

    assert(nullptr != courant);
    courant = courant->prochainElement();

    assert(nullptr != courant);
    for (NoeudXML *contenu : *courant)
    {
        assert(nullptr != contenu);
        if (contenu->estElement())
        {
            ElementXML *temp = (ElementXML *)contenu;

            assert(nullptr != resultat);
            assert(nullptr != temp);
            resultat->ajouterArcs(
                stoi(temp->attribut(string("inter_1"))),
                stoi(temp->attribut(string("inter_2"))),
                stoi(temp->attribut(string("longueur"))),
                temp->attribut(string("nom_rue")));
        }
    }
    return resultat;
}

vector<int> *
lireDestinations(istream &a_in)
{
    vector<int> *resultat = new vector<int>();
    string reponseUtilisateur;

    cout << "Entrez vos destinations separees par des espaces : ";
    getline(cin, reponseUtilisateur);

    istringstream entrees(reponseUtilisateur);

    while (!entrees.eof())
    {
        int dest = 0;
        entrees >> dest;
        if (!entrees.fail())
        {
            resultat->push_back(dest);
        }
    }

    return resultat;
}

/**
 * [imprimerChemin Affiche le sommet et le nom du chemin emprunte.]
 *
 * @param a_ruesMontreal [Un graphe contenant les noms de rues et les sommets.]
 * @param i              [L'index utilise dans la matrice des chemins precedents.]
 * @param j              [L'index utilise dans la matrice des chemins precedents.]
 */
void imprimerChemin(Graphe *a_ruesMontreal, int i, int j, stack<int> &pile, stack<int> &afficheAvant)
{
    pile.push(j);
    if (i != j)
    {
        imprimerChemin(a_ruesMontreal, i, a_ruesMontreal->leChemin[i][j], pile, afficheAvant);
    }

    unsigned int routeCourante;
    if (!pile.empty())
    {
        routeCourante = pile.top();
        pile.pop();
    }

    if (j != afficheAvant.top())
    {
        cout << j << ", ";
    }
    for (auto rue : *a_ruesMontreal->acces[routeCourante])
    {
        if (!pile.empty())
        {
            if (pile.top() == rue->sommetArrive)
            {
                cout << rue->nom << ", ";
            }
        }
    }
}

/**
 * calculerChemin Calcule la distance du chemin entre deux endroits.
 *
 * @param a_ruesMontreal [Un graphe contenant les noms de rues et les sommets.]
 * @param i              [L'index utilise dans la matrice des chemins precedents.]
 * @param j              [L'index utilise dans la matrice des chemins precedents.]
 * @param distance       [La valeur de distance.]
 */
void calculerChemin(Graphe *a_ruesMontreal, int i, int j, int &distance)
{

    if (i != j)
    {
        calculerChemin(a_ruesMontreal, i, a_ruesMontreal->leChemin[i][j], distance);
    }

    distance = distance + a_ruesMontreal->leMatrice[i][j];
}

/**
 * [afficherMeilleurTrajet Calcule et affiche le plus cours trajet atteignant certains noeuds.]
 *
 * @param a_ruesMontreal [Un graphe contenant les noms de rues et les sommets.]
 * @param a_destinations [Un vecteur contenant les destinations a visiter.]
 */
void afficherMeilleurTrajet(Graphe *a_ruesMontreal, vector<int> *a_destinations)
{
    stack<int> pile, afficheAvant;
    afficheAvant.push(20);

    if (a_destinations->size() == 1)
    {
        cout << a_destinations[0][0];
    }
    else
    {
        int t = 0;
        int distance;
        int distanceTemp;
        int c = 2;

        /*
        //permutations et calcul de distance minimale
        do {
            for (int a = 0; a < a_destinations->size()-1; ++a)
            {

                    for (int b = a+1; b < a_destinations->size(); ++b)
                    {

                    distanceTemp = distance;
                    calculerChemin(a_ruesMontreal, i, j, distance);
                    if (distance < distanceTemp)
                    {
                        distanceTemp = distance;
                    }

                    cout << a_destinations[0][a] << "," << a_destinations[0][b] << endl;
                    }

            }
        } while (next_permutation(a_destinations->begin(),a_destinations->end()));
        */

        while (c <= a_destinations->size())
        {
            int i = a_destinations[0][0 + t];
            int j = a_destinations[0][1 + t];

            imprimerChemin(a_ruesMontreal, i, j, pile, afficheAvant);
            afficheAvant.push(j);
            ++t;
            ++c;
        }
    }
    cout << endl;
    while (!afficheAvant.empty())
    {
        afficheAvant.pop();
    }
}

int main(int argn, char *argv[])
{
    Graphe *ruesMontreal = construireGraphe("map_montreal.xml");

    ruesMontreal->plusCourtChemin();

    vector<int> *destinations = lireDestinations(cin);

    if (0 < destinations->size())
    {
        afficherMeilleurTrajet(ruesMontreal, destinations);
    }

    return 0;
}