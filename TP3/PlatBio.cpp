

#include "PlatBio.h"

/////////////////////////////////////////////////
///NOM: PlatBio
///PARAMETRES: string nom, double prix, double cout, double ecotaxe
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de PlatBio
/////////////////////////////////////////////////
PlatBio::PlatBio(string nom, double prix, double cout, double ecotaxe): Plat(nom, prix, cout), ecoTaxe_ (ecotaxe)
{
	type_ = Bio;
}

/////////////////////////////////////////////////
///NOM: getEcoTaxe
///PARAMETRES: aucun
///RETOUR : ecotaxe_
///DESCRIPTION : getter qui retourne la valeur de l'eco taxe
/////////////////////////////////////////////////
double PlatBio::getEcoTaxe() const
{
	return ecoTaxe_;
}

/////////////////////////////////////////////////
///NOM: setEcoTaxe
///PARAMETRES: double ecoTaxe
///RETOUR : aucun
///DESCRIPTION : getter qui modifie l'eco taxe
/////////////////////////////////////////////////
void PlatBio::setEcoTaxe(double ecoTaxe)
{
	ecoTaxe_ = ecoTaxe ; 
}

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& os, const PlatBio& plat
///RETOUR : os
///DESCRIPTION : Methode qui overload l'operateur <<, qui a comme fonction d'afficher les attributs pertinents d'un PlatBio
/////////////////////////////////////////////////
ostream & operator<<(ostream & os, const PlatBio & plat)
{
	os << static_cast<Plat>(plat);
	os << "son eco-Tax est : " << plat.getEcoTaxe() << "$" <<endl;
	return os;
}
