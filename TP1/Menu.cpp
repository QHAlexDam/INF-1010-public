/*

*/

#include <iostream>
#include <fstream>
#include <string>
#include "Menu.h"

using namespace std;

//Constructeurs
Menu::Menu() // constructeur par defaut
{
	capacite_ = MAXPLAT;
	listePlats_ = new Plat*[MAXPLAT];
	nbPlats_ = 0;
	type_ = Matin;

}
Menu::Menu(string fichier, TypeMenu type) // constructeur par parametre
{
	type_ = type;
	capacite_ = MAXPLAT;
	nbPlats_ = 0;
	listePlats_ = new Plat*[MAXPLAT];
	Menu::lireMenu(fichier);
	

}

//Destructeur
Menu:: ~Menu()
{
	for (unsigned int i = 0; i < nbPlats_; i++)
	{
		delete listePlats_[i]; // les plats sont en relation de composition avec le menu, donc il faut detruire tous les plats du menu lorsqu'on detruit celui-ci

	}
	delete[] listePlats_;

}

//Getter
int Menu::getNbPlats() const // retourne le nombre de plat dans le menu
{
	return nbPlats_;
}
int Menu::getCapcite() const // retourne la capacite du menu
{
	return capacite_;
}
TypeMenu Menu::getTypeMenu() const // retourne le type de menu
{
	return type_;
}

Plat ** Menu::getListePlat() const // retourne tous les plats du menu 
{
	return listePlats_;
}

//Autre methodes
Plat* Menu::trouverPlat(string& nom) // trouve un plat dans la liste de plats par son nom
{ 
	Plat* plat = nullptr;

	for (unsigned int i = 0; i <nbPlats_ ; i++) { //on veut la liste de plats
		if (listePlats_[i]->getNom() == nom)
		{
			plat = listePlats_[i];
		}
	}
	return plat;
}

void Menu::ajouterPlat(Plat & plat) // ajoute un plat a la liste de plat, prenant en paramettre un Plat par reference
{
	if (nbPlats_ >= capacite_) 
	{
		int newCapacity = (capacite_ > 0) ? capacite_ * 2 : 10; // si la capacite est nulle, on la met a 10, sinon, on la double

		Plat** nouveauPlat = new Plat*[newCapacity]; // creation d'une liste temporaire de grandeur newCapacity
		capacite_ = newCapacity;

		for (int i = 0; i < nbPlats_; i++) // copie des plats de l'ancienne liste vers la nouvelle
		{
			nouveauPlat[i] = listePlats_[i];
		}

		delete[] listePlats_; // efface l'ancienne liste de pointeur
		listePlats_ = nouveauPlat; // on reassigne la liste
	}
	listePlats_[nbPlats_] = new Plat(plat); // assigner le nouveau plat a ajouter
}

void Menu::ajouterPlat(string & nom, double montant, double cout) // ajoute un plat en creant un nouvel objet Plat avec un constructeur
{
	Plat nouveauPlat = Plat(nom, montant,cout ); // appel du constructeur par parametre
	ajouterPlat(nouveauPlat); // appel de la fonction ajouterPlat precedent
	nbPlats_++;
}

bool Menu::lireMenu(string & fichier) // lit un fichier texte et receuille les donnees pertinent au menu
{
	ifstream lireFichier(fichier);
	string typeFichier;
	string typeMenu;

	if (lireFichier.fail())
	{
		cout << "ERREUR d'ouverture de fichier (Menu.cpp)";
		return  false;
	}
	else
	{
		while (!ws(lireFichier).eof()) 
		{
			switch (type_)
			{
			case Matin:
				typeMenu = "-MATIN";
				break;
			case Midi:
				typeMenu = "-MIDI";
				break;
			case Soir:
				typeMenu = "-SOIR";
				break;
			default:
				break;
			}

			getline(lireFichier, typeFichier);
			
			if (typeFichier == typeMenu)
			{
				for (unsigned int i = 0; i < MAXPLAT; i++) 
				{
					double coutt, prix;
					string nomPlat;
					lireFichier >> nomPlat;
					if (nomPlat[0] != '-')
					{
						lireFichier >> prix >> coutt;
						ajouterPlat(nomPlat, prix, coutt);
					}
						
				}
			}
		}
		lireFichier.close();
		return true;
	}
}

	void Menu::afficher() const // cette fonction affiche les plats du menu, en utilisant la methode afficher de la classe Plat
{
	for (unsigned int i = 0; i < nbPlats_; i++)
	{
		listePlats_[i]->afficher();
	}
}


