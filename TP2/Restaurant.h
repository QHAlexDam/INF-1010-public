
#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Table.h"
#include "Menu.h"
const int INTTABLES = 6;
class Restaurant {
public:
	//constructeurs
	Restaurant();
	Restaurant(const string& fichier, const string& nom,  TypeMenu moment);
	Restaurant(const Restaurant& restaurant);

	//destructeur
	~Restaurant();

	//setters
	void setMoment(TypeMenu moment);
	void setNom(string nom);

	//getters
	string getNom() const;
	TypeMenu getMoment() const;

	//Autres methodes
	void lireTable(const string& fichier);
	void libererTable(int id);
	void commanderPlat(const string& nom, int idTable);
	void placerClients(int nbClients);

	//Overload d'operateur
	friend ostream& operator<<(ostream& out, const Restaurant& restaurant);
	friend bool operator<(const Restaurant& restaurant1, const Restaurant& restaurant2); // compare le chiffre d'affaire entre 2 restos
	Restaurant& operator+=(Table* table);
	Restaurant& operator=(const Restaurant& restaurant);

private:
	string* nom_;
	double chiffreAffaire_;
	TypeMenu momentJournee_;

	//differents menus en fonction du moment de la journee
	Menu* menuMatin_;
	Menu* menuMidi_;
	Menu* menuSoir_;

	vector<Table*> tables_;
};
#endif // !RESTAURANT_H
