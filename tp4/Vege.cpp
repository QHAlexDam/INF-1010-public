
#include "Vege.h"
#include "debogageMemoire.hpp"

//Constructeur
Vege::Vege(string nom, double vitamines, double proteines, double mineraux)
	: nom_(nom),vitamines_(vitamines), proteines_(proteines), mineraux_(mineraux)
{
}

//Destructeur
Vege::~Vege() {}

//Getter

double Vege::getVitamines() const
{
	return vitamines_;
}

double Vege::getProteines() const
{
	return proteines_;
}

double Vege::getMineraux() const
{
	return mineraux_;
}

//Setter

void Vege::setVitamines(double vitamines)
{
	vitamines_ = vitamines;
}

void Vege::setProteines(double proteines)
{
	proteines_ = proteines;
}

void Vege::setMineraux(double mineraux)
{
	mineraux_ = mineraux;
}


//Afficheur

/////////////////////////////////////////////////
///NOM: afficherVege
///PARAMETRES: ostream& os
///RETOUR : aucun
///DESCRIPTION : affiche les donnees pertinente a Vege
/////////////////////////////////////////////////
void Vege::afficherVege(ostream & os) const
{
	os << "PLAT VEGE " << nom_ << " " 
		<< "Vitamines: "  << vitamines_ << " " 
		<< "Proteines: " << proteines_ << " " 
		<< "Mineraux: " << mineraux_ << endl;
}


