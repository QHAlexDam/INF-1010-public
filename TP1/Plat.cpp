
/*

*/

#include<iostream>
#include<string>
#include "Plat.h"

using namespace std;

//Constructeurs
Plat::Plat() // constructeur par defaut
{ 
	nom_ = "inconnu";
	prix_ = 0;
	cout_ = 0;
}
Plat::Plat(string nom, double prix, double cout) // constructeur par parametre
{
	nom_ = nom;
	prix_ = prix;
	cout_ = cout;
}

//Destructeur
Plat::~Plat()
{

}

//Getters
string Plat::getNom() const // retourne le nom du plat
{
	return nom_;
}
double Plat::getPrix() const // retourne le prix du plat 
{
	return prix_;
}
double Plat::getCout() const // retourne le cout du plat
{
	return cout_;
}

//Setters
void Plat::setNom(string nom) // modifie le nom du plat avec le nouveau nom entre en parametre
{
	nom_ = nom;
}
void Plat::setPrix(double prix) // modifie le prix du plat, avec le nouveau prix en parametre
{ 
	prix_ = prix;
}

/*Fonction d'affichage
Affiche les detail du plat, soit le nom, le prix ($) charge au client et le cout ($) de production
*/
void Plat::afficher() const
{
	cout << "	" << nom_ << " - " << prix_ << " $ " << "(" << cout_ << " $ pour le restaurant)" << endl;

}
