

#include "Plat.h"
#include<vector>

//constructeurs

/////////////////////////////////////////////////
///NOM: Plat
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : Constructeur par defaut de Plat, initialise le nom a "Inconnu", le prix et le cout a 0
/////////////////////////////////////////////////
Plat::Plat() : nom_("Inconnu"), prix_(0), cout_(0){
}

/////////////////////////////////////////////////
///NOM: Plat
///PARAMETRES: String nom, double prix, double cout
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de Plat, initialise le nom, le prix et le cout a des valeurs entrees en parametre
/////////////////////////////////////////////////
Plat::Plat(string nom, double prix, double cout) : nom_(nom), prix_(prix), cout_(cout) {
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

//overload d'operateurs

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& out, const Plat& plat
///RETOUR : out
///DESCRIPTION : Methode qui overload l'operateur <<, qui a comme fonction d'afficher les attributs pertinents d'un Plat
/////////////////////////////////////////////////
ostream& operator<< (std::ostream& out, const Plat& plat){
	out << plat.getNom() << " - " << plat.getPrix()<< " $ (" << plat.getCout() << "$ pour le restaurant)" << endl;
	return out;
}

/////////////////////////////////////////////////
///NOM: operator<
///PARAMETRES: const Plat& plat1, const Plat& plat1
///RETOUR : bool estMoinsCher
///DESCRIPTION : Methode qui overload l'operateur <, qui compare les prix entre un plat (plat1) et un deuxieme (plat2), 
///				retourne vrai si plat1 est moins cher que plat2
/////////////////////////////////////////////////
bool operator<(const Plat& plat1, const Plat& plat2) {
	bool estMoinsCher = false;

	if (plat1.getPrix() < plat2.getPrix()) {
		estMoinsCher = true;
	}
	return estMoinsCher;
}