/*
 * Arc.cpp
 *
 */


#include "Arc.hpp"


#include <iomanip>
#include <iostream>
#include <string>


using namespace std;


Arc::Arc( int a_sommetArrive, int a_longueur, string a_nom )
: sommetArrive( a_sommetArrive ),
  longueur( a_longueur ),
  nom( a_nom )
{
}


Arc::~Arc( void )
{
}


ostream & operator <<( ostream & a_out, Arc const & a_arc )
{
    a_out << a_arc.nom << "(" << a_arc.longueur << "m) " << a_arc.sommetArrive;

    return a_out;
}

