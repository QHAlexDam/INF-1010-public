
#include "PlatBio.h"
#include "debogageMemoire.hpp"

//Constructeur

/////////////////////////////////////////////////
///NOM: PlatBio
///PARAMETRES: string nom, double prix, double cout, double ecotaxe
///RETOUR :aucun
///DESCRIPTION :constructeur par parametre de PlatBio qui utilise le constructeur par parametre de Plat
/////////////////////////////////////////////////
PlatBio::PlatBio(string nom, double prix, double cout, double ecotaxe)
	: Plat(nom, prix, cout), ecoTaxe_(ecotaxe)
{}

//Destructeur

PlatBio::~ PlatBio(){}

//Getter

double PlatBio::getEcoTaxe() const
{
	return ecoTaxe_;
}

/////////////////////////////////////////////////
///NOM: getPrixDeRevient
///PARAMETRES: aucun
///RETOUR :double prixDeRevient
///DESCRIPTION : Methode qui calcule de prix de revient qui inclue l'ecotaxe
/////////////////////////////////////////////////
double PlatBio::getPrixDeRevient() const
{ 
	return (Plat::getPrix() - Plat::getCout() + ecoTaxe_);

}

//Setter

void PlatBio::setEcoTaxe(double ecoTaxe)
{
	ecoTaxe_ = ecoTaxe;
}

//Afficheur

/////////////////////////////////////////////////
///NOM: afficherPlat
///PARAMETRES: ostream& os
///RETOUR : aucun
///DESCRIPTION : affiche les donnees pertinente a PlatBio, utilise l'afficheur de la classe de base Plat
/////////////////////////////////////////////////
void PlatBio::afficherPlat(ostream& os) const
{
	Plat::afficherPlat(os);
	os << "PLat Bio comprend une Taxe ecologique de : " << ecoTaxe_ << "$" << endl;
}

//Autre methodes

/////////////////////////////////////////////////
///NOM: clone
///PARAMETRES: aucun
///RETOUR :Plat* (reellement un pointeur vers un PlatBio)
///DESCRIPTION :methode qui renvoie un nouvel objet qui est une copie de l'objet courant
/////////////////////////////////////////////////
Plat * PlatBio:: clone () const
{
	Plat* clone = new PlatBio(nom_, prix_, cout_, ecoTaxe_);
	return clone;
}


