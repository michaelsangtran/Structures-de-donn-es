#ifndef _CONSTANTES_HPP
#define _CONSTANTES_HPP

#include <string>

using namespace std;


int const NOMBRE_DENT_MINIMUM = 6;
int const NOMBRE_SILLON_MINIMUM = 1;
int const NOMBRE_SILLON_MAXIMUM = 4;


/* Message */

string const MSSG_QUESTION_CONTINUER = "Voulez-vous lancer une autre analyse ? (‘n’ pour non, autre pour oui.)";
string const MSSG_REQUETE_VITESSE = "Quelle est la vitesse de rotation de la première composante ?";
string const MSSG_REQUETE_COUPLE = "Quel est le couple appliqué à la première composante ?";


/* Message d'erreur */


string const MSSG_ERR_COMPOSANTE_INVALIDE = "Composante invalide.";
string const MSSG_ERR_COUPLE_INVALIDE = "Ce n'est pas un couple valide.";
string const MSSG_ERR_FICHIER_INEXISTANT = "Le fichier n'existe pas.";
string const MSSG_ERR_LIEN_INVALIDE = "Lien invalide.";
string const MSSG_ERR_MEME_SIGNE = "Les deux valeurs doivent avoir le même signe.";
string const MSSG_ERR_NOMBRE_DENT_MINIMUM_P1 = "Il doit y avoir un minimum de ";
string const MSSG_ERR_NOMBRE_DENT_MINIMUM_P2 = " dents.";
string const MSSG_ERR_NOMBRE_DENT_MINIMUM = MSSG_ERR_NOMBRE_DENT_MINIMUM_P1 + 
                                            to_string( NOMBRE_DENT_MINIMUM ) + 
                                            MSSG_ERR_NOMBRE_DENT_MINIMUM_P2;
string const MSSG_ERR_NOMBRE_SILLON_P1 = "Le nombre de sillon doit etre entre ";
string const MSSG_ERR_NOMBRE_SILLON_P2 = " et ";
string const MSSG_ERR_NOMBRE_SILLON_P3 = ".";
string const MSSG_ERR_NOMBRE_SILLON = MSSG_ERR_NOMBRE_SILLON_P1 + 
                                      to_string( NOMBRE_SILLON_MINIMUM ) + 
                                      MSSG_ERR_NOMBRE_SILLON_P2 + 
                                      to_string( NOMBRE_SILLON_MAXIMUM ) + 
                                      MSSG_ERR_NOMBRE_SILLON_P3;
string const MSSG_ERR_SEULEMENT_DIRECT = "Seulement un lien direct peut apparaitre apres une vis.";
string const MSSG_ERR_SEULEMENT_ENGRENAGE_DIRECT = "Seulement un engrenage peut apparaitre apres un lien direct.";
string const MSSG_ERR_SEULEMENT_ENGRENAGE_CHAINE = "Seulement un engrenage peut apparaitre apres une chaine.";
string const MSSG_ERR_UNE_COMPOSANTE_MINIMUM = "Il doit y avoir au moins une composante.";
string const MSSG_ERR_VITESSE_INVALIDE = "Ce n'est pas une vitesse valide.";

//ajoutes en surplus
string const MSSG_ERR_NOMBRE_ARGUMENT = "Il devrait y avoir un et un seul argument.";
string const MSSG_ERR_COMPOSANTE_ESSIEU = "Il faut une composante apres un essieu.";
string const MSSG_ERR_DENT_ENTIER = "Il devrait y avoir une valeur entiere pour le nombre de dents.";
string const MSSG_ERR_SILLON_ENTIER = "Il devrait y avoir une valeur entiere pour le nombre de sillons.";


#endif
