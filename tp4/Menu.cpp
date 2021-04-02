
#include "Menu.h"
#include "LectureFichierEnSections.h"
#include "debogageMemoire.hpp"
#include <cassert>  //? Contient "assert" qui permet de s'assurer qu'une expression est vraie, et terminer le programme avec un message d'erreur en cas contraire.
using namespace std;

// Constructeurs.

Menu::Menu() : type_{TypeMenu::Matin}
{}

Menu::Menu(string fichier, TypeMenu type) :type_{type}
{
	lireMenu(fichier); 
}

/////////////////////////////////////////////////
///NOM: Menu
///PARAMETRES: const Menu & menu
///RETOUR :aucun
///DESCRIPTION :Constructeur par copie qui cree un nouvel menu ayant les meme caracteristiques qu'un menu passe en parametre
/////////////////////////////////////////////////
Menu::Menu(const Menu & menu) : type_(menu.type_)
{	
	if (this != &menu) {

		for (int i = 0; i < menu.listePlats_.size(); i++) {
			if (dynamic_cast<PlatBioVege*>(menu.listePlats_[i])) {
				listePlats_.push_back(dynamic_cast<PlatBioVege*>(allouerPlat(menu.listePlats_[i])));
			}
			else if (dynamic_cast<PlatBio*>(menu.listePlats_[i]))
				listePlats_.push_back(dynamic_cast<PlatBio*>(allouerPlat(menu.listePlats_[i])));
			else if (dynamic_cast<PlatVege*>(menu.listePlats_[i])) {
				listePlats_.push_back(dynamic_cast<PlatVege*>(allouerPlat(menu.listePlats_[i])));
			}
			else
				listePlats_.push_back(allouerPlat(menu.listePlats_[i]));
		}
		for (int i = 0; i < listePlats_.size(); i++) {
			if (dynamic_cast<PlatBioVege*>(listePlats_[i]))
				listePlatsVege_.push_back(dynamic_cast<PlatBioVege*>(listePlats_[i]));
			else if (dynamic_cast<PlatVege*>(listePlats_[i]))
				listePlatsVege_.push_back(dynamic_cast<PlatVege*>(listePlats_[i]));
		}
	}


}

//Destructeur

/////////////////////////////////////////////////
///NOM: Menu
///PARAMETRES: aucun
///RETOUR :aucun
///DESCRIPTION :Destructeur de menu qui doit liberer la memoire des plats, car c'est en composition
/////////////////////////////////////////////////
Menu::~Menu()
{
	for (int i = 0; i < listePlats_.size(); i++) {
		delete listePlats_[i];
	}

	listePlats_.clear();
	listePlatsVege_.clear();
}

// Getters.

vector<Plat*> Menu::getListePlats() const
{
	return listePlats_;
}


// Autres methodes.

Plat* Menu::allouerPlat(Plat* plat) {
    return plat->clone();
}

/////////////////////////////////////////////////
///NOM: operator=
///PARAMETRES: const Menu & menu
///RETOUR :l'objet courant (*this)
///DESCRIPTION :surcharge de l'operateur = qui ecrase un menu existant avec les parametres d'un autre menu
/////////////////////////////////////////////////
Menu & Menu::operator=(const Menu & menu)  {
	if (this != &menu) {

		for (unsigned int i = 0; i < listePlats_.size(); i++) {
			delete listePlats_[i];
		}
		listePlats_.clear();
		listePlatsVege_.clear();
		for (int i = 0; i < menu.listePlats_.size(); i++) {
			if (dynamic_cast<PlatBioVege*>(menu.listePlats_[i])) {
				listePlats_.push_back(dynamic_cast<PlatBioVege*>(allouerPlat(menu.listePlats_[i])));
			}
			else if (dynamic_cast<PlatBio*>(menu.listePlats_[i]))
				listePlats_.push_back(dynamic_cast<PlatBio*>(allouerPlat(menu.listePlats_[i])));
			else if (dynamic_cast<PlatVege*>(menu.listePlats_[i])) {
				listePlats_.push_back(dynamic_cast<PlatVege*>(allouerPlat(menu.listePlats_[i])));
			}
			else
				listePlats_.push_back(allouerPlat(menu.listePlats_[i]));
		}
		for (int i = 0; i < listePlats_.size(); i++) {
			if (dynamic_cast<PlatBioVege*>(listePlats_[i]))
				listePlatsVege_.push_back(dynamic_cast<PlatBioVege*>(listePlats_[i]));
			else if (dynamic_cast<PlatVege*>(listePlats_[i]))
				listePlatsVege_.push_back(dynamic_cast<PlatVege*>(listePlats_[i]));
		}
		type_ = menu.type_;
	}

	return *this;
}

/////////////////////////////////////////////////
///NOM: operator+=
///PARAMETRES: owner<Plat*> plat
///RETOUR :l'objet courant (*this)
///DESCRIPTION :surcharge de l'operateur += ajoute un plat dans la liste de plat et, si il est vege, le rajoute aussi a la liste vegetarienne
/////////////////////////////////////////////////
Menu& Menu::operator+=(owner<Plat*> plat) {

	if (dynamic_cast<PlatBioVege*>(plat)) {
		listePlats_.push_back(dynamic_cast<PlatBioVege*>(plat));
		listePlatsVege_.push_back(dynamic_cast<PlatBioVege*>(plat));
	}
	else if (dynamic_cast<PlatBio*>(plat))
		listePlats_.push_back(dynamic_cast<PlatBio*>(plat));
	else if (dynamic_cast<PlatVege*>(plat)) {
		listePlats_.push_back(dynamic_cast<PlatVege*>(plat));
		listePlatsVege_.push_back(dynamic_cast<PlatVege*>(plat));
	}
	else
		listePlats_.push_back(plat);

	return *this;
}

void Menu::lireMenu(const string& nomFichier) {
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection(entetesDesTypesDeMenu[static_cast<int>(type_)]);
	while (!fichier.estFinSection())
		*this += lirePlatDe(fichier);
}

Plat* Menu::trouverPlatMoinsCher() const
{
	assert(!listePlats_.empty() && "La liste de plats de doit pas etre vide pour trouver le plat le moins cher.");
	Plat* minimum = listePlats_[0];
	for (Plat* plat : listePlats_)
		if (*plat < *minimum)
			minimum = plat;

	return minimum;
}

Plat* Menu::trouverPlat(string_view nom) const
{
	for (Plat* plat : listePlats_)
		if (plat->getNom() == nom)
			return plat;

	return nullptr;
}
Plat* Menu::lirePlatDe(LectureFichierEnSections& fichier)
{
	auto lectureLigne = fichier.lecteurDeLigne();

	string nom, typeStr;
	TypePlat type;
	double prix, coutDeRevient;
	lectureLigne >> nom >> typeStr >> prix >> coutDeRevient;
	type = TypePlat(stoi(typeStr));
	double ecotaxe, vitamines, proteines, mineraux;
	switch (type) {
	case TypePlat::Bio:
		lectureLigne >> ecotaxe;
		return new PlatBio{ nom, prix, coutDeRevient, ecotaxe };
	case TypePlat::BioVege:
		lectureLigne >> ecotaxe >> vitamines >> proteines >> mineraux;
		return new PlatBioVege(nom, prix, coutDeRevient, ecotaxe, vitamines, proteines, mineraux);
	case TypePlat::Vege:
		lectureLigne >> vitamines >> proteines >> mineraux;
		return new PlatVege(nom, prix, coutDeRevient, vitamines, proteines, mineraux);
	default:
		return new Plat{ nom, prix, coutDeRevient };
	}

}

// Fonctions globales.

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& os, const Menu& menu
///RETOUR :ostream os
///DESCRIPTION :surcharge de l'operateur<< qui sert a afficher le menu, ainsi que le menu entierement vege
/////////////////////////////////////////////////
ostream& operator<<(ostream& os, const Menu& menu)
{
	os << "VOICI SON MENU " << endl;
	for (int i = 0; i < menu.listePlats_.size(); i++)
	{
		menu.listePlats_[i]->afficherPlat(os);
    }

	os << endl << "MENU ENTIEREMENT VEGETARIEN" << endl;
	for (int i = 0; i < menu.listePlatsVege_.size(); i++)
	{
		menu.listePlatsVege_[i]->afficherVege(os);
	}

	return os;
}
