#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <functional>
#include "Constantes.hpp"

using namespace std;

/**
 * Classe Lien contenant le nom du lien.
 */
class Lien
{
private:
	string nomLien;

public:
	Lien(string nomLien) : nomLien(nomLien) {}
	Lien() {}
	~Lien();
	string getLien();
};

/**
 * Classe Essieu qui hérite de la classe Lien.
 */
class Essieu : public Lien
{
public:
	string essieu = "essieu";
	Essieu();
	~Essieu();
};

/**
 * Classe Direct qui hérite de la classe Lien.
 */
class Direct : public Lien
{
public:
	string direct = "direct";
	Direct(string direct) : direct(direct) {}
	Direct();
	~Direct();
};

/**
 * Classe Chaine qui hérite de la classe Lien.
 */
class Chaine : public Lien
{
public:
	string chaine = "chaine";
	Chaine(string chaine) : chaine(chaine) {}
	Chaine() {}
	~Chaine();
};

/**
 * Classe composante contenant le nom et le nombre.
 */
class Composante
{
private:
	string nomComposante;
	int nombreComposante;

public:
	Composante(string nomComposante, int nombreComposante) : nomComposante(nomComposante), nombreComposante(nombreComposante) {}
	Composante() {}
	~Composante();
	string getTypeComposante();
	int getNbrComposante();
};

/**
 * Classe Engrenage qui hérite de la classe Composante.
 */
class Engrenage : public Composante
{
public:
	string engrenage = "engrenage";
	int nombreDent = 0;
	Engrenage(string engrenage, int nombreDent) : engrenage(engrenage), nombreDent(nombreDent) {}
	Engrenage() {}
	~Engrenage();
};

/**
 * Classe Vis qui hérite de la classe Composante.
 */
class Vis : public Composante
{
public:
	string vis = "vis";
	int nombreSillon;
	Vis(string vis, int nombreSillon) : vis(vis), nombreSillon(nombreSillon) {}
	Vis() {}
	~Vis();
};

/**
 * Lien::getLien Getter pour le type de lien.
 * 
 * @return nomLien Le lien.
 */
string Lien::getLien()
{
	return nomLien;
}

/**
 * Composante::getTypeComposante Getter pour le type de composante
 * 
 * @return nomComposante La composante.
 */
string Composante::getTypeComposante()
{
	return nomComposante;
}

/**
 * Composante::getNbrComposante Getter pour le nombre de sillon/dents.
 * 
 * @return nombreComposante Le nombre de sillon/dents.
 */
int Composante::getNbrComposante()
{
	return nombreComposante;
}

/**
 * Destructeur de la classe Composante.
 */
Composante::~Composante(void) {}

/**
 * Destructeur de la classe Lien.
 */
Lien::~Lien(void) {}

/*Déclaration de méthodes*/
void afficherResultat(const double vitesseCourante, const double coupleCourant, const double efficaciteTotale, const unsigned int i);
double trouverR(const unsigned int i, const vector<pair<Composante *, pair<Lien *, Composante *>>> vecteur);
double trouverEfficacite(const vector<pair<Composante *, pair<Lien *, Composante *>>> vecteur, double &efficacite, const unsigned int i);
void creerTableauEfficacite(const vector<pair<Composante *, pair<Lien *, Composante *>>> vecteur, double efficacite, vector<double> &tabEfficacite);
void executerPartieUn(vector<pair<Composante *, pair<Lien *, Composante *>>> &vecteur, istream &fichierEntre);

/**
 * fichierNonExistant Vérifie si le fichier en argument est trouvé. Sinon, un message d'erreur est lancé.
 * 
 * @param input Le fichier d'entrée.
 */
void fichierNonExistant(istream &input)
{
	if (!input)
	{
		cerr << MSSG_ERR_FICHIER_INEXISTANT << endl;
		exit(-1);
	}
}

/*Définition de méthodes*/

/**
 * lireComposante Vérifie la composante lue. Un message d'erreur est lancé s'il n'y a pas de composante ou que la composante est invalide.
 * 
 * @param input              Le fichier d'entrée.
 * @param compteurComposante Un compteur pour le nombre de composantes lu avec succès.
 * @param composante         La composante lu dans le fichier.
 */
void lireComposante(istream &input, int &compteurComposante, string &composante)
{
	if (input.eof() && (compteurComposante == 0))
	{
		cerr << MSSG_ERR_UNE_COMPOSANTE_MINIMUM << endl;
		exit(-1);
	}
	else if (composante == "engrenage" || composante == "vis")
	{
		++compteurComposante;
	}
	else
	{
		cerr << MSSG_ERR_COMPOSANTE_INVALIDE << endl;
		exit(-1);
	}
}

/**
 * verifierLienPrecedentEtComposante Vérifie la validité de la composante suivant le lien. Un message d'erreur est lancé si les conditions ne sont pas respectés.
 * 
 * @param composante La composante lu dans le fichier.
 * @param input      Le fichier d'entrée.
 * @param lien       Le lien lu dans le fichier.
 */
void verifierLienPrecedentEtComposante(string &composante, istream &input, string &lien)
{
	if (composante == "vis" && lien == "direct")
	{
		cerr << MSSG_ERR_SEULEMENT_ENGRENAGE_DIRECT << endl;
		exit(-1);
	}
	else if (composante == "vis" && lien == "chaine")
	{
		cerr << MSSG_ERR_SEULEMENT_ENGRENAGE_CHAINE << endl;
		exit(-1);
	}
	else if (lien == "essieu" && input.fail())
	{
		cerr << MSSG_ERR_COMPOSANTE_ESSIEU << endl;
		exit(-1);
	}
}

/**
 * verifierEssieuEstFin Vérifie la présence d'une composante suivant un lien de type essieu.
 * 
 * @param input Le fichier d'entrée.
 * @param lien  Le lien lu dans le fichier.
 */
void verifierEssieuEstFin(istream &input, string &lien)
{
	if (lien == "essieu" && input.fail())
	{
		cerr << MSSG_ERR_COMPOSANTE_ESSIEU << endl;
		exit(-1);
	}
}

/**
 * verifierAucuneComposante Lance un message d'erreur s'il n'y a pas de composante dans le fichier.
 * 
 * @param compteurComposante Le nombre de composante valide.
 */
void verifierAucuneComposante(int &compteurComposante)
{
	if (compteurComposante == 0)
	{
		cerr << MSSG_ERR_UNE_COMPOSANTE_MINIMUM << endl;
		exit(-1);
	}
}

/**
 * verificationNombreComposante Vérifie la validité du nombre de sillon ou de dents. Une message d'erreur est lancé si ce nombre est absent ou n'est pas entière.
 * 
 * @param input      Le fichier d'entrée.
 * @param composante La composante lu dans le fichier.
 * @param nombre     Le nombre de sillon ou de dents lu dans le fichier.
 */
void verificationNombreComposante(istream &input, string &composante, int &nombre)
{
	if ((composante == "engrenage") && input.fail())
	{
		cerr << MSSG_ERR_DENT_ENTIER << endl;
		exit(-1);
	}
	else if ((composante == "vis") && input.fail())
	{
		cerr << MSSG_ERR_SILLON_ENTIER << endl;
		exit(-1);
	}
	else if ((composante == "engrenage") && (nombre < NOMBRE_DENT_MINIMUM))
	{
		cerr << MSSG_ERR_NOMBRE_DENT_MINIMUM << endl;
		exit(-1);
	}
	else if ((composante == "vis") && ((nombre < NOMBRE_SILLON_MINIMUM) || (nombre > NOMBRE_SILLON_MAXIMUM)))
	{
		cerr << MSSG_ERR_NOMBRE_SILLON << endl;
		exit(-1);
	}
}

/**
 * validationLien Valide le lien qui suit une composante. Un message d'erreur est lancé si un cas particulier n'est pas respecté.
 * 
 * @param lien               Le lien lu dans le fichier.
 * @param compteurComposante Le nombre de composante valide.
 * @param composante         La composante lu dans le fichier.
 */
void validationLien(string &lien, int &compteurComposante, string &composante)
{
	if (lien != "direct" && composante == "vis")
	{
		cerr << MSSG_ERR_SEULEMENT_DIRECT << endl;
		exit(-1);
	}
	else if (lien == "direct" && composante == "vis" && compteurComposante > 1)
	{
		cerr << MSSG_ERR_SEULEMENT_ENGRENAGE_DIRECT << endl;
		exit(-1);
	}
	else if (lien == "chaine" && composante == "vis")
	{
		cerr << MSSG_ERR_SEULEMENT_ENGRENAGE_CHAINE << endl;
		exit(-1);
	}
	else if (lien != "direct" && lien != "essieu" && lien != "chaine")
	{
		cerr << MSSG_ERR_LIEN_INVALIDE << endl;
		exit(-1);
	}
}

/**
 * demanderQuestions Demande l'entrée d'une vitesse et d'un couple. La question est redemandé si l'entrée est invalide ou que le la valeur et la vitesse ne sont pas du même signe.
 * 
 * @param bonVitesseCouple Indique le statut de validité de la vitesse et le couple.
 * @param vitesse          La vitesse de rotation saisie par l'utilisateur.
 * @param couple           Le couple saisi par l'utilisateur.
 */
void demanderQuestions(bool &bonVitesseCouple, double &vitesse, double &couple)
{
	while (!bonVitesseCouple)
	{
		cout << MSSG_REQUETE_VITESSE;

		while (!(cin >> vitesse))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << MSSG_ERR_VITESSE_INVALIDE << endl;
			cout << MSSG_REQUETE_VITESSE;
		}

		cout << MSSG_REQUETE_COUPLE;
		while (!(cin >> couple))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << MSSG_ERR_COUPLE_INVALIDE << endl;
			cout << MSSG_REQUETE_COUPLE;
		}

		if ((vitesse >= 0 && couple >= 0) || (vitesse < 0 && couple < 0))
		{
			bonVitesseCouple = true;
		}
		else
		{
			cerr << MSSG_ERR_MEME_SIGNE << endl;
		}
	}
}

/**
 * calculerefficaciteTotale Calcule l'efficacité totale en multiplicant ensemble chaque valeur d'un case.
 * 
 * @param  efficaciteTotale L'efficacité initialisé à 1.
 * @param  tabEfficacite    Un tableau contenant l'efficacité de chaque composante avec un lien.
 */
void calculerefficaciteTotale(double &efficaciteTotale, const vector<double> tabEfficacite)
{
	for (const auto &e : tabEfficacite)
	{
		efficaciteTotale *= e;
	}
}

/**
 * declencherProcessus Effectue le calcul et l'affichage de la vitesse et le couple pour chaque composante.
 * 
 * @param vecteur          Un vecteur qui contient l'information d'un composante lié à un autre composante.
 * @param efficaciteTotale L'éfficacité du mécanisme.
 * @param vitesse          La vitesse de rotation saisie par l'utilisateur.
 * @param couple           Le couple saisi par l'utilisateur.
 */
void declencherProcessus(const vector<pair<Composante *, pair<Lien *, Composante *>>> vecteur, double &efficaciteTotale, const double vitesse, const double couple)
{
	double r;
	double vitesseCourante = vitesse;
	double coupleCourant = couple;
	double vitesseProchaine;
	double coupleProchain;

	for (unsigned int i = 0; i < vecteur.size(); ++i)
	{

		if (vecteur[i].second.first->getLien() == "aucunLien")
		{
			efficaciteTotale = 1.0;
		}
		else
		{
			r = trouverR(i, vecteur);
		}

		afficherResultat(vitesseCourante, coupleCourant, efficaciteTotale, i);

		vitesseProchaine = vitesseCourante / r;
		coupleProchain = coupleCourant * r;

		vitesseCourante = vitesseProchaine;
		coupleCourant = coupleProchain;
		if (i + 1 == vecteur.size() && vecteur[i].second.first->getLien() != "aucunLien")
		{
			afficherResultat(vitesseCourante, coupleCourant, efficaciteTotale, i + 1);
		}
	}
}

/**
 * sortirOuNon Détermine s'il faut arrêter le programme ou non selon l'entrée de l'utilisateur.
 * 
 * @param continuer La réponse entrée pour lancer une autre analyse ou non.
 * @param sortir    Indique la décision de l'arrêt du programme.
 */
void sortirOuNon(const char continuer, bool &sortir)
{
	if (continuer == 'n')
	{
		sortir = true;
	}
}

/**
 * continuerOuNon Détermine s'il faut entrer une nouvelle analyse ou non selon l'entrée de d'utilisateur.
 * 
 * @param  continuer        La réponse entrée pour lancer une autre analyse ou non.
 * @param  bonVitesseCouple Indique que la vitesse et le couple ont été saisies et validés.
 */
void continuerOuNon(const char continuer, bool &bonVitesseCouple)
{
	if (continuer != 'n')
	{
		bonVitesseCouple = false;
	}
}

/**
 * detruireVecteur Efface chaque valeur présent dans le vecteur et enlève le vecteur de la mémoire.
 * 
 * @param vecteur Un vecteur qui contient l'information d'un composante lié à un autre composante.
 */
void detruireVecteur(vector<pair<Composante *, pair<Lien *, Composante *>>> &vecteur)
{
	for (auto &i : vecteur)
	{
		i.first->~Composante();
		i.second.first->~Lien();
		i.second.second->~Composante();
	}
	vecteur.clear();
}

/**
 * creerTableauEfficacite Trouve l'efficacité du mécanisme et le sauvegarde dans un tableau. Ceci est répété pour chaque composante et lien.
 * 
 * @param vecteur       Un vecteur qui contient l'information d'un composante lié à un autre composante.
 * @param efficacite    L'éfficacité du mécanisme dont nous voulons trouver sa valeur.
 * @param tabEfficacite Un tableau contenant l'ensenble des valeurs d'efficacité.
 */
void creerTableauEfficacite(const vector<pair<Composante *, pair<Lien *, Composante *>>> vecteur, double efficacite, vector<double> &tabEfficacite)
{
	for (unsigned int i = 0; i < vecteur.size(); ++i)
	{
		tabEfficacite.push_back(trouverEfficacite(vecteur, efficacite, i));
	}
}

/**
 * trouverEfficacite Trouve l'efficacité du mécanisme selon le type du composante, le nombre de dents s'il y a lieu et le type du lien.
 * 
 * @param  vecteur    Un vecteur qui contient l'information d'un composante lié à un autre composante.
 * @param  efficacite L'éfficacité du mécanisme dont nous voulons trouver sa valeur.
 * @param  i          L'index pour accedér au vecteur.
 * @return            efficacité L'éfficacité du mécanisme.
 */
double trouverEfficacite(const vector<pair<Composante *, pair<Lien *, Composante *>>> vecteur, double &efficacite, const unsigned int i)
{
	if (vecteur[i].second.first->getLien() == "essieu")
	{
		efficacite = 1.0;
	}
	else if (vecteur[i].first->getTypeComposante() == "vis" && vecteur[i].first->getNbrComposante() == 1 && vecteur[i].second.first->getLien() == "direct")
	{
		efficacite = 0.8;
	}
	else if (vecteur[i].first->getTypeComposante() == "vis" && vecteur[i].first->getNbrComposante() == 2 && vecteur[i].second.first->getLien() == "direct")
	{
		efficacite = 0.7;
	}
	else if (vecteur[i].first->getTypeComposante() == "vis" && vecteur[i].first->getNbrComposante() == 3 && vecteur[i].second.first->getLien() == "direct")
	{
		efficacite = 0.6;
	}
	else if (vecteur[i].first->getTypeComposante() == "vis" && vecteur[i].first->getNbrComposante() == 4 && vecteur[i].second.first->getLien() == "direct")
	{
		efficacite = 0.5;
	}
	else if (vecteur[i].first->getTypeComposante() != "vis" && vecteur[i].second.first->getLien() == "direct")
	{
		efficacite = 0.9;
	}
	else if (vecteur[i].second.first->getLien() == "chaine")
	{
		efficacite = 0.8;
	}
	return efficacite;
}

/**
 * afficherResultat Affiche sur la sortie standard la vitesse et le couple pour une composante.
 * 
 * @param vitesseCourante  La vitesse de rotation.
 * @param coupleCourant    Le couple appliqué au mécanisme.
 * @param efficaciteTotale L'éfficacité du mécanisme.
 * @param i                Le numéro pour la vitesse et le couple.
 */
void afficherResultat(const double vitesseCourante, const double coupleCourant, const double efficaciteTotale, const unsigned int i)
{
	cout << "V" << i << " = " << efficaciteTotale * vitesseCourante << ","
		 << "C" << i << " = " << efficaciteTotale * coupleCourant << endl;
}

/**
 * trouverR Trouve la valeur de r selon le lien, le type du premier et deuxième composante, dépendament du cas.
 * 
 * @param  i       L'index pour accedér au vecteur.
 * @param  vecteur Un vecteur qui contient l'information d'un composante lié à un autre composante.
 * @return         r 
 */
double trouverR(const unsigned int i, const vector<pair<Composante *, pair<Lien *, Composante *>>> vecteur)
{

	double valeurR;
	if (vecteur[i].second.first->getLien() == "essieu")
	{
		valeurR = 1.0;
	}
	else if (vecteur[i].second.first->getLien() == "direct" && vecteur[i].first->getTypeComposante() == "engrenage" && vecteur[i].second.second->getTypeComposante() == "engrenage")
	{
		valeurR = -1.0 * vecteur[i].second.second->getNbrComposante() / vecteur[i].first->getNbrComposante();
	}
	else if (vecteur[i].second.first->getLien() == "direct" && vecteur[i].first->getTypeComposante() == "vis" && vecteur[i].second.second->getTypeComposante() == "engrenage")
	{
		valeurR = static_cast<double>(vecteur[i].second.second->getNbrComposante()) / vecteur[i].first->getNbrComposante();
	}
	else if (vecteur[i].second.first->getLien() == "chaine" && vecteur[i].first->getTypeComposante() == "engrenage" && vecteur[i].second.second->getTypeComposante() == "engrenage")
	{
		valeurR = static_cast<double>(vecteur[i].second.second->getNbrComposante()) / vecteur[i].first->getNbrComposante();
	}
	return valeurR;
}

/**
 * executerPartieUn Exécute la partie concernant la lecture du composante, nombre du sillion/dent et du lien.
 * 
 * @param vecteur      Un vecteur qui contient l'information d'un composante lié à un autre composante.
 * @param fichierEntre Le fichier d'entrée.
 */
void executerPartieUn(vector<pair<Composante *, pair<Lien *, Composante *>>> &vecteur, istream &fichierEntre)
{
	string composante;
	string composanteDeux;
	int nombre;
	int nombreDeux;
	string lien;
	string lienDeux;
	int compteurComposante = 0;

	fichierNonExistant(fichierEntre);
	fichierEntre >> composante;
	lireComposante(fichierEntre, compteurComposante, composante);

	while (!fichierEntre.eof())
	{
		nombreDeux = nombre;
		fichierEntre >> nombre;

		verificationNombreComposante(fichierEntre, composante, nombre);

		lienDeux = lien;
		fichierEntre >> lien;

		if (fichierEntre.eof())
		{
			if (compteurComposante == 1)
			{
				vecteur.emplace_back(make_pair(new Composante(composante, nombre), make_pair(new Lien("aucunLien"), new Composante("aucunComposante", -1))));
			}
			else
			{
				vecteur.emplace_back(make_pair(new Composante(composanteDeux, nombreDeux), make_pair(new Lien(lienDeux), new Composante(composante, nombre))));
			}

			break;
		}
		else if (compteurComposante > 1)
		{
			vecteur.emplace_back(make_pair(new Composante(composanteDeux, nombreDeux), make_pair(new Lien(lienDeux), new Composante(composante, nombre))));
		}

		validationLien(lien, compteurComposante, composante);
		verifierEssieuEstFin(fichierEntre, lien);

		composanteDeux = composante;

		fichierEntre >> composante;
		lireComposante(fichierEntre, compteurComposante, composante);

		verifierLienPrecedentEtComposante(composante, fichierEntre, lien);
	}
}

/**
 * executerPartieDeux Exécute la partie concernant l'entrée d'une vitesse et d'un couple et l'affichage des résultats pour chaque composante.
 * 
 * @param vecteur Un vecteur qui contient l'information d'un composante lié à un autre composante.
 */
void executerPartieDeux(vector<pair<Composante *, pair<Lien *, Composante *>>> vecteur)
{

	double vitesse;
	double couple;
	char continuer;
	bool sortir = false;
	bool bonVitesseCouple = false;

	while (!sortir)
	{
		double efficacite;
		demanderQuestions(bonVitesseCouple, vitesse, couple);

		vector<double> tabEfficacite;
		creerTableauEfficacite(vecteur, efficacite, tabEfficacite);

		double efficaciteTotale = 1.0;
		calculerefficaciteTotale(efficaciteTotale, tabEfficacite);
		declencherProcessus(vecteur, efficaciteTotale, vitesse, couple);

		tabEfficacite.clear();

		cout << MSSG_QUESTION_CONTINUER;
		cin >> continuer;
		sortirOuNon(continuer, sortir);
		continuerOuNon(continuer, bonVitesseCouple);
	}
}

/**
 * main Le programme principal sert à lire un fichier, traiter l'information et afficher les résultats.
 * 
 * @param  argc L'exécutable tp1.
 * @param  argv Le nom du fichier à lire, en argument.
 * @return      0 Signifie la fin du programme.
 */
int main(int argc, char const *argv[])
{

	ifstream fichierEntre(argv[1]);
	vector<pair<Composante *, pair<Lien *, Composante *>>> vecteur;

	if (argc == 2)
	{
		executerPartieUn(vecteur, fichierEntre);
	}
	else
	{
		cerr << MSSG_ERR_NOMBRE_ARGUMENT << endl;
		exit(-1);
	}

	executerPartieDeux(vecteur);
	detruireVecteur(vecteur);

	return 0;
}