/*

*/


#include <iostream>
#include "Table.h"

using namespace std;

//Constructeurs
Table::Table() // constructeur par defaut
{
	capacite_ = MAXCAP;
	id_ = -1;
	nbPlaces_ = 1;
	nbPlats_ = 0;
	occupee_ = false;
	commande_ = new Plat*[MAXCAP];
}
Table::Table(int id, int nbPlaces) : capacite_(MAXCAP), occupee_(false) // constructeur par parametres
{
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbPlats_ = 0;
	capacite_ = MAXCAP;
	occupee_ = false;
	commande_ = new Plat*[MAXCAP];

}

//Destructeur
Table::~Table()
{}

//Getters
int Table::getId() const // retourne le id de la table
{
	return id_;
}
int Table::getNbPlaces() const // retourne le nb de places de la table
{
	return nbPlaces_;
}
bool Table::estOccupee() const // retourne si la table est occupee ou non
{
	return occupee_;
}

//Setters
void Table::libererTable() // libere la table et enleve les commandes
{

	delete[] commande_; // aggregation, on ne detruit pas les plats apres avoir libere la table
	occupee_ = false;
	nbPlats_ = 0;
}
void Table::placerClient() // les clients sont places sur la table, celle-ci devient donc occupee
{
	occupee_ = true;
}
void Table::setId(int id) // change le id de la table
{
	id_ = id;
}

//Autre methodes
void Table::commander(Plat * plat) // ajoute un pointeur vers un plat quelconque dans la liste de pointeur commande_
{
	if (plat != nullptr)
	{
		if (nbPlats_ >= capacite_)
		{
			int newCapacity = (capacite_ > 0) ? capacite_ * 2 : 10; // verifier s'il reste de la place dans le tableau
			capacite_ = newCapacity;
			Plat** nouvelleCommande = new Plat*[capacite_];


			for (unsigned int i = 0; i < nbPlats_; i++)
			{
				nouvelleCommande[i] = commande_[i]; // copie des donnees
			}

			delete[] commande_;
			commande_ = nouvelleCommande;
		}
		commande_[nbPlats_] = plat;
		nbPlats_++;
	}
	

}
double Table::getChiffreAffaire() const
{
	double chiffreAffaire = 0.0;
	for (unsigned int i = 0; i < nbPlats_; i++)
	{
		chiffreAffaire += commande_[i]->getPrix() - commande_[i]->getCout();

	}
	return chiffreAffaire;
	
}

//Affichage
void Table::afficher() const
{

	/*cout << "Table " << id_ << " de " << nbPlaces_ << " personne(s)" << endl;
	cout << "Plat(s) commande(s)" << endl;*/
	string estOccupe = "est occupe. ", libre = "libre. ";

	cout << "	La table numero " << id_ << " ";
	if (estOccupee() == true)
		cout << estOccupe;
	else
		cout << libre;
	if (nbPlats_ > 0)
	{
		cout << "Voici les commandes passees par les clients: " << endl;


		for (unsigned int i = 0; i < nbPlats_; i++)
		{
			commande_[i]->afficher();
		}

	}
	else
		cout << "Pas de commande" << endl;
	
}