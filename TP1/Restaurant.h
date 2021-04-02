

#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <fstream>
#include <string>
#include "Table.h"

const int INTTABLES = 6;
class Restaurant {
public: 
	//constructeurs 
	Restaurant(); 
	Restaurant(string& fichier, string& nom,  TypeMenu moment); 

	//Destructeur
	~Restaurant();

	//setters 
	void setMoment(TypeMenu moment); 

	//getters 
	string getNom() const; 
	TypeMenu getMoment() const; 

	//Autres methodes 
	void lireTable(string& fichier); 
	void ajouterTable(int id, int nbPlaces);
	void libererTable(int id); 
	void commanderPlat(string& nom, int idTable);
	void placerClients(int nbClients); 

	//affichage 
	void afficher() const;

private: 
	string* nom_; 

	double chiffreAffaire_; 
	TypeMenu momentJournee_; 

	//differents menus en fonction du moment de la journee
	//string nomFichier = "polyFood.txt";
	Menu* menuMatin_; // = new Menu(nomFichier, Matin);
	Menu* menuMidi_; // = new Menu(nomFichier, Midi);
	Menu* menuSoir_; // = new Menu(nomFichier, Soir);

	//liste des tables 
	unsigned int capaciteTables_;
	Table** tables_; 
	unsigned int nbTables_; 

};
#endif // !RESTAURANT_H
