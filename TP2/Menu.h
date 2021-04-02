

#ifndef MENU_H
#define MENU_H

#include<vector>
#include "Plat.h"
#include <fstream>


enum TypeMenu{Matin, Midi, Soir};
const int MAXPLAT = 5;
class Menu {
public:
	// constructeurs
	Menu(); // constructeur par defaut
	Menu(string fichier, TypeMenu type);// constructeur par parametre
	Menu(const Menu& menu); // constructeur par copie

	//destructeur
	~Menu();

	//getters
	int getNbPlats() const;
	TypeMenu getType() const;
	vector<Plat*> getListePlat() const;

	//surcharge d'operateurs
	//void afficher() const; //A MODIFIER
	friend ostream& operator<<(ostream& out, const Menu& menu); 
	Menu& operator+=(Plat*  plat);
	Menu& operator=(const Menu& menu);
	

	//methodes en plus
	Plat* trouverPlat(const string& nom) const; // A MODIFIER
	Plat * trouverPlatMoinsCher() const; // Utilise les vecteurs (NE PAS MODIFIER)
	//void ajouterPlat(Plat& plat); // A MODIFIER
	bool lireMenu(const string& fichier);

private :
	// A MODIFIER
	//int capacite_;
	//Plat** listePlats_;
	//int nbPlats_;
	TypeMenu type_;

	vector<Plat*> listePlats_;
};

#endif // !MENU_H
