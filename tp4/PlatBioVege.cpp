
#include "PlatBioVege.h"
#include "Vege.h"
#include"PlatBio.h"
#include "debogageMemoire.hpp"

//Constructeur

/////////////////////////////////////////////////
///NOM: PlatBioVege
///PARAMETRES: string nom, double prix, double cout, double ecotaxe, double vitamines, double proteines, double mineraux
///RETOUR :aucun
///DESCRIPTION :constructeur par parametre de PlatBioVege qui utilise le constructeur par parametre de PlatBio et celui de Vege
/////////////////////////////////////////////////
PlatBioVege::PlatBioVege(string nom, double prix, double cout, double ecotaxe, double vitamines, double proteines, double mineraux)
	: PlatBio(nom, prix, cout, ecotaxe), Vege(nom, vitamines, proteines, mineraux)
{ 

}

//Destructeur

PlatBioVege:: ~PlatBioVege(){}

//Afficheur

/////////////////////////////////////////////////
///NOM: afficherPlat
///PARAMETRES: ostream& os
///RETOUR : aucun
///DESCRIPTION : affiche les donnees pertinente a PlatBioVege, utilise les afficher des classes meres PlatBio et Vege
/////////////////////////////////////////////////
void PlatBioVege::afficherPlat(ostream & os) const
{   
	PlatBio::afficherPlat(os);
	
	os << "ET ";

	Vege::afficherVege(os);
	

}

//Autre methodes

/////////////////////////////////////////////////
///NOM: calculerApportNutritif
///PARAMETRES: aucun
///RETOUR :double apportNutritif
///DESCRIPTION :methode qui calcule et retourne l'apport nutritif
/////////////////////////////////////////////////
double PlatBioVege::calculerApportNutritif() const
{
	return ((vitamines_* proteines_)/mineraux_)*RAPPORT_NUTRITIF_BIO*AVANTAGE_SANS_PESTICIDE;
}

/////////////////////////////////////////////////
///NOM: clone
///PARAMETRES: aucun
///RETOUR :Plat* (reelement un pointeur vers un PlatBioVege)
///DESCRIPTION :methode qui renvoie un nouvel objet qui est une copie de l'objet courant
/////////////////////////////////////////////////
Plat * PlatBioVege::clone() const
{ 
	Plat* clone = new PlatBioVege(PlatBio::nom_, prix_, cout_, ecoTaxe_, vitamines_, proteines_, mineraux_);  
	return clone;
}


