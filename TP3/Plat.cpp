

#include "Plat.h"

//constructeur 

/////////////////////////////////////////////////
///NOM: Plat
///PARAMETRES: String nom, double prix, double cout
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de Plat, initialise le nom, le prix et le cout a des valeurs entrees en parametre
/////////////////////////////////////////////////
Plat::Plat(string nom , double prix , double cout){
	nom_ = nom;
	prix_ = prix; 
	cout_ = cout; 
	type_ = Regulier;
}
//getters 

/////////////////////////////////////////////////
///NOM: getNom
///PARAMETRES: aucun
///RETOUR : nom_
///DESCRIPTION : getter qui retourne le nom du plat
/////////////////////////////////////////////////
string Plat::getNom() const {
	return nom_; 
}

/////////////////////////////////////////////////
///NOM: getPrix
///PARAMETRES: aucun
///RETOUR : prix_
///DESCRIPTION : getter qui retourne le prix du plat
/////////////////////////////////////////////////
double Plat::getPrix() const {
	return prix_; 
}

/////////////////////////////////////////////////
///NOM: getCout
///PARAMETRES: aucun
///RETOUR : cout_
///DESCRIPTION : getter qui retourne le cout du plat
/////////////////////////////////////////////////
double Plat::getCout() const {
	return cout_; 
}

/////////////////////////////////////////////////
///NOM: getType
///PARAMETRES: aucun
///RETOUR : type
///DESCRIPTION : getter qui retourne le type de plat (regulier, bio, custom)
/////////////////////////////////////////////////
TypePlat Plat::getType() const
{
	return type_;
}

//setters 

/////////////////////////////////////////////////
///NOM: setNom
///PARAMETRES: String nom
///RETOUR : aucun
///DESCRIPTION : Setter qui modifie le nom du plat avec le nom passe en parametre
/////////////////////////////////////////////////
void Plat::setNom(string nom) {
	nom_ = nom; 
}

/////////////////////////////////////////////////
///NOM: setPrix
///PARAMETRES: double prix
///RETOUR : aucun
///DESCRIPTION : Setter qui modifie le prix du plat avec le prix passe en parametre
/////////////////////////////////////////////////
void Plat::setPrix(double prix) {
	prix_ = prix; 
}

/////////////////////////////////////////////////
///NOM: operator<
///PARAMETRES: const Plat& plat1, const Plat& plat1
///RETOUR : bool estMoinsCher
///DESCRIPTION : Methode qui overload l'operateur <, qui compare les prix entre un plat (plat1) et un deuxieme (plat2), 
///				retourne vrai si plat1 est moins cher que plat2
/////////////////////////////////////////////////
bool Plat::operator<(const Plat& plat) const 
{
	return this->prix_ < plat.prix_;
}

//autres methodes

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& os, const Plat& plat
///RETOUR : os
///DESCRIPTION : Methode qui overload l'operateur <<, qui a comme fonction d'afficher les attributs pertinents d'un Plat
/////////////////////////////////////////////////
ostream& operator<<(ostream& os, const Plat& plat)
{
	os << plat.nom_ << " - " << plat.prix_ << " $ (" << plat.cout_ << "$ pour le restaurant)  " ;
	return os;
}