/*

*/


#include <iostream>
#include <fstream>
#include <string>
#include "Restaurant.h"

//Constructeur
Restaurant::Restaurant() //constructeur par defaut
{
	nom_ = new string;
	*nom_ = "inconnu";
	momentJournee_ = Matin;
	chiffreAffaire_ = 0.0;
	//capaciteTables_ = INTTABLES;
	//tables_ = new Table*[capaciteTables_];
	//nbTables_ = 0;
	menuMatin_ = new Menu;
	menuMidi_ = new Menu;
	menuSoir_ = new Menu;
}
Restaurant::Restaurant(string & fichier, string & nom, TypeMenu moment) // constructeur par parametres
{
	nom_ = new string;
	*nom_ = nom;
	momentJournee_ = moment;
	chiffreAffaire_ = 0.0;
	lireTable(fichier);
	menuMatin_ = new Menu(fichier, Matin);
	menuMidi_ = new Menu(fichier, Midi);
	menuSoir_ = new Menu(fichier, Soir);
	//capaciteTables_ = INTTABLES;
	//nbTables_ = 0;
	//tables_ = new Table*[INTTABLES];
}

//Destructor
Restaurant::~Restaurant()
{
	delete nom_;
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;
	for (unsigned int i = 0; i < nbTables_; i++)
	{
		delete tables_[i]; // le restaurant et ses tables sont en composition, si on delete le restaurant, il faut delete les tables aussi
	}
	delete[] tables_;
}

//Setter
void Restaurant::setMoment(TypeMenu moment) // modifie le moment de la journee
{
	momentJournee_ = moment;
}

//Getter
string Restaurant::getNom() const // retourne le nom du restaurant (dereference)
{
	return *nom_;
}
TypeMenu Restaurant::getMoment() const // retourne le moment de la journee
{
	return momentJournee_;
}


void Restaurant::lireTable(string & fichier)
{
	ifstream lireFichier;
	string tempStr;
	lireFichier.open(fichier);
	if (lireFichier.fail())
	{
		cout << "ERREUR d'ouverture de fichier (restaurant.cpp)";
	}
	else
	{
		while (!ws(lireFichier).eof())
		{
			getline(lireFichier, tempStr);
			if (tempStr == "-TABLES")
			{
				while (!ws(lireFichier).eof())
				{
					int id, NbPlaces;
					lireFichier >> id >> NbPlaces;
					ajouterTable(id, NbPlaces);
				}

			}
		}
		lireFichier.close();
	}
}
void Restaurant::ajouterTable(int id, int nbPlaces)
{

	if (nbTables_ >= capaciteTables_) 
	{
		int newCapacity = (capaciteTables_ > 0) ? capaciteTables_ * 2 : 10; // si capacite nulle, on la met a 10, sinon elle est doublee
		Table** tempTable = new Table*[newCapacity];
		capaciteTables_ = newCapacity;
		for (unsigned int i = 0; i < nbTables_; i++)
		{
			tempTable[i] = tables_[i];
		}
		delete[] tables_;
		tables_ = tempTable;
	}
	tables_[nbTables_] = new Table(id, nbPlaces);
	nbTables_++;
}
void Restaurant::libererTable(int id) // libere la table et update le chiffre d'affaire
{
	for (unsigned int i = 0; i < nbTables_; i++)
	{
		if (tables_[i]->getId() == id)
		{
			chiffreAffaire_ += tables_[i]->getChiffreAffaire(); // on additionne le chiffre d'affaire de la table au restaurant
			tables_[i]->libererTable(); // efface les commandes et met la table a non occupe
		}
	}
}
void Restaurant::commanderPlat(string& nom, int idTable) // commander un plat et l'assigner a une table
{
	for (unsigned int i = 0; i < nbTables_; i++)
	{
		if (tables_[i]->getId() == idTable)
		{
			switch (momentJournee_)
			{
			case Matin:
				tables_[i]->commander(menuMatin_->trouverPlat(nom));
				break;
			case Midi:
				tables_[i]->commander(menuMidi_->trouverPlat(nom));
				break;
			case Soir:
				tables_[i]->commander(menuSoir_->trouverPlat(nom));
				break;
			}
		}
	}
}
void Restaurant::placerClients(int nbClients) // place les clients de facon "intelligente", soit avec le moins de place vide possible
{
	//Table* tempTable;
	int moindrePlace = 0;
	int index = -1;
	for (unsigned int i = 0; i < nbTables_; i++) // classer les tables en ordre croissant de nombre de places
	{
		if (tables_[i]->estOccupee() == false && tables_[i]->getNbPlaces() >= nbClients)
		{
			if (tables_[i]->getNbPlaces() < moindrePlace || moindrePlace == 0)
			{
				moindrePlace = tables_[i]->getNbPlaces();
				index = i;
			}
			if (index == -1)
				cout << " ERREUR pas de table convenable pour le client." << endl;
			else
				tables_[index]->placerClient();
		}
		/*
		for (unsigned int j = i+1; j < nbTables_ - (i+1); j++)
		{
			if (tables_[j] < tables_[i])
			{
				tempTable = tables_[i];
				tables_[i] = tables_[j];
				tables_[j] = tempTable;
			}
		}
	}

	for (unsigned int i = 0; i < nbTables_; i++) // parcourir les tables et placer de sorte que le nombre de client est le plus pres du nombre de place
	{
		if (nbClients <= (tables_[i]->getNbPlaces()) && tables_[i]->estOccupee() == false)
		{
			tables_[i]->placerClient();
		}
		else if (i == nbTables_ - 1 && nbClients > tables_[i]->getNbPlaces()) // si on est rendu a la derniere table et que qu'il y a plus de clients que de places
			cout << "ERREUR: il n'y a pas de tables assez grande pour accommoder ce groupe" << endl;
		else if (i == nbTables_ - 1 && nbClients <= tables_[i]->getNbPlaces()) // si on est rendu a la derniere table, mais qu'il y a une table occupee, mais assez grande
			cout << "ERREUR: toutes les tables semblent etre occupees, veuiller attendre ou revenir plus tard" << endl;
	}*/
	}
}

//affichage
void Restaurant::afficher() const
{
	cout << "Le restaurant " << *nom_;
	if (chiffreAffaire_ > 0)
	{
		cout << " a fait " << chiffreAffaire_ << " $ en profit" << endl;
	}
	else
		cout << " n'a pas fait de profits ou le chiffre d'affaire n'est pas encore calcule." << endl;
	
	cout << "Voici les Tables: " << endl;
	for (unsigned int i = 0; i < nbTables_; i++)
	{
		tables_[i]->afficher();
	}

	cout << "Voici son menu: " << endl;
	//string nomFichier = "polyFood.txt";
	cout << "Matin: ";
	//menuMatin_ = new Menu (nomFichier, Matin);
	menuMatin_->afficher();
	cout << endl << "Midi: ";
	//menuMidi_ = new Menu(nomFichier, Midi);
	menuMidi_->afficher();
	cout << endl << "Soir: ";
	//menuSoir_ = new Menu(nomFichier, Soir);
	menuSoir_->afficher();
	cout << endl;


}


