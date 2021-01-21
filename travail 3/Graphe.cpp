/*
 * Graphe.cpp
 */

#include "Graphe.hpp"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>


using namespace std;



Graphe::Graphe( void )
{

}


Graphe::~Graphe( void )
{
    // Puisque _adjacences n'est pas un pointeur il est automatiquement desalloue.
    // Le destructeur de vector s'occupe d'appeler les destructeurs sur chacun de
    // ses elements.
    // Il n'est donc pas utile de desallouer les elements.
}


void
Graphe::ajouterArcs( int a_sommet1, int a_sommet2, int a_longueur, string a_nom )
{
    int tailleMinimum = a_sommet1 < a_sommet2 ? a_sommet2 : a_sommet1;
    while ( _adjacences.size() <= tailleMinimum )
    {
        _adjacences.push_back( new vector< Arc * >() );
    }

    assert( 0 <= a_sommet1 && a_sommet1 < _adjacences.size() );
    assert( nullptr != _adjacences[a_sommet1] );
    _adjacences[a_sommet1]->push_back( new Arc( a_sommet2, a_longueur, a_nom ) );

    assert( 0 <= a_sommet2 && a_sommet2 < _adjacences.size() );
    assert( nullptr != _adjacences[a_sommet2] );
    _adjacences[a_sommet2]->push_back( new Arc( a_sommet1, a_longueur, a_nom ) );
}


/**
 * remplirMatriceAdjacence Convertit une liste d'adjacences en une matrice.
 * Un sommet inatteignable aura une valeur de distance egale a 999 (infini).
 *
 * @param d Un vecteur de distances.
 */
void
Graphe::remplirMatriceAdjacence(vector<vector<int>> &d) {
    //remplissage de la matrice : D<-M
    for (unsigned i = 0; i < _adjacences.size(); i++) {
        for (auto j : *_adjacences[i]) {
            d[i][j->sommetArrive] = j->longueur;
        }
    }

    //remplir autres cases par infini(999)
    for (unsigned i = 0; i < d.size(); i++) {
        for (unsigned j = 0; j < d.size(); j++) {
            if (i != j && (d[i][j] == 0)) {
                d[i][j] = 999;
            }
        }
    }

}


/**
 * remplirMatriceRoutePrececente Construit une matrice de route precedente selon la liste d'adjacences.
 * Un sommet inatteignable aura une valeur de sommet egale a 999 (infini).
 *
 * @param pi Un vecteur de passage precedent.
 */
void
Graphe::remplirMatriceRoutePrececente(vector<vector<int>> &pi) {
    for (unsigned i = 0; i < _adjacences.size(); i++) {
        for (auto j : *_adjacences[i]) {
            pi[i][j->sommetArrive] = i;
        }
    }

    //remplir pi, autre case ont infini ou un nombre
    for (unsigned i = 0; i < pi.size(); i++) {
        for (unsigned j = 0; j < pi.size(); j++) {
            if (i == j) {
                pi[i][j] = i;
            }
        }
    }
}


/**
 * plusCourtChemin Determine le plus court chemin entre chaque destination selon l'algorithme Floyd-Warshall.
 * La matrice de distances et de passage precedent sont remplies et finalises.
 */
void
Graphe::plusCourtChemin( void )
{
    vector<vector<int>> d(_adjacences.size(), vector<int>(_adjacences.size()));
    vector<vector<int>> nouvelleMatrice(_adjacences.size(), vector<int>(_adjacences.size()));
    vector<vector<int>> pi(_adjacences.size(), vector<int>(_adjacences.size()));
    vector<vector<int>> t(_adjacences.size(), vector<int>(_adjacences.size()));
    vector<vector<int>> p(_adjacences.size(), vector<int>(_adjacences.size()));

    int i, k, j;
    remplirMatriceAdjacence(d);
    remplirMatriceRoutePrececente(pi);

    for (k = 0; k < d.size(); ++k)
    {
        t = d;// T <- D
        p = pi;// P <- pi
        d = nouvelleMatrice;// D <- nouvelle matrice n x n

        for (i = 0; i < d.size(); ++i)
        {
            for (j = 0; j < d.size(); ++j)
            {
                if (t[i][k] + t[k][j] < t[i][j])
                {
                    d[i][j] = t[i][k] + t[k][j];
                    pi[i][j] = k;
                }
                else
                {
                    d[i][j] = t[i][j];
                }
            }
        }
    }

    acces = _adjacences;
    leMatrice = d;
    leChemin = pi;
}


ostream &
operator <<( ostream & a_out, Graphe const & a_graphe )
{
    int i = 0;
    int j = 0;

    for ( i = 0; i < a_graphe._adjacences.size(); ++ i )
    {
        a_out << i << " : ";
        for ( j = 0; j < a_graphe._adjacences[i]->size(); ++ j )
        {
            if ( 0 != j )
            {
                a_out << ", ";
            }
            a_out << *( a_graphe._adjacences[i]->at(j) );
        }
        a_out << endl;
    }

    return a_out;
}
