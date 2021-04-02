

#include "Plat.h"
#include "PlatBio.h"
#include "PlatVege.h"
#include "PlatBioVege.h"
#include "debogageMemoire.hpp"
using namespace std;

//Constructeur

Plat::Plat(string_view nom, double prix, double cout) : nom_(nom), prix_(prix), cout_(cout) {
}
Plat::~Plat()
{}

//getters 

string Plat::getNom() const {
	return nom_;
}

double Plat::getPrix() const {
	return prix_;
}

double Plat::getCout() const {
	return cout_;
}

double Plat::getPrixRevient() const
{
	return (prix_ - cout_);

}

//setters 

void Plat::setNom(string nom) {
	nom_ = nom;
}

void Plat::setPrix(double prix) {
	prix_ = prix;
}



//Afficheur

/////////////////////////////////////////////////
///NOM: afficherPlat
///PARAMETRES: ostream & os
///RETOUR :aucun
///DESCRIPTION :afficheur qui affiche les donnees pertinentes d'un plat
/////////////////////////////////////////////////
void Plat::afficherPlat(ostream & os) const
{
	os << "PLAT -----" << nom_ << " - " << prix_ << "$ " << "(" << cout_ << "$ pour le restaurant)" << endl;
}

//Autre methodes

bool Plat::operator < (const Plat& plat) const
{
	return prix_ < plat.prix_;
}

/////////////////////////////////////////////////
///NOM: clone
///PARAMETRES: aucun
///RETOUR :Plat*
///DESCRIPTION :methode qui renvoie un nouvel objet qui est une copie de l'objet courant
/////////////////////////////////////////////////
 Plat *  Plat:: clone () const
{ 
	 return new Plat(nom_, prix_, cout_);
}
