

#ifndef MENU_H
#define MENU_H 
#include <fstream>
#include <string>
#include <iostream>
#include "Plat.h"


enum TypeMenu{Matin, Midi, Soir}; // represente les 3 types de menu que possede le restaurant dependamment du moment de la journee
const int MAXPLAT = 5; // represente le nombre de plat par menu
class Menu {
public: 
	//Constructeurs
	Menu(); 
	Menu(string fichier, TypeMenu type); 

	//Destructeur 
	~Menu();

	//Getters
	int getNbPlats() const; 
	int getCapcite() const;
	TypeMenu getTypeMenu() const;
	Plat** getListePlat() const;
	
	//Affichage 
	void afficher() const; 

	//Methodes en plus
	Plat* trouverPlat(string& nom); 
	void ajouterPlat(Plat & plat); 
	void ajouterPlat(string& nom, double montant, double cout); 
	bool lireMenu(string& fichier); 
	
private : 
	unsigned int capacite_;
	Plat** listePlats_;  
	unsigned int nbPlats_; 
	TypeMenu type_; 
};

#endif // !MENU_H
