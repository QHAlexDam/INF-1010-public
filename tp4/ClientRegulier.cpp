
#include "ClientRegulier.h"
#include "debogageMemoire.hpp"

//Constructeur

ClientRegulier::ClientRegulier()
{
	nbPoints_ = 0;
}

/////////////////////////////////////////////////
///NOM: ClientRegulier
///PARAMETRES: string_view nom, string_view prenom, int tailleGroupe, int npoints
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de ClientRegulier, utilise le contructeur 
///				par parametre de la classe Client et set le nombre de points au parametre
/////////////////////////////////////////////////
ClientRegulier::ClientRegulier(string_view nom, string_view prenom, int tailleGroupe, int npoints)
	: Client(nom , prenom, tailleGroupe), nbPoints_(npoints)
{ // ok
}

//Destructeur
ClientRegulier::~ClientRegulier() {}

//Getter
int ClientRegulier::getNbPoints() const
{
	return nbPoints_;
}

/////////////////////////////////////////////////
///NOM: getReduction
///PARAMETRES: const Restaurant & res, double montant, bool estLivraison
///RETOUR : double reduction
///DESCRIPTION :methode qui calcule la reduction et la retourne
/////////////////////////////////////////////////
double ClientRegulier::getReduction(const Restaurant & res, double montant, bool estLivraison) const
{
	//ok
	double reduction = 0.0;
	if (nbPoints_ > SEUIL_DEBUT_REDUCTION) {
		reduction = ((-montant)*TAUX_REDUC_REGULIER);
	}
	return reduction;
}

//Afficheur

/////////////////////////////////////////////////
///NOM: afficherClient
///PARAMETRES: ostream & os
///RETOUR :aucun
///DESCRIPTION :afficheur qui utilise l'afficheur de la classe de base Client, en plus du nombre de points
/////////////////////////////////////////////////
void ClientRegulier::afficherClient(ostream & os) const
{
	//ok
	Client::afficherClient(os);
	os << "points: " << nbPoints_ << endl;
}

//Autre methodes

void ClientRegulier::augmenterNbPoints(int bonus)
{
	nbPoints_ += bonus;
}

