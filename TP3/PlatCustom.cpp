

#include "PlatCustom.h"

/////////////////////////////////////////////////
///NOM: PlatCustom
///PARAMETRES: string nom, double prix, double cout, int nbIngredients
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de PlatCustom
/////////////////////////////////////////////////
PlatCustom::PlatCustom(string nom, double prix, double cout, int nbIngredients): Plat(nom, prix, cout)
{
	nbIngredients_ = nbIngredients;
	supplement_ = calculerSupplement();
	type_ = Custom;
}

/////////////////////////////////////////////////
///NOM: getNbIngredients
///PARAMETRES: aucun
///RETOUR : nbIngredients_
///DESCRIPTION : getter qui retourne le nombre d'ingredients additionnel a ajouter
/////////////////////////////////////////////////
int PlatCustom::getNbIngredients() const
{
	return nbIngredients_;
}

/////////////////////////////////////////////////
///NOM: getSupplement
///PARAMETRES: aucun
///RETOUR : supplement_
///DESCRIPTION : getter qui retourne le supplement a payer
/////////////////////////////////////////////////
double PlatCustom::getSupplement() const
{
	return supplement_;
}

/////////////////////////////////////////////////
///NOM: setNbIngredients
///PARAMETRES: int nIngredients
///RETOUR : aucun
///DESCRIPTION : change le nb d'ingredients
/////////////////////////////////////////////////
void PlatCustom::setNbIngredients(int nIngredients) 
{
	nbIngredients_ = nIngredients;
}

/////////////////////////////////////////////////
///NOM: calculerSupplement
///PARAMETRES: aucun
///RETOUR : le calcul du suplement (double)
///DESCRIPTION : calcule le supplent a partir du nb d'ingredients
/////////////////////////////////////////////////
double PlatCustom::calculerSupplement() const
{
	return (nbIngredients_ * FRAIS_CUSTOMISATION);
}

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& os, const PlatCustom& plat
///RETOUR : os
///DESCRIPTION : Methode qui overload l'operateur <<, qui a comme fonction d'afficher les attributs pertinents d'un PlatCustom
/////////////////////////////////////////////////
ostream & operator<<(ostream & os, const PlatCustom & plat)
{
	// TODO: insert return statement here
	//Plat plat2 = static_cast<PlatCustom>(plat);
	os << static_cast<Plat>(plat) << " contient: " << plat.nbIngredients_ 
		<< " ingredients extra pour un supplement de : " << plat.getSupplement() <<"$" << endl;
	return os;
}
