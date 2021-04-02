

#ifndef PLAT_H
#define PLAT_H

#include <string>
#include<vector>
#include <iostream>

using namespace std;

class Plat {
public:

	// constructeurs
	Plat();
	Plat(string nom, double prix, double cout);

	//getters
	string getNom() const;
	double getPrix() const;
	double getCout() const;

	//setters
	void setNom(string nom);
	void setPrix(double prix);

	//Overload d'operateurs
	friend ostream& operator<< (ostream& out, const Plat& plat);
	friend bool operator<(const Plat& plat1, const Plat& plat2);

private:
	string nom_;
	double prix_;
	double cout_;

};

#endif // !PLAT_H
