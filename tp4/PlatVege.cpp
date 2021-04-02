
#include "PlatVege.h"
#include "debogageMemoire.hpp"

//Constructeur

/////////////////////////////////////////////////
///NOM: PlatVege
///PARAMETRES: string nom, double prix, double cout, double vitamines, double proteines, double mineraux
///RETOUR :aucun
///DESCRIPTION :constructeur par parametre de PlatVege qui utilise le constructeur par parametre de Plat et celui de Vege
/////////////////////////////////////////////////
PlatVege::PlatVege(string nom, double prix, double cout , double vitamines, double proteines, double mineraux)
	: Plat(nom , prix, cout), Vege (nom, vitamines, proteines, mineraux)
{
	setTaxe();
}

//Destructeur

PlatVege::~ PlatVege(){}

//Setter

void PlatVege::setTaxe()
{
	taxe_ = 0.07;
	 
}

//Getter

double PlatVege::getTaxe() const
{
	return taxe_;
}

//Afficheur

/////////////////////////////////////////////////
///NOM: afficherPlat
///PARAMETRES: ostream& os
///RETOUR : aucun
///DESCRIPTION : affiche les donnees pertinente a PlatBio, utilise l'afficheur de la classe de base Plat et de celui de Vege
/////////////////////////////////////////////////
void PlatVege::afficherPlat(ostream & os) const
{
	Plat::afficherPlat(os);
	os << "PLAT VEGE ";
	Vege::afficherVege(os);
	os << "(Apport nutritif: " << calculerApportNutritif() << "mg)" << endl;
}

//Autres methodes

/////////////////////////////////////////////////
///NOM: clone
///PARAMETRES: aucun
///RETOUR :Plat* (reelement un pointeur vers un PlatVege)
///DESCRIPTION :methode qui renvoie un nouvel objet qui est une copie de l'objet courant
/////////////////////////////////////////////////
Plat* PlatVege::clone()const
{ 
	return new PlatVege(Plat::nom_, prix_, cout_, vitamines_, proteines_, mineraux_);
}

/////////////////////////////////////////////////
///NOM: calculerApportNutritif
///PARAMETRES: aucun
///RETOUR :double apportNutritif
///DESCRIPTION :methode qui calcule et retourne l'apport nutritif
/////////////////////////////////////////////////
double PlatVege::calculerApportNutritif() const
{
	return (vitamines_*proteines_/mineraux_)*RAPPORT_NUTRITIF;
}


