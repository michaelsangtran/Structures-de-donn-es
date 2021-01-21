/*
 * Arc.hpp
 *
 */

#ifndef TP3_ARC_HPP_
#define TP3_ARC_HPP_

#include <iostream>
#include <string>


using namespace std;


class Arc
{
public:
    int sommetArrive;
    int longueur;
    string nom;

    Arc( int a_sommetArrive, int a_longueur, string a_nom );
    virtual ~Arc( void );

    friend ostream & operator <<( ostream &, Arc const & );
};


#endif /* TP3_ARC_HPP_ */
