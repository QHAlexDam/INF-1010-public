

#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include "Menu.h"

const  int MAXCAP = 5;
class Table {
public: 
	//Constructeurs 
	Table(); 
	Table(int id, int nbPlaces);

	//Destructeur
	~Table();

	//Getters 
	int getId() const; 
	int getNbPlaces() const; 
	bool estOccupee() const; 

	//Setters 
	void libererTable(); 
	void placerClient(); 
	void setId(int id); 

	//Autres methodes 
	void commander(Plat* plat); 
	double getChiffreAffaire() const;

	//affichage
	void afficher() const; 

private : 
	Plat** commande_; 
	unsigned int capacite_; 
	unsigned int nbPlats_; 

	int id_; 
	unsigned int nbPlaces_; 
	bool occupee_; 
};
#endif // !TABLE_H
