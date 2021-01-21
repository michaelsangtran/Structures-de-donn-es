/*
 * Graphe.hpp
 *
 */

#ifndef TP3_GRAPHE_HPP_
#define TP3_GRAPHE_HPP_


#include "Arc.hpp"
#include "Graphe.hpp"

#include <iostream>
#include <vector>

using namespace std;

class Graphe
{
private:
    vector< vector< Arc * > * > _adjacences;
public:
    Graphe( void );
    virtual ~Graphe( void );

    void ajouterArcs( int a_sommet1, int a_sommet2, int a_longueur, string a_nom );
    void remplirMatriceAdjacence(vector<vector<int>> &d);
    void remplirMatriceRoutePrececente(vector<vector<int>> &pi);
    void plusCourtChemin( void );

    vector<vector<int>> leMatrice;
    vector<vector<int>> leChemin;
    vector< vector< Arc * > * > acces;

    friend ostream & operator <<( ostream &, Graphe const & );
};


#endif /* TP2_GRAPHE_HPP_ */
